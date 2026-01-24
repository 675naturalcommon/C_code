#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <atomic>

// 工具函数：获取带时间戳的输出
std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);
    std::tm bt;
    localtime_s(&bt, &timer);

    std::ostringstream oss;
    oss << std::put_time(&bt, "%H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

// ============================================================================
// 1. 读者优先解决方案 (Reader Priority)
// 优点: 读者可以并发访问，提高读取效率
// 缺点: 可能导致写者饥饿（writer starvation）
// ============================================================================
class ReaderPriorityRW {
private:
    std::shared_mutex rw_mutex;      // 读写互斥锁
    std::mutex count_mutex;          // 保护读者计数的互斥锁
    int reader_count = 0;            // 当前活跃读者数量
    int data = 0;                    // 共享数据
    std::atomic<int> total_reads{0};
    std::atomic<int> total_writes{0};

public:
    void read(int reader_id) {
        // 增加读者计数
        {
            std::unique_lock<std::mutex> lock(count_mutex);
            reader_count++;
            if (reader_count == 1) {
                rw_mutex.lock_shared();  // 第一个读者获取共享锁
            }
        }

        // 临界区：读取数据
        total_reads.fetch_add(1, std::memory_order_relaxed);
        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 开始读取，数据=" << data
                  << "，活跃读者数=" << reader_count << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 读取完成，数据=" << data << std::endl;

        // 减少读者计数
        {
            std::unique_lock<std::mutex> lock(count_mutex);
            reader_count--;
            if (reader_count == 0) {
                rw_mutex.unlock_shared();  // 最后一个读者释放共享锁
            }
        }
    }

    void write(int writer_id) {
        std::unique_lock lock(rw_mutex);  // 获取独占锁

        // 临界区：写入数据
        total_writes.fetch_add(1, std::memory_order_relaxed);
        data++;
        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 开始写入，新数据=" << data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 写入完成，数据=" << data << std::endl;
    }

    void print_stats() {
        std::cout << "\n统计信息: 总读取次数=" << total_reads.load()
                  << ", 总写入次数=" << total_writes.load() << std::endl;
    }
};

// ============================================================================
// 2. 写者优先解决方案 (Writer Priority)
// 优点: 防止写者饥饿，保证写操作能及时执行
// 缺点: 可能导致读者饥饿（reader starvation）
// ============================================================================
class WriterPriorityRW {
private:
    std::mutex mutex;
    std::condition_variable read_cv;
    std::condition_variable write_cv;

    int active_readers = 0;          // 当前活跃读者数
    int waiting_writers = 0;         // 等待的写者数
    int active_writers = 0;          // 当前活跃写者数
    int data = 0;
    std::atomic<int> total_reads{0};
    std::atomic<int> total_writes{0};

public:
    void read(int reader_id) {
        std::unique_lock<std::mutex> lock(mutex);

        // 如果有写者在等待或活跃，读者需要等待
        read_cv.wait(lock, [this]() {
            return waiting_writers == 0 && active_writers == 0;
        });

        active_readers++;
        lock.unlock();

        // 临界区：读取数据
        total_reads.fetch_add(1, std::memory_order_relaxed);
        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 开始读取，数据=" << data
                  << "，活跃读者=" << active_readers << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 读取完成" << std::endl;

        lock.lock();
        active_readers--;

        // 如果最后一个读者完成且有写者在等待，通知写者
        if (active_readers == 0 && waiting_writers > 0) {
            write_cv.notify_one();
        }
    }

    void write(int writer_id) {
        std::unique_lock<std::mutex> lock(mutex);
        waiting_writers++;

        // 等待没有活跃的读者和写者
        write_cv.wait(lock, [this]() {
            return active_readers == 0 && active_writers == 0;
        });

        waiting_writers--;
        active_writers++;
        lock.unlock();

        // 临界区：写入数据
        total_writes.fetch_add(1, std::memory_order_relaxed);
        data++;
        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 开始写入，新数据=" << data
                  << "，等待写者=" << waiting_writers << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 写入完成" << std::endl;

        lock.lock();
        active_writers--;

        // 优先通知其他等待的写者
        if (waiting_writers > 0) {
            write_cv.notify_one();
        } else {
            read_cv.notify_all();  // 没有等待写者，通知所有读者
        }
    }

    void print_stats() const {
        std::cout << "\n统计信息: 总读取次数=" << total_reads.load()
                  << ", 总写入次数=" << total_writes.load() << std::endl;
    }
};

// ============================================================================
// 3. 公平解决方案 (Fair Solution)
// 使用FIFO队列确保先到先服务，避免饥饿问题
// ============================================================================
class FairReaderWriter {
private:
    std::mutex mutex;
    std::condition_variable cv;

    int active_readers = 0;
    bool writer_active = false;
    int waiting_count = 0;           // 等待的线程总数
    int data = 0;
    std::atomic<int> total_reads{0};
    std::atomic<int> total_writes{0};

public:
    void read(int reader_id) {
        std::unique_lock<std::mutex> lock(mutex);
        waiting_count++;

        // 等待写者完成
        cv.wait(lock, [this]() {
            return !writer_active;
        });

        waiting_count--;
        active_readers++;
        lock.unlock();

        // 临界区：读取数据
        total_reads.fetch_add(1, std::memory_order_relaxed);
        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 开始读取，数据=" << data
                  << "，活跃读者=" << active_readers << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 读取完成" << std::endl;

        lock.lock();
        active_readers--;

        if (active_readers == 0) {
            cv.notify_all();  // 通知等待的写者
        }
    }

    void write(int writer_id) {
        std::unique_lock<std::mutex> lock(mutex);
        waiting_count++;

        // 等待没有活跃读者和写者
        cv.wait(lock, [this]() {
            return active_readers == 0 && !writer_active;
        });

        waiting_count--;
        writer_active = true;
        lock.unlock();

        // 临界区：写入数据
        total_writes.fetch_add(1, std::memory_order_relaxed);
        data++;
        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 开始写入，新数据=" << data
                  << "，等待线程=" << waiting_count << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));

        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 写入完成" << std::endl;

        lock.lock();
        writer_active = false;
        cv.notify_all();  // 公平通知所有等待线程
    }

    void print_stats() const {
        std::cout << "\n统计信息: 总读取次数=" << total_reads.load()
                  << ", 总写入次数=" << total_writes.load() << std::endl;
    }
};

