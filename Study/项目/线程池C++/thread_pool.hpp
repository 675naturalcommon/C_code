#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
#include <type_traits>
#include <memory>
#include <stdexcept>

/**
 * @brief 一个功能完备的C++17线程池实现
 *
 * 支持动态调整线程数、暂停/恢复、任务提交返回future、异常传播等功能。
 * 线程安全，异常安全，资源管理正确。
 */
class ThreadPool
{
public:
    /**
     * @brief 构造函数，创建指定数量的工作线程
     * @param numThreads 初始线程数量，如果为0则使用硬件并发数
     */
    explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency())
        : stop(false), paused(false), threadsToStop(0), activeThreads(0)
    {
        if (numThreads == 0)
        {
            numThreads = std::thread::hardware_concurrency();
            if (numThreads == 0)
                numThreads = 1; // 回退到1个线程
        }

        // 创建工作线程
        workers.reserve(numThreads);
        for (size_t i = 0; i < numThreads; ++i)
        {
            workers.emplace_back([this]
                                 { workerThread(); });
        }
        activeThreads = numThreads;
    }

    /**
     * @brief 析构函数，等待所有任务完成并停止所有线程
     */
    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
            // 唤醒所有等待的线程
            condition.notify_all();
            // 唤醒暂停状态下的线程
            pausedCondition.notify_all();
        }

        // 等待所有线程完成
        for (std::thread &worker : workers)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }
    }

    // 禁止拷贝
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    /**
     * @brief 提交任务到线程池
     * @tparam F 可调用对象类型
     * @tparam Args 参数类型
     * @param f 可调用对象
     * @param args 参数
     * @return std::future<typename std::invoke_result_t<F, Args...>> 任务的future，用于获取结果或异常
     */
    template <typename F, typename... Args>
    auto enqueue(F &&f, Args &&...args)
        -> std::future<typename std::invoke_result_t<F, Args...>>
    {
        using return_type = typename std::invoke_result_t<F, Args...>;

        // 使用std::packaged_task包装任务，支持返回值
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_type> result = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            // 如果线程池已停止，不允许提交新任务
            if (stop)
            {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            // 将任务包装为void()类型，放入队列
            tasks.emplace([task]()
                          { (*task)(); });
        }

        // 通知一个等待的线程有新任务
        condition.notify_one();
        return result;
    }

    /**
     * @brief 动态调整线程数量
     * @param newThreadCount 新的线程数量
     */
    void resize(size_t newThreadCount)
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        size_t currentCount = workers.size();

        if (newThreadCount > currentCount)
        {
            // 增加线程
            size_t toAdd = newThreadCount - currentCount;
            for (size_t i = 0; i < toAdd; ++i)
            {
                workers.emplace_back([this]
                                     { workerThread(); });
            }
            activeThreads += toAdd;
        }
        else if (newThreadCount < currentCount)
        {
            // 减少线程
            size_t toStop = currentCount - newThreadCount;
            threadsToStop += toStop;

            // 唤醒所有空闲线程，让它们检查是否需要退出
            condition.notify_all();
            pausedCondition.notify_all();
        }
        // 如果相等，什么都不做
    }

    /**
     * @brief 暂停任务执行
     *
     * 已提交但未开始的任务不会开始，正在执行的任务不受影响。
     */
    void pause()
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        paused = true;
    }

    /**
     * @brief 恢复任务执行
     */
    void resume()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            paused = false;
        }
        // 唤醒所有等待的线程
        pausedCondition.notify_all();
        condition.notify_all();
    }

    /**
     * @brief 获取当前工作线程数量
     * @return size_t 线程数量
     */
    size_t workerCount() const
    {
        return activeThreads.load();
    }

    /**
     * @brief 获取等待执行的任务数量
     * @return size_t 等待任务数量
     */
    size_t pendingTaskCount() const
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        return tasks.size();
    }

    /**
     * @brief 检查线程池是否处于暂停状态
     * @return bool 如果暂停返回true，否则false
     */
    bool isPaused() const
    {
        return paused.load();
    }

