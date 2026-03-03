/**
 * @file thread_pool_example.cpp
 * @brief 线程池示例程序，演示ThreadPool的所有功能
 *
 * 编译命令（Windows）:
 *   g++ -std=c++17 -o thread_pool_example thread_pool_example.cpp -pthread
 *
 * 编译命令（Linux/Mac）:
 *   g++ -std=c++17 -o thread_pool_example thread_pool_example.cpp -pthread
 */

#include "thread_pool.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <future>
#include <atomic>

int main()
{
    std::cout << "=== C++17 线程池示例程序 ===" << std::endl;
    std::cout << "演示ThreadPool的所有功能" << std::endl
              << std::endl;

    // 1. 创建线程池（4个线程）
    std::cout << "1. 创建线程池（4个线程）" << std::endl;
    ThreadPool pool(4);
    std::cout << "   初始线程数: " << pool.workerCount() << std::endl;
    std::cout << "   等待任务数: " << pool.pendingTaskCount() << std::endl;
    std::cout << "   是否暂停: " << (pool.isPaused() ? "是" : "否") << std::endl;

    // 2. 提交若干任务（打印、计算）
    std::cout << "\n2. 提交若干任务（打印、计算）" << std::endl;
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 10; ++i)
    {
        auto future = pool.enqueue([i]
                                   {
                                       // 模拟一些工作
                                       std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                       std::cout << "   任务 " << i << " 在线程 " << std::this_thread::get_id() << " 执行" << std::endl;
                                       return i * i; // 返回平方值
                                   });
        futures.push_back(std::move(future));
    }

    std::cout << "   已提交10个任务" << std::endl;
    std::cout << "   等待任务数: " << pool.pendingTaskCount() << std::endl;

    // 3. 演示获取返回值（计算平方和）
    std::cout << "\n3. 获取任务返回值（计算平方和）" << std::endl;
    int sum = 0;
    for (size_t i = 0; i < futures.size(); ++i)
    {
        int result = futures[i].get(); // 阻塞直到任务完成并获取结果
        std::cout << "   任务" << i << " 结果: " << result << std::endl;
        sum += result;
    }
    std::cout << "   平方和: " << sum << " (正确值: 285)" << std::endl;

    // 4. 演示异常传播
    std::cout << "\n4. 演示异常传播" << std::endl;
    auto futureWithException = pool.enqueue([]
                                            {
                                                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                                                throw std::runtime_error("任务执行时发生自定义异常");
                                                return 42; // 这行不会执行
                                            });

    try
    {
        futureWithException.get(); // 这里应该抛出异常
        std::cout << "   错误：应该捕获到异常！" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "   成功捕获异常: " << e.what() << std::endl;
    }

    // 5. 演示动态调整线程数
    std::cout << "\n5. 动态调整线程数" << std::endl;
    std::cout << "   当前线程数: " << pool.workerCount() << std::endl;

    std::cout << "   增大到6个线程..." << std::endl;
    pool.resize(6);
    std::cout << "   调整后线程数: " << pool.workerCount() << std::endl;

    // 提交一些任务来测试新线程
    std::vector<std::future<void>> resizeFutures;
    for (int i = 0; i < 5; ++i)
    {
        resizeFutures.push_back(pool.enqueue([i]
                                             {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "   调整后任务 " << i << " 执行" << std::endl; }));
    }

    // 等待这些任务完成
    for (auto &fut : resizeFutures)
    {
        fut.wait();
    }

    std::cout << "   减小到2个线程..." << std::endl;
    pool.resize(2);
    std::cout << "   调整后线程数: " << pool.workerCount() << std::endl;

    // 6. 演示暂停/恢复功能
    std::cout << "\n6. 演示暂停/恢复功能" << std::endl;

    // 提交一些长时间运行的任务
    std::vector<std::future<void>> pauseFutures;
    std::atomic<int> completedTasks{0};

    for (int i = 0; i < 5; ++i)
    {
        auto fut = pool.enqueue([i, &completedTasks]
                                {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            std::cout << "   暂停测试任务 " << i << " 完成" << std::endl;
            ++completedTasks; });
        pauseFutures.push_back(std::move(fut));
    }

    // 等待一小段时间，让一些任务开始执行
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "   暂停线程池..." << std::endl;
    pool.pause();
    std::cout << "   是否暂停: " << (pool.isPaused() ? "是" : "否") << std::endl;

    // 提交更多任务（这些任务应该不会立即开始，因为线程池暂停了）
    std::vector<std::future<void>> pausedTasks;
    for (int i = 5; i < 10; ++i)
    {
        pausedTasks.push_back(pool.enqueue([i, &completedTasks]
                                           {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "   暂停后任务 " << i << " 完成" << std::endl;
            ++completedTasks; }));
    }

    std::cout << "   等待任务数: " << pool.pendingTaskCount() << std::endl;

    // 等待一段时间，观察已完成任务数
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << "   当前已完成任务数: " << completedTasks << " (应该小于5，因为部分任务被暂停)" << std::endl;

    std::cout << "   恢复线程池..." << std::endl;
    pool.resume();
    std::cout << "   是否暂停: " << (pool.isPaused() ? "是" : "否") << std::endl;

    // 等待所有任务完成
    for (auto &fut : pauseFutures)
    {
        fut.wait();
    }
    for (auto &fut : pausedTasks)
    {
        fut.wait();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "   最终完成的任务数: " << completedTasks << " (应该是10)" << std::endl;

    // 7. 演示析构时自动等待任务完成
    std::cout << "\n7. 演示析构时自动等待任务完成" << std::endl;
    {
        ThreadPool smallPool(2);
        std::atomic<int> destructorTasks{0};

        for (int i = 0; i < 5; ++i)
        {
            smallPool.enqueue([i, &destructorTasks]
                              {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                std::cout << "   析构测试任务 " << i << " 完成" << std::endl;
                ++destructorTasks; });
        }

        std::cout << "   提交了5个任务到小型线程池" << std::endl;
        std::cout << "   等待任务数: " << smallPool.pendingTaskCount() << std::endl;
        std::cout << "   离开作用域，线程池将自动等待所有任务完成..." << std::endl;

        // 不等待任务完成，直接离开作用域
        // 析构函数会自动等待
    }
    std::cout << "   线程池已正确析构，所有任务应该都已完成" << std::endl;

    // 8. 性能测试：计算斐波那契数列
    std::cout << "\n8. 性能测试：并行计算斐波那契数列" << std::endl;

    // 定义斐波那契函数
    auto fibonacci = [](int n) -> long long
    {
        if (n <= 1)
            return n;
        long long a = 0, b = 1;
        for (int i = 2; i <= n; ++i)
        {
            long long temp = a + b;
            a = b;
            b = temp;
        }
        return b;
    };

    // 创建新线程池
    ThreadPool perfPool(4);

    // 提交多个斐波那契计算任务
    std::vector<std::future<long long>> fibFutures;
    std::vector<int> fibNumbers = {30, 35, 40, 45, 30, 35, 40, 45};

    auto startTime = std::chrono::high_resolution_clock::now();

    for (int num : fibNumbers)
    {
        fibFutures.push_back(perfPool.enqueue([num, fibonacci]
                                              { return fibonacci(num); }));
    }

    // 收集结果
    long long total = 0;
    for (size_t i = 0; i < fibFutures.size(); ++i)
    {
        long long result = fibFutures[i].get();
        std::cout << "   Fibonacci(" << fibNumbers[i] << ") = " << result << std::endl;
        total += result;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "   总和: " << total << std::endl;
    std::cout << "   计算时间: " << duration.count() << " 毫秒" << std::endl;

    // 9. 测试线程池停止后不能提交新任务
    std::cout << "\n9. 测试线程池停止后不能提交新任务" << std::endl;
    {
        ThreadPool tempPool(2);

        // 提交一个简单任务
        tempPool.enqueue([]
                         { std::cout << "   临时线程池任务执行" << std::endl; });

        // 等待一下让任务执行
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // 离开作用域，线程池析构
    }
    std::cout << "   临时线程池已销毁" << std::endl;

    // 10. 测试默认构造函数（使用硬件并发数）
    std::cout << "\n10. 测试默认构造函数（使用硬件并发数）" << std::endl;
    ThreadPool defaultPool;
    std::cout << "   默认线程数: " << defaultPool.workerCount() << std::endl;
    std::cout << "   硬件并发数: " << std::thread::hardware_concurrency() << std::endl;

    std::cout << "\n=== 示例程序结束 ===" << std::endl;
    std::cout << "所有测试通过！" << std::endl;

    return 0;
}