// ============================================================================
// 4. 使用C++17 shared_mutex的简洁实现
// 最简单高效的实现方式，推荐用于生产环境
// ============================================================================
class SimpleReaderWriter {
private:
    mutable std::shared_mutex mutex;
    int data = 0;
    std::atomic<int> total_reads{0};
    std::atomic<int> total_writes{0};

public:
    void read(int reader_id) {
        std::shared_lock lock(mutex);  // 获取共享锁，允许多个读者

        total_reads.fetch_add(1, std::memory_order_relaxed);
        std::cout << "[" << get_timestamp() << "] 读者 " << reader_id
                  << " 读取数据=" << data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void write(int writer_id) {
        std::unique_lock lock(mutex);  // 获取独占锁，只允许一个写者

        total_writes.fetch_add(1, std::memory_order_relaxed);
        data++;
        std::cout << "[" << get_timestamp() << "] 写者 " << writer_id
                  << " 写入数据=" << data << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    void print_stats() const {
        std::cout << "\n统计信息: 总读取次数=" << total_reads.load()
                  << ", 总写入次数=" << total_writes.load() << std::endl;
    }
};

// ============================================================================
// 测试函数
// ============================================================================
template<typename RWType>
void run_test(const std::string& test_name, RWType& rw_system,
              int num_readers, int num_writers,
              int reads_per_reader, int writes_per_writer) {
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "测试: " << test_name << std::endl;
    std::cout << "配置: " << num_readers << "个读者(每个读" << reads_per_reader << "次), "
              << num_writers << "个写者(每个写" << writes_per_writer << "次)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::vector<std::thread> threads;
    auto start_time = std::chrono::steady_clock::now();

    // 创建读者线程
    for (int i = 0; i < num_readers; ++i) {
        threads.emplace_back([&rw_system, i, reads_per_reader]() {
            for (int j = 0; j < reads_per_reader; ++j) {
                rw_system.read(i + 1);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        });
    }

    // 创建写者线程
    for (int i = 0; i < num_writers; ++i) {
        threads.emplace_back([&rw_system, i, writes_per_writer, num_readers]() {
            for (int j = 0; j < writes_per_writer; ++j) {
                rw_system.write(i + 1);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    // 等待所有线程完成
    for (auto& thread : threads) {
        thread.join();
    }

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    rw_system.print_stats();
    std::cout << "总用时: " << duration.count() << " 毫秒" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

// ============================================================================
// 主函数
// ============================================================================
int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║          读者-写者问题 (Reader-Writer Problem)                  ║\n";
    std::cout << "║                   多种实现方案演示                               ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n";

    // 测试配置
    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;
    const int READS_PER_READER = 3;
    const int WRITES_PER_WRITER = 2;

    // 1. 测试读者优先方案
    {
        ReaderPriorityRW rw_system;
        run_test("读者优先方案 (Reader Priority)", rw_system,
                 NUM_READERS, NUM_WRITERS, READS_PER_READER, WRITES_PER_WRITER);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // 2. 测试写者优先方案
    {
        WriterPriorityRW rw_system;
        run_test("写者优先方案 (Writer Priority)", rw_system,
                 NUM_READERS, NUM_WRITERS, READS_PER_READER, WRITES_PER_WRITER);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // 3. 测试公平方案
    {
        FairReaderWriter rw_system;
        run_test("公平方案 (Fair Solution)", rw_system,
                 NUM_READERS, NUM_WRITERS, READS_PER_READER, WRITES_PER_WRITER);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // 4. 测试简洁方案
    {
        SimpleReaderWriter rw_system;
        run_test("简洁方案 (Simple - shared_mutex)", rw_system,
                 NUM_READERS, NUM_WRITERS, READS_PER_READER, WRITES_PER_WRITER);
    }

    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                     所有测试完成!                                ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n";
    std::cout << "\n方案对比:\n";
    std::cout << "1. 读者优先: 读者可并发，但写者可能饥饿\n";
    std::cout << "2. 写者优先: 写者优先执行，但读者可能饥饿\n";
    std::cout << "3. 公平方案: FIFO策略，避免饥饿，但效率稍低\n";
    std::cout << "4. 简洁方案: 使用标准库，代码简洁，推荐生产使用\n";
    std::cout << std::endl;

    return 0;
}
