/**
 * @file simple_test.c
 * @brief 线程池简单测试程序
 *
 * 快速验证线程池的基本功能
 */

#include "thread_pool.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/* 测试计数器 */
static int task_counter = 0;
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief 简单的测试任务
 */
void test_task(void *arg)
{
    int task_id = *(int *)arg;

    pthread_mutex_lock(&counter_mutex);
    task_counter++;
    pthread_mutex_unlock(&counter_mutex);

    printf("任务 %d 完成 (总计: %d)\n", task_id, task_counter);

    free(arg);
}

int main()
{
    printf("=== 线程池简单测试 ===\n\n");

    /* 1. 创建线程池 */
    printf("1. 创建包含3个线程的线程池\n");
    thread_pool_t *pool = thread_pool_create(3);
    if (pool == NULL)
    {
        fprintf(stderr, "创建线程池失败\n");
        return 1;
    }
    printf("   当前线程数: %zu\n", thread_pool_worker_count(pool));

    /* 2. 提交10个任务 */
    printf("\n2. 提交10个任务\n");
    for (int i = 0; i < 10; i++)
    {
        int *task_id = malloc(sizeof(int));
        *task_id = i;
        if (thread_pool_submit(pool, test_task, task_id) != 0)
        {
            fprintf(stderr, "提交任务 %d 失败\n", i);
            free(task_id);
        }
    }
    printf("   等待任务数: %zu\n", thread_pool_pending_count(pool));

    /* 等待任务完成 */
    sleep(3);

    /* 3. 测试暂停/恢复 */
    printf("\n3. 测试暂停/恢复\n");
    thread_pool_pause(pool);
    printf("   线程池已暂停: %s\n", thread_pool_is_paused(pool) ? "是" : "否");

    /* 在暂停期间提交任务 */
    int *paused_task = malloc(sizeof(int));
    *paused_task = 100;
    thread_pool_submit(pool, test_task, paused_task);
    printf("   在暂停期间提交任务100，等待任务数: %zu\n", thread_pool_pending_count(pool));

    sleep(2);
    printf("   等待2秒后，任务100应该还没有执行\n");

    thread_pool_resume(pool);
    printf("   恢复线程池\n");

    sleep(1);
    printf("   恢复后等待1秒，任务100应该已执行\n");

    /* 4. 测试动态调整线程数 */
    printf("\n4. 测试动态调整线程数\n");
    printf("   当前线程数: %zu\n", thread_pool_worker_count(pool));

    printf("   增加到5个线程...\n");
    thread_pool_resize(pool, 5);
    sleep(1);
    printf("   调整后线程数: %zu\n", thread_pool_worker_count(pool));

    printf("   减少到2个线程...\n");
    thread_pool_resize(pool, 2);
    sleep(2); // 给线程退出的时间
    printf("   调整后线程数: %zu (可能需要更多时间才能减少)\n", thread_pool_worker_count(pool));

    /* 5. 提交更多任务 */
    printf("\n5. 再提交5个任务\n");
    for (int i = 10; i < 15; i++)
    {
        int *task_id = malloc(sizeof(int));
        *task_id = i;
        thread_pool_submit(pool, test_task, task_id);
    }

    /* 等待所有任务完成 */
    printf("\n6. 等待所有任务完成...\n");
    while (thread_pool_pending_count(pool) > 0)
    {
        printf("   剩余任务数: %zu\n", thread_pool_pending_count(pool));
        sleep(1);
    }

    sleep(1); // 确保最后一批任务完成

    /* 6. 最终统计 */
    printf("\n7. 最终统计\n");
    printf("   总完成任务数: %d\n", task_counter);
    printf("   预期完成数: 16 (10个初始 + 1个暂停期间 + 5个额外)\n");

    /* 7. 销毁线程池 */
    printf("\n8. 销毁线程池\n");
    thread_pool_destroy(pool);
    printf("   线程池已销毁\n");

    pthread_mutex_destroy(&counter_mutex);

    printf("\n=== 测试完成 ===\n");

    return 0;
}