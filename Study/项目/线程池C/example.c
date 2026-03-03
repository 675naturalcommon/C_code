/**
 * @file example.c
 * @brief 线程池示例程序
 *
 * 演示线程池的各种功能：
 * 1. 创建线程池并提交任务
 * 2. 动态调整线程数
 * 3. 暂停和恢复
 * 4. 处理异常任务
 * 5. 共享变量和结果收集
 */

#include "thread_pool.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

/* 全局互斥锁用于保护共享结果 */
static pthread_mutex_t result_mutex = PTHREAD_MUTEX_INITIALIZER;
static int total_sum = 0;
static int completed_tasks = 0;

/**
 * @brief 普通任务函数
 *
 * 打印线程ID和参数，模拟工作（sleep）
 */
void print_task(void *arg)
{
    int task_id = *(int *)arg;
    pthread_t tid = pthread_self();

    printf("线程 %lu 正在执行任务 %d\n", (unsigned long)tid, task_id);
    sleep(1); // 模拟工作
    printf("线程 %lu 完成任务 %d\n", (unsigned long)tid, task_id);

    free(arg); // 释放动态分配的参数
}

/**
 * @brief 计算任务函数
 *
 * 计算累加和，将结果添加到全局变量中
 */
void compute_task(void *arg)
{
    int value = *(int *)arg;

    pthread_mutex_lock(&result_mutex);
    total_sum += value;
    completed_tasks++;
    pthread_mutex_unlock(&result_mutex);

    printf("计算任务完成: 值=%d, 当前总和=%d\n", value, total_sum);

    free(arg);
}

/**
 * @brief 异常任务函数
 *
 * 模拟可能发生异常的任务（如除零）
 */
void exception_task(void *arg)
{
    int task_id = *(int *)arg;

    printf("异常任务 %d 开始执行\n", task_id);

    /* 模拟除零异常 */
    if (task_id == 5)
    {
        printf("任务 %d 触发除零异常\n", task_id);
        /* 在C中，除零会导致SIGFPE信号，这里我们只是打印错误 */
        fprintf(stderr, "警告: 任务 %d 尝试除以零\n", task_id);
        /* 实际应用中应该使用信号处理或返回错误码 */
    }

    sleep(1);
    printf("异常任务 %d 完成（即使有异常也继续）\n", task_id);

    free(arg);
}

/**
 * @brief 长时间运行的任务
 */
void long_task(void *arg)
{
    int task_id = *(int *)arg;
    printf("长时间任务 %d 开始，将运行3秒\n", task_id);
    sleep(3);
    printf("长时间任务 %d 完成\n", task_id);
    free(arg);
}

/**
 * @brief 信号处理函数（可选）
 */
void signal_handler(int sig)
{
    printf("接收到信号 %d，线程池继续运行\n", sig);
}

int main()
{
    printf("=== 线程池示例程序开始 ===\n\n");

    /* 注册信号处理（可选） */
    signal(SIGSEGV, signal_handler);
    signal(SIGFPE, signal_handler);

    /* 1. 创建包含4个线程的线程池 */
    printf("1. 创建包含4个工作线程的线程池\n");
    thread_pool_t *pool = thread_pool_create(4);
    if (pool == NULL)
    {
        fprintf(stderr, "创建线程池失败\n");
        return 1;
    }
    printf("   线程池创建成功，当前线程数: %zu\n", thread_pool_worker_count(pool));

    /* 2. 提交10个普通任务 */
    printf("\n2. 提交10个普通任务\n");
    for (int i = 0; i < 10; i++)
    {
        int *task_id = malloc(sizeof(int));
        *task_id = i;
        if (thread_pool_submit(pool, print_task, task_id) != 0)
        {
            fprintf(stderr, "提交任务 %d 失败\n", i);
            free(task_id);
        }
    }
    printf("   已提交10个任务，等待任务数: %zu\n", thread_pool_pending_count(pool));

    /* 等待部分任务完成 */
    sleep(2);

    /* 3. 提交计算任务，演示共享变量 */
    printf("\n3. 提交5个计算任务（累加1-5）\n");
    for (int i = 1; i <= 5; i++)
    {
        int *value = malloc(sizeof(int));
        *value = i;
        if (thread_pool_submit(pool, compute_task, value) != 0)
        {
            fprintf(stderr, "提交计算任务 %d 失败\n", i);
            free(value);
        }
    }

    /* 4. 动态调整线程数 */
    printf("\n4. 动态调整线程数\n");
    printf("   当前线程数: %zu\n", thread_pool_worker_count(pool));

    printf("   增加到6个线程...\n");
    if (thread_pool_resize(pool, 6) == 0)
    {
        printf("   调整成功，当前线程数: %zu\n", thread_pool_worker_count(pool));
    }
    else
    {
        printf("   调整失败\n");
    }

    sleep(2);

    printf("   减少到2个线程...\n");
    if (thread_pool_resize(pool, 2) == 0)
    {
        printf("   调整成功，当前线程数: %zu\n", thread_pool_worker_count(pool));
    }
    else
    {
        printf("   调整失败\n");
    }

    /* 5. 暂停和恢复 */
    printf("\n5. 暂停线程池5秒\n");
    thread_pool_pause(pool);
    printf("   线程池已暂停: %s\n", thread_pool_is_paused(pool) ? "是" : "否");

    /* 在暂停期间提交任务 */
    printf("   在暂停期间提交3个任务\n");
    for (int i = 100; i < 103; i++)
    {
        int *task_id = malloc(sizeof(int));
        *task_id = i;
        thread_pool_submit(pool, print_task, task_id);
    }
    printf("   等待任务数: %zu\n", thread_pool_pending_count(pool));

    printf("   等待5秒...\n");
    sleep(5);

    printf("   恢复线程池\n");
    thread_pool_resume(pool);
    printf("   线程池已暂停: %s\n", thread_pool_is_paused(pool) ? "是" : "否");

    /* 6. 提交异常任务 */
    printf("\n6. 提交异常任务（模拟除零）\n");
    for (int i = 0; i < 3; i++)
    {
        int *task_id = malloc(sizeof(int));
        *task_id = i + 5; // 任务5会触发"异常"
        thread_pool_submit(pool, exception_task, task_id);
    }

    /* 7. 提交长时间任务 */
    printf("\n7. 提交2个长时间任务（每个3秒）\n");
    for (int i = 0; i < 2; i++)
    {
        int *task_id = malloc(sizeof(int));
        *task_id = i + 1000;
        thread_pool_submit(pool, long_task, task_id);
    }

    /* 等待所有任务完成 */
    printf("\n8. 等待所有任务完成...\n");

    int last_pending = thread_pool_pending_count(pool);
    while (last_pending > 0)
    {
        printf("   剩余任务数: %zu\n", last_pending);
        sleep(2);
        last_pending = thread_pool_pending_count(pool);
    }

    /* 额外等待确保长时间任务完成 */
    sleep(4);

    /* 显示最终结果 */
    printf("\n9. 最终统计\n");
    printf("   计算任务完成数: %d\n", completed_tasks);
    printf("   累加总和: %d\n", total_sum);
    printf("   预期总和(1+2+3+4+5): 15\n");

    /* 8. 销毁线程池 */
    printf("\n10. 销毁线程池\n");
    thread_pool_destroy(pool);
    printf("   线程池已销毁\n");

    /* 销毁结果互斥锁 */
    pthread_mutex_destroy(&result_mutex);

    printf("\n=== 线程池示例程序结束 ===\n");

    return 0;
}