#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

using namespace std;

class CircularBuffer {
public:
    CircularBuffer(int sz) : buffer(sz), size(sz), front(0), rear(0), count(0) {}

    // 尝试放入一个元素（阻塞直到有空位）
    void put(int item) {
        unique_lock<mutex> lk(mtx);
        // 如果满了就等 not_full
        not_full.wait(lk, [this]() { return count < size; });

        // 放入
        buffer[rear] = item;
        rear = (rear + 1) % size;
        ++count;

        // 唤醒等待的消费者（有东西可取了）
        not_empty.notify_one();
        // unlock 在 unique_lock 作用域结束时自动释放
    }

    // 尝试取出一个元素（阻塞直到有元素）
    int take() {
        unique_lock<mutex> lk(mtx);
        not_empty.wait(lk, [this]() { return count > 0; });

        int item = buffer[front];
        front = (front + 1) % size;
        --count;

        // 唤醒等待的生产者（有空位了）
        not_full.notify_one();
        return item;
    }

    // 下面提供只读接口供实验打印队列状态（可选）
    void snapshot(int &out_front, int &out_rear, int &out_count) {
        lock_guard<mutex> lk(mtx);
        out_front = front;
        out_rear = rear;
        out_count = count;
    }


private:
    vector<int> buffer;      // 存储元素的数组
    int size;               // 缓冲区容量
    int front;              // 队首指针（消费者取数据的位置）
    int rear;               // 队尾指针（生产者放数据的位置）
    int count;              // 当前元素数量
    mutex mtx;              // 互斥锁，保护共享数据
    condition_variable not_full;   // 条件变量：缓冲区不满
    condition_variable not_empty;  // 条件变量：缓冲区不空
};

// 全局统计（用于让所有线程在处理完 total_items 后自然结束）
atomic<int> produced_count(0);
atomic<int> consumed_count(0);

void producer_thread(CircularBuffer &cb, int id, int total_items, int produce_delay_ms) {
    while (true) {
        int cur_prod = ++produced_count; // 先递增，用来产生产品编号（1..）
        if (cur_prod > total_items) {
            // 超过总量则不真正生产，结束线程（也可选择把超过的放回计数）
            break;
        }
        int item = cur_prod; // 产品编号
        // 生成产品（模拟耗时）
        this_thread::sleep_for(chrono::milliseconds(produce_delay_ms));

        // 按流程：获取锁 -> 若满则等待 -> 入队 -> notify -> 释放锁
        cb.put(item);

        // 打印日志（加锁避免输出混乱）
        {
            static mutex print_mtx;
            lock_guard<mutex> print_lock(print_mtx);
            int f, r, c;
            cb.snapshot(f, r, c);
            cout << "[生产者 " << id << "] 生产了 item=" << item
                 << " | 缓冲区状态: [队尾=" << r << ", 队首=" << f << ", 数量=" << c << "]\n";
        }
    }
    {
        static mutex print_mtx;
        lock_guard<mutex> print_lock(print_mtx);
        cout << "[生产者 " << id << "] 已完成工作\n";
    }
}

void consumer_thread(CircularBuffer &cb, int id, int total_items, int consume_delay_ms) {
    while (true) {
        // 在消费前检查是否还有剩余要被消费的项
        int cur_consumed = consumed_count.load();
        if (cur_consumed >= total_items) break;

        // 获取并消费一个元素（会在队列空时阻塞等待）
        int item = cb.take();

        // 模拟消费处理耗时
        this_thread::sleep_for(chrono::milliseconds(consume_delay_ms));

        int newc = ++consumed_count;

        // 打印日志（加锁避免输出混乱）
        {
            static mutex print_mtx;
            lock_guard<mutex> print_lock(print_mtx);
            int f, r, c;
            cb.snapshot(f, r, c);
            cout << "           [消费者 " << id << "] 消费了 item=" << item
                 << " | 缓冲区状态: [队尾=" << r << ", 队首=" << f << ", 数量=" << c << "]"
                 << " | 总消费数=" << newc << "\n";
        }

        if (newc >= total_items) break;
    }
    {
        static mutex print_mtx;
        lock_guard<mutex> print_lock(print_mtx);
        cout << "           [消费者 " << id << "] 已完成工作\n";
    }
}

int main() {

    int producer_count = 3;
    int consumer_count = 2;
    int buffer_size = 5;
    int total_items = 20;           // 本次实验将生产并被消费的总产品数（便于结束）
    int produce_delay_ms = 150;     // 生产耗时（用于模拟）
    int consume_delay_ms = 300;     // 消费耗时（用于模拟）

    cout << "\n========================================\n";
    cout << "===    生产者-消费者算法演示    ===\n";
    cout << "========================================\n";
    cout << "生产者数量: " << producer_count << "\n";
    cout << "消费者数量: " << consumer_count << "\n";
    cout << "缓冲区大小: " << buffer_size << "\n";
    cout << "产品总数量: " << total_items << "\n";
    cout << "========================================\n\n";

    CircularBuffer cb(buffer_size);

    // 启动生产者线程
    vector<thread> producers;
    for (int i = 0; i < producer_count; ++i) {
        producers.emplace_back(producer_thread, std::ref(cb), i+1, total_items, produce_delay_ms);
    }

    // 启动消费者线程
    vector<thread> consumers;
    for (int i = 0; i < consumer_count; ++i) {
        consumers.emplace_back(consumer_thread, std::ref(cb), i+1, total_items, consume_delay_ms);
    }

    // 等待所有线程结束
    for (auto &t : producers) if (t.joinable()) t.join();
    // 有可能生产线程结束后，消费者还在消费队列中剩余项，继续等待
    for (auto &t : consumers) if (t.joinable()) t.join();

    cout << "\n========================================\n";
    cout << "===      实验完成！所有任务完成      ===\n";
    cout << "========================================\n";
    return 0;
}
