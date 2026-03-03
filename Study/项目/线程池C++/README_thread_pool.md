# C++17 线程池 (ThreadPool)

一个功能完备的现代C++17线程池实现，支持动态调整线程数、暂停/恢复、任务提交返回future、异常传播等功能。

## 功能特性

- ✅ 线程安全，异常安全，资源管理正确
- ✅ 动态调整线程数量 (`resize()`)
- ✅ 暂停/恢复任务执行 (`pause()`/`resume()`)
- ✅ 任务提交返回 `std::future` 用于获取结果或捕获异常
- ✅ 支持任意可调用对象（函数、lambda、std::bind等）
- ✅ 完美转发参数，正确处理左值/右值
- ✅ 析构时自动等待所有任务完成
- ✅ 线程池停止后不能提交新任务（抛出异常）

## 快速开始

### 包含头文件

```cpp
#include "thread_pool.hpp"
```

### 创建线程池

```cpp
// 创建4个线程的线程池
ThreadPool pool(4);

// 使用默认构造函数（使用硬件并发数）
ThreadPool defaultPool;
```

### 提交任务

```cpp
// 提交无返回值任务
pool.enqueue([] {
    std::cout << "Hello from thread pool!" << std::endl;
});

// 提交有返回值任务
auto future = pool.enqueue([](int x, int y) {
    return x + y;
}, 10, 20);

int result = future.get(); // 获取结果：30

// 提交可能抛出异常的任务
auto futureWithException = pool.enqueue([] {
    throw std::runtime_error("Something went wrong");
    return 42;
});

try {
    futureWithException.get();
} catch (const std::exception& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
}
```

### 动态调整线程数

```cpp
std::cout << "Current threads: " << pool.workerCount() << std::endl;

// 增加到6个线程
pool.resize(6);
std::cout << "After resize to 6: " << pool.workerCount() << std::endl;

// 减少到2个线程
pool.resize(2);
std::cout << "After resize to 2: " << pool.workerCount() << std::endl;
```

### 暂停/恢复

```cpp
// 暂停线程池（已提交但未开始的任务不会开始）
pool.pause();
std::cout << "Is paused: " << pool.isPaused() << std::endl;

// 提交一些任务（这些任务不会立即开始）
for (int i = 0; i < 5; ++i) {
    pool.enqueue([i] {
        std::cout << "Task " << i << std::endl;
    });
}

// 恢复线程池
pool.resume();
std::cout << "Is paused: " << pool.isPaused() << std::endl;
```

### 查询状态

```cpp
size_t threads = pool.workerCount();      // 当前工作线程数
size_t pending = pool.pendingTaskCount(); // 等待执行的任务数量
bool paused = pool.isPaused();            // 是否处于暂停状态
```

## 编译要求

- C++17 或更高版本
- 支持多线程的编译器

### 编译命令

```bash
# Windows (MinGW/GCC)
g++ -std=c++17 -o your_program your_program.cpp -pthread

# Linux/Mac
g++ -std=c++17 -o your_program your_program.cpp -pthread

# MSVC (Visual Studio)
cl /std:c++17 /EHsc your_program.cpp
```

## 示例程序

项目中包含一个完整的示例程序 `thread_pool_example.cpp`，演示了所有功能：

```bash
# 编译示例
g++ -std=c++17 -o thread_pool_example thread_pool_example.cpp -pthread

# 运行示例
./thread_pool_example.exe  # Windows
./thread_pool_example      # Linux/Mac
```

## 实现细节

### 类设计

```cpp
class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
    ~ThreadPool();

    // 禁止拷贝
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    // 任务提交
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result_t<F, Args...>>;

    // 动态调整线程数
    void resize(size_t newThreadCount);

    // 暂停/恢复
    void pause();
    void resume();

    // 查询状态
    size_t workerCount() const;
    size_t pendingTaskCount() const;
    bool isPaused() const;
};
```

### 内部实现

1. **任务队列**: 使用 `std::queue` 存储 `std::function<void()>` 任务
2. **线程管理**: 使用 `std::vector<std::thread>` 存储工作线程
3. **同步原语**: 使用 `std::mutex` 和 `std::condition_variable` 保护共享数据
4. **状态标志**: 使用 `std::atomic` 变量确保线程安全
5. **异常安全**: 任务异常通过 `std::future` 传播，线程池本身不会崩溃

### 工作线程逻辑

每个工作线程循环执行以下操作：

1. 等待条件变量（有任务、线程池停止、或需要退出）
2. 检查是否需要退出（停止标志或resize减少线程）
3. 检查是否处于暂停状态
4. 从队列获取任务并执行
5. 捕获任务异常（通过std::future传播）

## 注意事项

1. **线程安全**: 所有公共成员函数都是线程安全的
2. **异常安全**: 任务异常不会导致线程池崩溃
3. **资源管理**: 析构函数确保所有线程正确join
4. **性能**: 使用条件变量避免忙等待
5. **灵活性**: 支持任意参数数量和返回类型

## 许可证

本项目代码可自由使用、修改和分发。

## 作者

C++黑马学习项目 - 线程池实现
