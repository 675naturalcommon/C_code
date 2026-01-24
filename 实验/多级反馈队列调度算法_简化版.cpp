#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// ==================== 基础数据结构实现 ====================

// 链表节点
template<typename T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(T val) : data(val), next(nullptr) {}
};

// 队列（基于链表）
template<typename T>
class MyQueue {
    ListNode<T>* front = nullptr;
    ListNode<T>* rear = nullptr;
    int count = 0;

public:
    ~MyQueue() { while (!empty()) pop(); }

    bool empty() const { return front == nullptr; }
    int size() const { return count; }

    T front_val() {
        if (empty()) {
            static T defaultVal;
            return defaultVal;
        }
        return front->data;
    }

    void push(T val) {
        ListNode<T>* node = new ListNode<T>(val);
        if (rear) {
            rear->next = node;
        } else {
            front = node;
        }
        rear = node;
        count++;
    }

    void pop() {
        if (empty()) return;
        ListNode<T>* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        count--;
    }

    // 遍历队列（用于显示状态）
    void traverse(void (*func)(T, int)) {
        ListNode<T>* cur = front;
        int idx = 1;
        while (cur) {
            func(cur->data, idx++);
            cur = cur->next;
        }
    }
};

// 动态数组
template<typename T>
class MyVector {
    T* data;
    int capacity;
    int length;

public:
    MyVector() : data(new T[10]), capacity(10), length(0) {}
    ~MyVector() { delete[] data; }

    T& operator[](int i) { return data[i]; }
    const T& operator[](int i) const { return data[i]; }
    int size() const { return length; }
    bool empty() const { return length == 0; }

