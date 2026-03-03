/**
 * @file thread_pool.h
 * @brief POSIX线程池实现头文件
 *
 * 提供线程池的创建、销毁、任务提交、动态调整线程数、暂停/恢复等功能。
 * 线程池使用不透明指针设计，对外仅暴露前向声明，具体实现在.c文件中。
 *
 * @note 编译时需要链接pthread库：gcc -pthread thread_pool.c example.c -o example
 */

#pragma once

#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief 任务节点结构体
 *
 * 表示线程池中的一个任务，包含任务函数、参数和链表指针。
 */
typedef struct task_s
{
    void (*function)(void *); /**< 任务函数指针 */
    void *arg;                /**< 任务函数参数 */
    struct task_s *next;      /**< 链表下一节点指针 */
} task_t;

/**
 * @brief 线程池结构体（不透明指针）
 *
 * 线程池的主要数据结构，对外仅暴露前向声明。
 * 具体定义在thread_pool.c中，以封装内部实现细节。
 */
typedef struct thread_pool_s thread_pool_t;

/**
 * @brief 创建线程池
 *
 * 分配并初始化线程池结构体，创建指定数量的工作线程并启动。
 *
 * @param num_threads 初始线程数量
 * @return thread_pool_t* 成功返回线程池指针，失败返回NULL
 */
thread_pool_t *thread_pool_create(size_t num_threads);

/**
 * @brief 销毁线程池
 *
 * 设置停止标志，等待所有已提交任务完成（暂停状态下先恢复），
 * 唤醒所有线程等待它们退出，最后释放所有资源。
 *
 * @param pool 线程池指针
 */
void thread_pool_destroy(thread_pool_t *pool);

/**
 * @brief 提交任务到线程池
 *
 * 将任务加入队列，等待工作线程执行。
 *
 * @param pool 线程池指针
 * @param function 任务函数指针
 * @param arg 任务函数参数
 * @return int 成功返回0，失败返回-1（如pool已停止或内存不足）
 */
int thread_pool_submit(thread_pool_t *pool, void (*function)(void *), void *arg);

/**
 * @brief 动态调整线程池大小
 *
 * 调整线程池中的工作线程数量：
 * - 若new_thread_count大于当前线程数：创建新线程并加入线程池
 * - 若小于：设置退出标志，让多余的空闲线程自行退出
 *
 * @param pool 线程池指针
 * @param new_thread_count 新的线程数量
 * @return int 成功返回0，失败返回-1（如内存不足）
 */
int thread_pool_resize(thread_pool_t *pool, size_t new_thread_count);

/**
 * @brief 暂停线程池
 *
 * 设置暂停标志，已提交但未开始的任务暂停执行（正在执行的继续）。
 * 工作线程在取任务前检查暂停标志，若为真则等待条件变量。
 */
void thread_pool_pause(thread_pool_t *pool);

/**
 * @brief 恢复线程池
 *
 * 清除暂停标志，并广播条件变量唤醒等待的线程继续取任务。
 */
void thread_pool_resume(thread_pool_t *pool);

/**
 * @brief 获取当前工作线程数量
 *
 * @param pool 线程池指针
 * @return size_t 当前线程数量
 */
size_t thread_pool_worker_count(thread_pool_t *pool);

/**
 * @brief 获取等待执行的任务数量
 *
 * @param pool 线程池指针
 * @return size_t 等待任务数
 */
size_t thread_pool_pending_count(thread_pool_t *pool);

/**
 * @brief 检查线程池是否处于暂停状态
 *
 * @param pool 线程池指针
 * @return bool 暂停返回true，否则返回false
 */
bool thread_pool_is_paused(thread_pool_t *pool);