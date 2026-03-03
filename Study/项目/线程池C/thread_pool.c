/**
 * @file thread_pool.c
 * @brief POSIX线程池实现
 *
 * 实现线程池的核心功能，包括创建、销毁、任务提交、动态调整线程数、
 * 暂停/恢复等功能。使用链表作为任务队列，支持线程安全的操作。
 */

#include "thread_pool.h"
#include <stdio.h>
#include <errno.h>

/**
 * @brief 线程池结构体定义
 *
 * 包含线程池的所有状态信息，使用互斥锁和条件变量保护共享数据。
 */
struct thread_pool_s
{
    pthread_t *threads;          /**< 线程数组 */
    size_t thread_count;         /**< 当前线程数量 */
    size_t max_threads;          /**< 线程数组容量（用于动态调整） */
    task_t *task_queue_head;     /**< 任务队列头指针 */
    task_t *task_queue_tail;     /**< 任务队列尾指针（便于入队） */
    size_t pending_count;        /**< 等待执行的任务数 */
    pthread_mutex_t queue_mutex; /**< 保护任务队列和状态 */
    pthread_cond_t queue_cond;   /**< 通知线程取任务 */
    pthread_cond_t pause_cond;   /**< 用于暂停等待 */
    bool stop;                   /**< 停止标志（析构时设置） */
    bool paused;                 /**< 暂停标志 */
    size_t threads_to_stop;      /**< 需要退出的线程数（用于动态缩减） */
};

/**
 * @brief 工作线程函数
 *
 * 每个工作线程的执行入口，循环从任务队列中取出任务执行。
 * 支持线程退出、暂停、动态缩减等功能。
 *
 * @param arg 线程池指针
 * @return void* 总是返回NULL
 */
static void *worker(void *arg)
{
    thread_pool_t *pool = (thread_pool_t *)arg;

    while (1)
    {
        pthread_mutex_lock(&pool->queue_mutex);

        /* 检查是否需要退出 */
        while ((pool->task_queue_head == NULL && pool->stop) ||
               (pool->threads_to_stop > 0 && pool->task_queue_head == NULL))
        {

            /* 如果是动态缩减导致的退出 */
            if (pool->threads_to_stop > 0 && pool->task_queue_head == NULL)
            {
                pool->threads_to_stop--;
                pool->thread_count--;
                pthread_mutex_unlock(&pool->queue_mutex);
                pthread_exit(NULL);
            }

            /* 如果是线程池销毁导致的退出 */
            if (pool->task_queue_head == NULL && pool->stop)
            {
                pool->thread_count--;
                pthread_mutex_unlock(&pool->queue_mutex);
                pthread_exit(NULL);
            }
        }

        /* 检查是否暂停 */
        while (pool->paused && !pool->stop)
        {
            pthread_cond_wait(&pool->pause_cond, &pool->queue_mutex);
        }

        /* 再次检查退出条件（可能在等待暂停时被设置） */
        if (pool->stop && pool->task_queue_head == NULL)
        {
            pool->thread_count--;
            pthread_mutex_unlock(&pool->queue_mutex);
            pthread_exit(NULL);
        }

        /* 从队列中取出任务 */
        if (pool->task_queue_head != NULL)
        {
            task_t *task = pool->task_queue_head;
            pool->task_queue_head = task->next;
            if (pool->task_queue_head == NULL)
            {
                pool->task_queue_tail = NULL;
            }
            pool->pending_count--;

            pthread_mutex_unlock(&pool->queue_mutex);

            /* 执行任务 */
            task->function(task->arg);

            /* 释放任务节点内存 */
            free(task);
        }
        else
        {
            /* 队列为空，等待新任务 */
            pthread_cond_wait(&pool->queue_cond, &pool->queue_mutex);
            pthread_mutex_unlock(&pool->queue_mutex);
        }
    }

    return NULL;
}

/**
 * @brief 创建线程池
 */