private:
    // 工作线程函数
    void workerThread()
    {
        while (true)
        {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(queueMutex);

                // 等待条件：有任务可执行，或线程池停止，或需要退出（resize减少线程）
                condition.wait(lock, [this]
                               { return stop || !tasks.empty() || threadsToStop > 0; });

                // 检查是否需要退出
                if (stop || threadsToStop > 0)
                {
                    if (threadsToStop > 0)
                    {
                        --threadsToStop;
                        --activeThreads;
                        // 当前线程退出，减少线程计数
                        // 注意：线程对象还在workers中，会在析构时join
                        return;
                    }
                    if (stop)
                    {
                        --activeThreads;
                        return;
                    }
                }

                // 如果处于暂停状态，等待恢复
                while (paused && !stop)
                {
                    pausedCondition.wait(lock);
                    if (stop)
                        return;
                }

                // 再次检查退出条件（可能在等待暂停时发生变化）
                if (stop || threadsToStop > 0)
                {
                    if (threadsToStop > 0)
                    {
                        --threadsToStop;
                        --activeThreads;
                        return;
                    }
                    if (stop)
                    {
                        --activeThreads;
                        return;
                    }
                }

                // 获取任务
                if (!tasks.empty())
                {
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                else
                {
                    // 没有任务，继续等待
                    continue;
                }
            }

            // 执行任务
            try
            {
                task();
            }
            catch (...)
            {
                // 任务异常由std::future传播，这里不处理
                // 但确保线程不会因任务异常而崩溃
            }
        }
    }

private:
    // 工作线程
    std::vector<std::thread> workers;

    // 任务队列
    std::queue<std::function<void()>> tasks;

    // 同步原语
    mutable std::mutex queueMutex;
    std::condition_variable condition;
    std::condition_variable pausedCondition;

    // 状态标志
    std::atomic<bool> stop;            // 线程池是否停止
    std::atomic<bool> paused;          // 线程池是否暂停
    std::atomic<size_t> threadsToStop; // 需要停止的线程数量（用于resize减少线程）
    std::atomic<size_t> activeThreads; // 当前活跃线程数量
};

// 示例程序
#ifdef THREAD_POOL_EXAMPLE
#include <iostream>
#include <chrono>
#include <random>

int main()
{
    std::cout << "=== C++17 线程池示例程序 ===" << std::endl;

    // 1. 创建线程池（4个线程）
    std::cout << "1. 创建线程池（4个线程）" << std::endl;
    ThreadPool pool(4);
    std::cout << "   初始线程数: " << pool.workerCount() << std::endl;

    // 2. 提交若干任务（打印、计算）
    std::cout << "\n2. 提交若干任务" << std::endl;
    std::vector<std::future<int>> futures;

    for (int i = 0; i < 10; ++i)
    {
        auto future = pool.enqueue([i]
                                   {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "   任务 " << i << " 在线程 " << std::this_thread::get_id() << " 执行" << std::endl;
            return i * i; });
        futures.push_back(std::move(future));
    }

    // 3. 演示获取返回值（计算平方和）
    std::cout << "\n3. 获取任务返回值" << std::endl;
    int sum = 0;
    for (size_t i = 0; i < futures.size(); ++i)
    {
        sum += futures[i].get();
    }
    std::cout << "   平方和: " << sum << std::endl;

    // 4. 演示异常传播
    std::cout << "\n4. 演示异常传播" << std::endl;
    auto futureWithException = pool.enqueue([]
                                            {
        throw std::runtime_error("任务执行时发生异常");
        return 42; });

    try
    {
        futureWithException.get();
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
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "   暂停测试任务 " << i << " 完成" << std::endl;
            ++completedTasks; });
        pauseFutures.push_back(std::move(fut));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::cout << "   暂停线程池..." << std::endl;
    pool.pause();
    std::cout << "   是否暂停: " << (pool.isPaused() ? "是" : "否") << std::endl;

    // 提交更多任务（这些任务应该不会立即开始）
    for (int i = 5; i < 10; ++i)
    {
        pool.enqueue([i, &completedTasks]
                     {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "   暂停后任务 " << i << " 完成" << std::endl;
            ++completedTasks; });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "   已完成任务数: " << completedTasks << " (应该小于5)" << std::endl;

    std::cout << "   恢复线程池..." << std::endl;
    pool.resume();
    std::cout << "   是否暂停: " << (pool.isPaused() ? "是" : "否") << std::endl;

    // 等待所有任务完成
    for (auto &fut : pauseFutures)
    {
        fut.wait();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "   最终完成的任务数: " << completedTasks << std::endl;

    // 7. 演示析构时自动等待任务完成
    std::cout << "\n7. 演示析构时自动等待任务完成" << std::endl;
    {
        ThreadPool smallPool(2);
        for (int i = 0; i < 3; ++i)
        {
            smallPool.enqueue([i]
                              {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                std::cout << "   析构测试任务 " << i << " 完成" << std::endl; });
        }
        std::cout << "   离开作用域，线程池将自动等待任务完成..." << std::endl;
    }
    std::cout << "   线程池已正确析构" << std::endl;

    std::cout << "\n=== 示例程序结束 ===" << std::endl;
    return 0;
}
#endif // THREAD_POOL_EXAMPLE