    void push_back(const T& val) {
        if (length >= capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < length; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        data[length++] = val;
    }

    // 冒泡排序
    void sort(bool (*cmp)(const T&, const T&)) {
        for (int i = 0; i < length - 1; i++) {
            for (int j = 0; j < length - i - 1; j++) {
                if (!cmp(data[j], data[j + 1])) {
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    // 检查是否包含某个值
    bool contains(const T& val) const {
        for (int i = 0; i < length; i++) {
            if (data[i] == val) return true;
        }
        return false;
    }
};

// ==================== 进程和调度器 ====================

struct Process {
    string name;           // 进程名称
    int pid;               // 进程PID (0~3500)
    int arriveTime;        // 到达时间 (0~100)
    int burstTime;         // 服务时间 (20~100)
    int remainingTime;     // 剩余运行时间
    int queueLevel;        // 当前队列级别 (0-4, 0最高)
    int timeInQueue;       // 在当前队列已用时间
    int consecutiveRuns;   // 连续调度次数（最后一级队列用）
    int startTime;         // 开始时间
    int finishTime;        // 完成时间
    bool completed;        // 是否完成

    Process() : name(""), pid(0), arriveTime(0), burstTime(0), remainingTime(0),
                queueLevel(0), timeInQueue(0), consecutiveRuns(0),
                startTime(-1), finishTime(-1), completed(false) {}

    Process(string n, int p, int a, int b)
        : name(n), pid(p), arriveTime(a), burstTime(b), remainingTime(b),
          queueLevel(0), timeInQueue(0), consecutiveRuns(0),
          startTime(-1), finishTime(-1), completed(false) {}

    // 获取进程信息字符串
    string getInfo() const {
        char buffer[100];
        sprintf(buffer, "%s(PID:%d) 到达:%d 总需:%d 剩余:%d",
                name.c_str(), pid, arriveTime, burstTime, remainingTime);
        return string(buffer);
    }
};

class MLFQScheduler {
private:
    MyVector<MyQueue<Process*>> queues;  // 5级队列
    MyVector<int> timeSlices;            // 每级队列的时间片
    MyVector<Process> processes;         // 所有进程
    int currentTime;                     // 当前系统时间
    int completedCount;                  // 已完成进程数

public:
    MLFQScheduler() : currentTime(0), completedCount(0) {
        srand(time(nullptr));

        // 初始化5级队列
        for (int i = 0; i < 5; i++) {
            queues.push_back(MyQueue<Process*>());
        }

        // 生成5个不同的时间片 (1~16)
        generateTimeSlices();

        // 生成至少5个进程
        generateProcesses(5 + (rand() % 3));

        // 显示系统初始化状态
        displayInitialStatus();
    }

    // 生成5个不同的时间片
    void generateTimeSlices() {
        MyVector<int> used;
        while (timeSlices.size() < 5) {
            int ts = (rand() % 16) + 1;  // 1~16
            if (!used.contains(ts)) {
                used.push_back(ts);
                timeSlices.push_back(ts);
            }
        }
        // 按从小到大排序（时间片越小优先级越高）
        timeSlices.sort([](const int& a, const int& b) { return a < b; });
    }

    // 生成随机进程
    void generateProcesses(int count) {
        for (int i = 0; i < count; i++) {
            char nameBuf[10];
            sprintf(nameBuf, "P%d", i + 1);
            string name = nameBuf;

            int pid = rand() % 3501;           // 0~3500
            int arrive = rand() % 101;         // 0~100
            int burst = 20 + (rand() % 81);    // 20~100

            processes.push_back(Process(name, pid, arrive, burst));
        }

        // 按到达时间排序
        processes.sort([](const Process& a, const Process& b) {
            return a.arriveTime < b.arriveTime;
        });
    }

    // 显示系统初始化状态
    void displayInitialStatus() {
        cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                   多级反馈队列调度算法模拟器 (简化版)                       ║" << endl;
        cout << "║                 Multilevel Feedback Queue Scheduler (Simplified)             ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl;

        cout << "\n系统初始化完成 - 当前时间: " << currentTime << endl;
        cout << string(60, '=') << endl;

        cout << "\n队列配置:" << endl;
        cout << "队列级别\t优先级\t时间片大小" << endl;
        cout << "--------\t------\t----------" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "队列" << (i + 1) << "\t\t" << (i + 1) << "\t" << timeSlices[i] << endl;
        }

        cout << "\n进程基本信息:" << endl;
        cout << "名称\tPID\t到达时间\t服务时间\t剩余时间" << endl;
        cout << "----\t---\t--------\t--------\t--------" << endl;
        for (int i = 0; i < processes.size(); i++) {
            const Process& p = processes[i];
            cout << p.name << "\t" << p.pid << "\t" << p.arriveTime
                 << "\t\t" << p.burstTime << "\t\t" << p.remainingTime << endl;
        }

        displayQueueStatus("初始队列状态");
    }

    // 显示队列状态
    void displayQueueStatus(const string& title) {
        cout << "\n" << title << ":" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "队列" << (i + 1) << " (时间片:" << timeSlices[i] << "): ";
            if (queues[i].empty()) {
                cout << "空" << endl;
            } else {
                cout << queues[i].size() << "个进程 - ";
                queues[i].traverse([](Process* p, int pos) {
                    cout << p->name << "(位置:" << pos << ",剩余:" << p->remainingTime << ") ";
                });
                cout << endl;
            }
        }
    }

    // 显示进程事件
    void displayProcessEvent(Process* p, const string& event) {
        cout << "\n" << string(60, '-') << endl;
        cout << "事件: " << event << endl;
        cout << "进程: " << p->getInfo() << endl;
        cout << "当前队列: " << (p->queueLevel + 1)
             << ", 连续调度次数: " << p->consecutiveRuns << endl;
        cout << string(60, '-') << endl;
    }

    // 检查新到达的进程
    void checkNewArrivals() {
        for (int i = 0; i < processes.size(); i++) {
            Process* p = &processes[i];
            if (!p->completed && p->arriveTime == currentTime) {
                // 检查进程是否已经在队列中
                bool alreadyInQueue = false;
                for (int q = 0; q < 5; q++) {
                    // 简单检查：如果进程在队列中，它的queueLevel应该>=0且timeInQueue可能>0
                    // 更好的方法是遍历队列检查，但为了简化，我们检查startTime
                    if (p->startTime != -1) {
                        alreadyInQueue = true;
                        break;
                    }
                }

                if (!alreadyInQueue) {
                    // 新进程到达，加入最高优先级队列
                    p->queueLevel = 0;
                    p->timeInQueue = 0;
                    p->consecutiveRuns = 0;
                    queues[0].push(p);

                    displayProcessEvent(p, "新进程进入系统");
                    displayQueueStatus("新进程进入后队列状态");
                }
            }
        }
    }

    // 查找最高优先级非空队列
    int findHighestPriorityQueue() {
        for (int i = 0; i < 5; i++) {
            if (!queues[i].empty()) return i;
        }
        return -1;  // 所有队列都为空
    }

    // 执行调度
    void schedule() {
        cout << "\n" << string(60, '=') << endl;
        cout << "开始多级反馈队列调度模拟" << endl;
        cout << string(60, '=') << endl;

        int maxTime = 1000;  // 防止无限循环

        while (completedCount < processes.size() && currentTime < maxTime) {
            // 检查新到达的进程
            checkNewArrivals();

            // 查找最高优先级非空队列
            int qIndex = findHighestPriorityQueue();

            if (qIndex == -1) {
                // 所有队列为空，时间推进
                currentTime++;
                continue;
            }

            // 从队列中取出进程
            Process* currentProcess = queues[qIndex].front_val();
            queues[qIndex].pop();

            // 记录开始时间
            if (currentProcess->startTime == -1) {
                currentProcess->startTime = currentTime;
            }

            // 获取当前队列的时间片
            int timeSlice = timeSlices[qIndex];

            // 确定实际执行时间
            int execTime = (currentProcess->remainingTime < timeSlice) ?
                          currentProcess->remainingTime : timeSlice;

            // 更新连续调度次数（如果是最后一级队列）
            if (qIndex == 4) {
                currentProcess->consecutiveRuns++;
            } else {
                currentProcess->consecutiveRuns = 0;
            }

            // 显示调度信息
            cout << "\n时间 " << currentTime << ": 调度 " << currentProcess->name
                 << " 从队列" << (qIndex + 1)
                 << " 执行 " << execTime << " 单位时间" << endl;

            // 执行进程（模拟时间流逝）
            for (int t = 0; t < execTime; t++) {
                currentTime++;
                currentProcess->remainingTime--;
                currentProcess->timeInQueue++;
                checkNewArrivals();  // 检查在此期间到达的新进程
            }

            // 检查进程是否完成
            if (currentProcess->remainingTime == 0) {
                // 进程完成
                currentProcess->finishTime = currentTime;
                currentProcess->completed = true;
                completedCount++;

                displayProcessEvent(currentProcess, "进程离开系统");
                displayQueueStatus("进程离开后队列状态");

                cout << "✓ 进程 " << currentProcess->name << " 已完成!" << endl;
                cout << "  开始时间: " << currentProcess->startTime
                     << ", 完成时间: " << currentProcess->finishTime
                     << ", 周转时间: " << (currentProcess->finishTime - currentProcess->arriveTime) << endl;
            } else {
                // 进程未完成，需要重新加入队列
                handleUnfinishedProcess(currentProcess, qIndex, timeSlice);
                displayQueueStatus("进程重新加入后队列状态");
            }
        }

        // 调度结束
        cout << "\n" << string(60, '=') << endl;
        if (completedCount == processes.size()) {
            cout << "所有进程已完成调度!" << endl;
        } else {
            cout << "达到最大时间限制 " << maxTime << "，调度提前结束!" << endl;
        }
        cout << string(60, '=') << endl;

        printStatistics();
    }

    // 处理未完成的进程
    void handleUnfinishedProcess(Process* p, int qIndex, int timeSlice) {
        if (p->timeInQueue >= timeSlice) {
            // 当前队列时间片已用完
            p->timeInQueue = 0;  // 重置当前队列耗时

            if (qIndex == 4) {
                // 最后一级队列特殊规则
                if (p->consecutiveRuns >= 2) {
                    // 连续调度两次仍未完成，返回第一级队列
                    cout << "⚠️  特殊规则触发: " << p->name
                         << " 在最后一级队列中连续调度" << p->consecutiveRuns
                         << "次仍未完成，返回第一级队列!" << endl;
                    p->queueLevel = 0;
                    p->consecutiveRuns = 0;
                } else {
                    // 留在最后一级队列
                    cout << "  " << p->name << " 时间片用完，留在队列5" << endl;
                }
            } else {
                // 降级到下一级队列
                int nextLevel = (qIndex + 1 < 4) ? qIndex + 1 : 4;
                p->queueLevel = nextLevel;
                p->consecutiveRuns = 0;
                cout << "  " << p->name << " 时间片用完，降级到队列" << (nextLevel + 1) << endl;
            }
        } else {
            // 时间片未用完，重新加入当前队列
            cout << "  " << p->name << " 时间片未用完，重新加入队列" << (qIndex + 1) << endl;
        }

        queues[p->queueLevel].push(p);
    }

    // 打印统计信息
    void printStatistics() {
        cout << "\n最终统计信息:" << endl;
        cout << "名称\tPID\t到达\t服务\t开始\t完成\t周转\t等待" << endl;
        cout << "----\t---\t----\t----\t----\t----\t----\t----" << endl;

        double totalTurnaround = 0;
        double totalWaiting = 0;

        for (int i = 0; i < processes.size(); i++) {
            const Process& p = processes[i];
            int turnaround = p.finishTime - p.arriveTime;
            int waiting = turnaround - p.burstTime;

            totalTurnaround += turnaround;
            totalWaiting += waiting;

            cout << p.name << "\t" << p.pid << "\t"
                 << p.arriveTime << "\t" << p.burstTime << "\t"
                 << p.startTime << "\t" << p.finishTime << "\t"
                 << turnaround << "\t" << waiting << endl;
        }

        cout << "\n平均周转时间: " << fixed << setprecision(2)
             << (totalTurnaround / processes.size()) << endl;
        cout << "平均等待时间: " << fixed << setprecision(2)
             << (totalWaiting / processes.size()) << endl;
        cout << "总调度时间: " << currentTime << " 单位时间" << endl;

        cout << "\n队列配置总结:" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "队列" << (i + 1) << ": 时间片大小 = " << timeSlices[i]
                 << ", 优先级 = " << (i + 1) << endl;
        }
    }
};

// 主函数
int main() {
    cout << "多级反馈队列调度算法模拟器 (简化版)" << endl;
    cout << "=====================================" << endl;
    cout << "算法规则:" << endl;
    cout << "1. 5级队列，优先级从高到低（队列1最高，队列5最低）" << endl;
    cout << "2. 每级队列时间片大小为1~16之间的随机数，且各不相同" << endl;
    cout << "3. 新进程进入最高优先级队列（队列1）" << endl;
    cout << "4. 当前队列时间片用完后，进程进入下一级队列参与调度" << endl;
    cout << "5. 最后一级队列中的进程时间片耗尽时，返回本级队列继续排队" << endl;
    cout << "6. 最后一级队列中的进程，如果连续被调度两次仍未运行结束，则返回至第一级队列" << endl;
    cout << "7. 高优先级队列中的进程优先于低优先级队列中的进程" << endl;
    cout << endl;

    cout << "进程生成规则:" << endl;
    cout << "- 进程PID: 0~3500之间的随机整数" << endl;
    cout << "- 到达时间: 0~100之间的随机数" << endl;
    cout << "- 服务时间: 20~100之间的随机数" << endl;
    cout << "- 至少模拟5个进程" << endl;
    cout << endl;

    cout << "开始模拟..." << endl;
    cout << "=============" << endl;

    MLFQScheduler scheduler;
    scheduler.schedule();

    cout << "\n模拟完成!" << endl;

    return 0;
}