thread_pool_t *thread_pool_create(size_t num_threads)
{
    if (num_threads == 0)
    {
        return NULL;
    }

    /* 分配线程池结构体 */
    thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
    if (pool == NULL)
    {
        return NULL;
    }

    /* 初始化线程池字段 */
    pool->threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    if (pool->threads == NULL)
    {
        free(pool);
        return NULL;
    }

    pool->thread_count = 0;
    pool->max_threads = num_threads;
    pool->task_queue_head = NULL;
    pool->task_queue_tail = NULL;
    pool->pending_count = 0;
    pool->stop = false;
    pool->paused = false;
    pool->threads_to_stop = 0;

    /* 初始化互斥锁和条件变量 */
    if (pthread_mutex_init(&pool->queue_mutex, NULL) != 0)
    {
        free(pool->threads);
        free(pool);
        return NULL;
    }

    if (pthread_cond_init(&pool->queue_cond, NULL) != 0)
    {
        pthread_mutex_destroy(&pool->queue_mutex);
        free(pool->threads);
        free(pool);
        return NULL;
    }

    if (pthread_cond_init(&pool->pause_cond, NULL) != 0)
    {
        pthread_cond_destroy(&pool->queue_cond);
        pthread_mutex_destroy(&pool->queue_mutex);
        free(pool->threads);
        free(pool);
        return NULL;
    }

    /* 创建工作线程 */
    for (size_t i = 0; i < num_threads; i++)
    {
        if (pthread_create(&pool->threads[i], NULL, worker, pool) != 0)
        {
            /* 创建失败，回滚已创建的线程 */
            pool->stop = true;
            pthread_cond_broadcast(&pool->queue_cond);
            pthread_cond_broadcast(&pool->pause_cond);

            for (size_t j = 0; j < i; j++)
            {
                pthread_join(pool->threads[j], NULL);
            }

            pthread_cond_destroy(&pool->pause_cond);
            pthread_cond_destroy(&pool->queue_cond);
            pthread_mutex_destroy(&pool->queue_mutex);
            free(pool->threads);
            free(pool);
            return NULL;
        }
        pool->thread_count++;
    }

    return pool;
}

/**
 * @brief 销毁线程池
 */
void thread_pool_destroy(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return;
    }

    pthread_mutex_lock(&pool->queue_mutex);

    /* 如果处于暂停状态，先恢复 */
    if (pool->paused)
    {
        pool->paused = false;
        pthread_cond_broadcast(&pool->pause_cond);
    }

    /* 设置停止标志 */
    pool->stop = true;

    /* 唤醒所有等待的线程 */
    pthread_cond_broadcast(&pool->queue_cond);
    pthread_cond_broadcast(&pool->pause_cond);

    pthread_mutex_unlock(&pool->queue_mutex);

    /* 等待所有线程退出 */
    for (size_t i = 0; i < pool->max_threads; i++)
    {
        pthread_join(pool->threads[i], NULL);
    }

    /* 释放任务队列中剩余的任务（理论上应该为空） */
    task_t *task = pool->task_queue_head;
    while (task != NULL)
    {
        task_t *next = task->next;
        free(task);
        task = next;
    }

    /* 销毁同步对象 */
    pthread_mutex_destroy(&pool->queue_mutex);
    pthread_cond_destroy(&pool->queue_cond);
    pthread_cond_destroy(&pool->pause_cond);

    /* 释放内存 */
    free(pool->threads);
    free(pool);
}

/**
 * @brief 提交任务到线程池
 */
