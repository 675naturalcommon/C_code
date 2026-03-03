# POSIX线程池实现 (C语言)

一个功能完备的C语言线程池实现，基于POSIX线程(pthread)库。支持动态调整线程数、暂停/恢复、任务提交等功能。

## 功能特性

- ✅ 线程池创建与销毁
- ✅ 任务提交与执行
- ✅ 动态调整线程数量
- ✅ 暂停与恢复线程池
- ✅ 线程安全的任务队列
- ✅ 错误处理与资源管理
- ✅ 避免内存泄漏
- ✅ 支持异常任务处理

## 文件结构

```
线程池C/
├── thread_pool.h     # 头文件（接口声明）
├── thread_pool.c     # 实现文件
├── example.c         # 完整示例程序
├── simple_test.c     # 简单测试程序
└── README.md         # 本文档
```

## 编译说明

### 在Linux环境下编译

```bash
# 编译示例程序
gcc -pthread thread_pool.c example.c -o thread_pool_example

# 编译简单测试程序
gcc -pthread thread_pool.c simple_test.c -o simple_test

# 运行程序
./thread_pool_example
./simple_test
```

### 在Windows环境下编译（使用MinGW或Cygwin）

```bash
# 需要安装pthread库
gcc -pthread thread_pool.c example.c -o thread_pool_example.exe
```

## API接口

### 头文件包含

```c
#include "thread_pool.h"
```

### 数据类型

```c
// 线程池句柄（不透明指针）
typedef struct thread_pool_s thread_pool_t;

// 任务节点结构体
typedef struct task_s {
    void (*function)(void*);   // 任务函数指针
    void* arg;                 // 任务函数参数
    struct task_s* next;       // 链表下一节点指针
} task_t;
```

### 函数接口

#### 创建与销毁

```c
// 创建线程池
thread_pool_t* thread_pool_create(size_t num_threads);

// 销毁线程池
void thread_pool_destroy(thread_pool_t* pool);
```

#### 任务管理

```c
// 提交任务到线程池
int thread_pool_submit(thread_pool_t* pool, void (*function)(void*), void* arg);
```

#### 线程池控制

```c
// 动态调整线程池大小
int thread_pool_resize(thread_pool_t* pool, size_t new_thread_count);

// 暂停线程池
void thread_pool_pause(thread_pool_t* pool);

// 恢复线程池
void thread_pool_resume(thread_pool_t* pool);
```

#### 状态查询

```c
// 获取当前工作线程数量
size_t thread_pool_worker_count(thread_pool_t* pool);

// 获取等待执行的任务数量
size_t thread_pool_pending_count(thread_pool_t* pool);

// 检查线程池是否处于暂停状态
bool thread_pool_is_paused(thread_pool_t* pool);
```

## 使用示例

### 基本用法

```c
#include "thread_pool.h"
#include <stdio.h>
#include <unistd.h>

// 任务函数
void my_task(void* arg) {
    int id = *(int*)arg;
    printf("执行任务 %d\n", id);
    sleep(1);
    free(arg);
}

int main() {
    // 1. 创建线程池（4个工作线程）
    thread_pool_t* pool = thread_pool_create(4);

    // 2. 提交10个任务
    for (int i = 0; i < 10; i++) {
        int* task_id = malloc(sizeof(int));
        *task_id = i;
        thread_pool_submit(pool, my_task, task_id);
    }

    // 3. 等待任务完成
    sleep(3);

    // 4. 动态调整线程数
    thread_pool_resize(pool, 6);  // 增加到6个线程
    sleep(1);
    thread_pool_resize(pool, 2);  // 减少到2个线程

    // 5. 暂停和恢复
    thread_pool_pause(pool);
    sleep(2);
    thread_pool_resume(pool);

    // 6. 销毁线程池
    thread_pool_destroy(pool);

    return 0;
}
```

### 处理计算结果

```c
#include "thread_pool.h"
#include <stdio.h>
#include <pthread.h>

// 共享结果变量
static int total_sum = 0;
static pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;

// 计算任务
void compute_task(void* arg) {
    int value = *(int*)arg;

    pthread_mutex_lock(&sum_mutex);
    total_sum += value;
    pthread_mutex_unlock(&sum_mutex);

    free(arg);
}

int main() {
    thread_pool_t* pool = thread_pool_create(4);

    // 提交计算任务
    for (int i = 1; i <= 100; i++) {
        int* value = malloc(sizeof(int));
        *value = i;
        thread_pool_submit(pool, compute_task, value);
    }

    // 等待所有任务完成
    while (thread_pool_pending_count(pool) > 0) {
        sleep(1);
    }

    printf("总和: %d\n", total_sum);  // 输出: 5050

    thread_pool_destroy(pool);
    pthread_mutex_destroy(&sum_mutex);

    return 0;
}
```

## 实现细节

### 线程池结构

```c
struct thread_pool_s {
    pthread_t* threads;            // 线程数组
    size_t thread_count;           // 当前线程数量
    size_t max_threads;            // 线程数组容量
    task_t* task_queue_head;       // 任务队列头指针
    task_t* task_queue_tail;       // 任务队列尾指针
    size_t pending_count;          // 等待执行的任务数
    pthread_mutex_t queue_mutex;   // 保护任务队列和状态
    pthread_cond_t queue_cond;     // 通知线程取任务
    pthread_cond_t pause_cond;     // 用于暂停等待
    bool stop;                     // 停止标志
    bool paused;                   // 暂停标志
    size_t threads_to_stop;        // 需要退出的线程数
};
```

### 工作线程逻辑

1. 加锁访问共享数据
2. 检查退出条件（停止或动态缩减）
3. 检查暂停状态
4. 从队列取出任务
5. 解锁并执行任务
6. 释放任务内存
7. 循环等待新任务

### 线程安全

- 所有共享数据访问都通过互斥锁保护
- 条件变量用于线程间通信
- 避免死锁和竞态条件
- 使用循环检查避免虚假唤醒

### 内存管理

- 动态分配的内存都会正确释放
- 错误路径有完整的资源回滚
- 任务节点在执行后立即释放

## 注意事项

1. **线程安全**: 线程池本身是线程安全的，可以在多个线程中调用其接口函数
2. **任务函数**: 任务函数应该避免长时间阻塞，否则会影响其他任务执行
3. **参数内存**: 任务参数的内存由调用者分配，在线程池中释放
4. **异常处理**: 任务函数中的异常不会影响线程池其他线程
5. **资源清理**: 确保在程序退出前销毁线程池

## 性能考虑

1. **锁粒度**: 尽量减少锁的持有时间
2. **任务队列**: 使用链表实现，入队出队操作高效
3. **线程唤醒**: 使用条件变量避免忙等待
4. **动态调整**: 线程增减是异步的，不影响正在执行的任务

## 测试验证

项目包含两个测试程序：

1. **example.c**: 完整的功能演示，包括：
   - 创建线程池
   - 提交普通任务
   - 计算任务和共享变量
   - 动态调整线程数
   - 暂停和恢复
   - 异常任务处理
   - 长时间任务

2. **simple_test.c**: 简单的功能验证，快速测试核心功能

## 许可证

本项目代码可以自由使用、修改和分发。

## 作者

C语言线程池实现 - 基于POSIX线程库