int thread_pool_submit(thread_pool_t *pool, void (*function)(void *), void *arg)
{
    if (pool == NULL || function == NULL)
    {
        return -1;
    }

    /* 创建任务节点 */
    task_t *task = (task_t *)malloc(sizeof(task_t));
    if (task == NULL)
    {
        return -1;
    }

    task->function = function;
    task->arg = arg;
    task->next = NULL;

    pthread_mutex_lock(&pool->queue_mutex);

    /* 检查线程池是否已停止 */
    if (pool->stop)
    {
        pthread_mutex_unlock(&pool->queue_mutex);
        free(task);
        return -1;
    }

    /* 将任务加入队列 */
    if (pool->task_queue_tail == NULL)
    {
        pool->task_queue_head = task;
        pool->task_queue_tail = task;
    }
    else
    {
        pool->task_queue_tail->next = task;
        pool->task_queue_tail = task;
    }

    pool->pending_count++;

    /* 通知等待的线程有新任务 */
    pthread_cond_signal(&pool->queue_cond);

    pthread_mutex_unlock(&pool->queue_mutex);

    return 0;
}

/**
 * @brief 动态调整线程池大小
 */
int thread_pool_resize(thread_pool_t *pool, size_t new_thread_count)
{
    if (pool == NULL || new_thread_count == 0)
    {
        return -1;
    }

    pthread_mutex_lock(&pool->queue_mutex);

    size_t current = pool->thread_count;

    if (new_thread_count > current)
    {
        /* 需要增加线程 */
        size_t to_add = new_thread_count - current;

        /* 检查是否需要扩大线程数组 */
        if (new_thread_count > pool->max_threads)
        {
            pthread_t *new_threads = (pthread_t *)realloc(pool->threads,
                                                          new_thread_count * sizeof(pthread_t));
            if (new_threads == NULL)
            {
                pthread_mutex_unlock(&pool->queue_mutex);
                return -1;
            }
            pool->threads = new_threads;
            pool->max_threads = new_thread_count;
        }

        /* 创建新线程 */
        for (size_t i = current; i < new_thread_count; i++)
        {
            if (pthread_create(&pool->threads[i], NULL, worker, pool) != 0)
            {
                /* 部分失败，但已创建的线程有效 */
                pthread_mutex_unlock(&pool->queue_mutex);
                return -1;
            }
            pool->thread_count++;
        }
    }
    else if (new_thread_count < current)
    {
        /* 需要减少线程 */
        size_t to_remove = current - new_thread_count;
        pool->threads_to_stop += to_remove;

        /* 唤醒所有等待的线程，让多余的空闲线程退出 */
        pthread_cond_broadcast(&pool->queue_cond);
        pthread_cond_broadcast(&pool->pause_cond);
    }

    pthread_mutex_unlock(&pool->queue_mutex);

    return 0;
}

/**
 * @brief 暂停线程池
 */
void thread_pool_pause(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return;
    }

    pthread_mutex_lock(&pool->queue_mutex);
    pool->paused = true;
    pthread_mutex_unlock(&pool->queue_mutex);
}

/**
 * @brief 恢复线程池
 */
void thread_pool_resume(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return;
    }

    pthread_mutex_lock(&pool->queue_mutex);
    pool->paused = false;
    pthread_cond_broadcast(&pool->pause_cond);
    pthread_mutex_unlock(&pool->queue_mutex);
}

/**
 * @brief 获取当前工作线程数量
 */
size_t thread_pool_worker_count(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return 0;
    }

    pthread_mutex_lock(&pool->queue_mutex);
    size_t count = pool->thread_count;
    pthread_mutex_unlock(&pool->queue_mutex);

    return count;
}

/**
 * @brief 获取等待执行的任务数量
 */
size_t thread_pool_pending_count(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return 0;
    }

    pthread_mutex_lock(&pool->queue_mutex);
    size_t count = pool->pending_count;
    pthread_mutex_unlock(&pool->queue_mutex);

    return count;
}

/**
 * @brief 检查线程池是否处于暂停状态
 */
bool thread_pool_is_paused(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return false;
    }

    pthread_mutex_lock(&pool->queue_mutex);
    bool paused = pool->paused;
    pthread_mutex_unlock(&pool->queue_mutex);

    return paused;
}