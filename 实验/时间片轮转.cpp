#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <limits>

using namespace std;

// 进程结构体
struct Process {
    int id;           // 进程ID
    int arriveTime;   // 到达时间
    int burstTime;    // 运行时间
    int remainingTime; // 剩余运行时间
    int startTime;    // 开始时间
    int finishTime;   // 完成时间
    int turnaroundTime; // 周转时间
    int waitingTime;  // 等待时间
    int responseTime; // 响应时间
    bool started;     // 是否已经开始过
    int priority;     // 进程优先级（可选）

    Process(int id, int arrive, int burst, int priority = 0) {
        this->id = id;
        arriveTime = arrive;
        burstTime = burst;
        remainingTime = burst;
        startTime = -1;
        finishTime = -1;
        turnaroundTime = 0;
        waitingTime = 0;
        responseTime = 0;
        started = false;
        this->priority = priority;
    }
};

class RRScheduler {
private:
    vector<Process> processes;
    int timeQuantum;
    int totalTime;
    bool usePriority;  // 是否使用优先级

public:
    RRScheduler(vector<Process> &procs, int quantum, bool usePriority = false) {
        processes = procs;
        timeQuantum = quantum;
        totalTime = 0;
        this->usePriority = usePriority;
    }

    // 模拟RR调度
    void simulate() {
        queue<int> readyQueue; // 就绪队列，存储进程索引
        vector<bool> completed(processes.size(), false);
        int currentTime = 0;
        int completedCount = 0;
        int totalProcesses = processes.size();
        int contextSwitches = 0;

        // 按到达时间排序进程
        sort(processes.begin(), processes.end(),
             [](const Process &a, const Process &b) {
                 return a.arriveTime < b.arriveTime;
             });

        cout << "\n" << string(80, '=') << endl;
        cout << "时间片轮转调度算法模拟 (时间片大小: " << timeQuantum << ")" << endl;
        cout << string(80, '=') << endl;

        cout << "\n调度甘特图:" << endl;
        cout << "时间\t进程\t剩余时间" << endl;
        cout << "----\t----\t--------" << endl;

        // 初始化就绪队列，加入所有在时间0到达的进程
        for (int i = 0; i < totalProcesses; i++) {
            if (processes[i].arriveTime <= currentTime) {
                readyQueue.push(i);
            }
        }

        while (completedCount < totalProcesses) {
            if (readyQueue.empty()) {
                // 如果没有就绪进程，时间推进到下一个进程到达
                int nextArrival = findNextArrival(currentTime, completed);
                if (nextArrival == -1) break;

                cout << currentTime << "-" << processes[nextArrival].arriveTime
                     << "\t空闲\t-" << endl;

                currentTime = processes[nextArrival].arriveTime;
                readyQueue.push(nextArrival);
                continue;
            }

            int currentIndex = readyQueue.front();
            readyQueue.pop();
            Process &currentProcess = processes[currentIndex];

            // 记录开始时间（如果是第一次执行）
            if (!currentProcess.started) {
                currentProcess.startTime = currentTime;
                currentProcess.responseTime = currentTime - currentProcess.arriveTime;
                currentProcess.started = true;
            }

            // 执行进程（一个时间片或直到完成）
            int executionTime = min(timeQuantum, currentProcess.remainingTime);

            // 输出甘特图
            cout << currentTime << "-" << (currentTime + executionTime)
                 << "\tP" << currentProcess.id
                 << "\t" << (currentProcess.remainingTime - executionTime) << endl;

            currentTime += executionTime;
            currentProcess.remainingTime -= executionTime;
            contextSwitches++;

            // 检查在此期间到达的新进程并加入就绪队列
            for (int i = 0; i < totalProcesses; i++) {
                if (!completed[i] && !processes[i].started &&
                    processes[i].arriveTime <= currentTime &&
                    processes[i].arriveTime > currentTime - executionTime) {
                    readyQueue.push(i);
                }
            }

            if (currentProcess.remainingTime == 0) {
                // 进程完成
                currentProcess.finishTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.finishTime - currentProcess.arriveTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
                completed[currentIndex] = true;
                completedCount++;
            } else {
                // 进程未完成，重新加入就绪队列
                readyQueue.push(currentIndex);
            }
        }

        totalTime = currentTime;

        // 输出上下文切换统计
        cout << "\n调度统计:" << endl;
        cout << "总上下文切换次数: " << contextSwitches << endl;
        cout << "总调度时间: " << totalTime << " 单位时间" << endl;
    }

    // 计算并输出统计信息
    void printStatistics() {
        cout << "\n" << string(80, '=') << endl;
        cout << "进程详细信息" << endl;
        cout << string(80, '=') << endl;

        cout << "ID\t到达\t运行\t开始\t完成\t周转\t等待\t响应\t优先级" << endl;
        cout << "--\t----\t----\t----\t----\t----\t----\t----\t----" << endl;

        double avgTurnaround = 0, avgWaiting = 0, avgResponse = 0;

        for (const auto &p : processes) {
            cout << "P" << p.id << "\t"
                 << p.arriveTime << "\t"
                 << p.burstTime << "\t"
                 << p.startTime << "\t"
                 << p.finishTime << "\t"
                 << p.turnaroundTime << "\t"
                 << p.waitingTime << "\t"
                 << p.responseTime << "\t"
                 << p.priority << endl;

            avgTurnaround += p.turnaroundTime;
            avgWaiting += p.waitingTime;
            avgResponse += p.responseTime;
        }

        avgTurnaround /= processes.size();
        avgWaiting /= processes.size();
        avgResponse /= processes.size();

        cout << "\n" << string(80, '=') << endl;
        cout << "性能指标" << endl;
        cout << string(80, '=') << endl;

        cout << "平均周转时间: " << fixed << setprecision(2) << avgTurnaround << endl;
        cout << "平均等待时间: " << fixed << setprecision(2) << avgWaiting << endl;
        cout << "平均响应时间: " << fixed << setprecision(2) << avgResponse << endl;

        // 计算处理机利用率
        double totalBusyTime = 0;
        for (const auto &p : processes) {
            totalBusyTime += p.burstTime;
        }
        double cpuUtilization = (totalBusyTime / totalTime) * 100;
        cout << "处理机利用率: " << fixed << setprecision(2) << cpuUtilization << "%" << endl;

        // 计算吞吐量
        double throughput = (double)processes.size() / totalTime;
        cout << "系统吞吐量: " << fixed << setprecision(4) << throughput << " 进程/单位时间" << endl;
    }

    // 生成性能报告
    void generateReport() {
        cout << "\n" << string(80, '=') << endl;
        cout << "性能分析报告" << endl;
        cout << string(80, '=') << endl;

        map<int, int> completionOrder;
        for (int i = 0; i < processes.size(); i++) {
            completionOrder[processes[i].finishTime] = processes[i].id;
        }

        cout << "进程完成顺序: ";
        bool first = true;
        for (const auto &entry : completionOrder) {
            if (!first) cout << " -> ";
            cout << "P" << entry.second;
            first = false;
        }
        cout << endl;
    }

private:
    // 找到下一个到达的进程索引
    int findNextArrival(int currentTime, vector<bool> &completed) {
        int minArrival = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < processes.size(); i++) {
            if (!completed[i] && processes[i].arriveTime > currentTime &&
                processes[i].arriveTime < minArrival) {
                minArrival = processes[i].arriveTime;
                minIndex = i;
            }
        }
        return minIndex;
    }
};

// 分析不同时间片大小的性能
void analyzeTimeQuantum() {
    // 测试数据
    vector<Process> testProcesses = {
        Process(1, 0, 5),
        Process(2, 1, 3),
        Process(3, 2, 8),
        Process(4, 3, 6),
        Process(5, 4, 4)
    };

    vector<int> timeQuanta = {1, 2, 3, 4, 5, 6, 8, 10};

    cout << "\n" << string(80, '=') << endl;
    cout << "不同时间片大小的性能分析" << endl;
    cout << string(80, '=') << endl;

    cout << "时间片\t平均周转\t平均等待\t平均响应\tCPU利用率\t吞吐量" << endl;
    cout << "------\t--------\t--------\t--------\t---------\t------" << endl;

    for (int quantum : timeQuanta) {
        vector<Process> tempProcesses = testProcesses;
        RRScheduler scheduler(tempProcesses, quantum);
        scheduler.simulate();

        // 计算统计信息
        double avgTurnaround = 0, avgWaiting = 0, avgResponse = 0;
        double totalBusyTime = 0, totalTime = 0;

        for (const auto &p : tempProcesses) {
            avgTurnaround += p.turnaroundTime;
            avgWaiting += p.waitingTime;
            avgResponse += p.responseTime;
            totalBusyTime += p.burstTime;
            totalTime = max(totalTime, (double)p.finishTime);
        }

        avgTurnaround /= tempProcesses.size();
        avgWaiting /= tempProcesses.size();
        avgResponse /= tempProcesses.size();
        double cpuUtilization = (totalBusyTime / totalTime) * 100;
        double throughput = tempProcesses.size() / totalTime;

        cout << quantum << "\t" << fixed << setprecision(2)
             << avgTurnaround << "\t\t"
             << avgWaiting << "\t\t"
             << avgResponse << "\t\t"
             << cpuUtilization << "%\t\t"
             << fixed << setprecision(4) << throughput << endl;
    }
}

// 交互式输入进程信息
vector<Process> inputProcesses() {
    vector<Process> processes;
    int numProcesses;

    cout << "\n请输入进程数量: ";
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; i++) {
        int arrive, burst, priority;
        cout << "进程 P" << (i+1) << " - 到达时间: ";
        cin >> arrive;
        cout << "进程 P" << (i+1) << " - 运行时间: ";
        cin >> burst;
        cout << "进程 P" << (i+1) << " - 优先级(0-10, 0为默认): ";
        cin >> priority;

        processes.emplace_back(i+1, arrive, burst, priority);
    }

    return processes;
}

// 演示不同场景
void demonstrateScenarios() {
    cout << "\n" << string(80, '=') << endl;
    cout << "不同调度场景演示" << endl;
    cout << string(80, '=') << endl;

    // 场景1: CPU密集型
    cout << "\n场景1: CPU密集型进程" << endl;
    vector<Process> cpuIntensive = {
        Process(1, 0, 10),
        Process(2, 1, 8),
        Process(3, 2, 12)
    };
    RRScheduler scheduler1(cpuIntensive, 3);
    scheduler1.simulate();
    scheduler1.printStatistics();

    // 场景2: I/O密集型
    cout << "\n场景2: I/O密集型进程(短时间片)" << endl;
    vector<Process> ioIntensive = {
        Process(1, 0, 2),
        Process(2, 1, 3),
        Process(3, 2, 1),
        Process(4, 3, 2)
    };
    RRScheduler scheduler2(ioIntensive, 1);
    scheduler2.simulate();
    scheduler2.printStatistics();
}

int main() {
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                      时间片轮转调度算法改进版本                              ║" << endl;
    cout << "║                          Enhanced Round Robin Scheduler                      ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl;

    int choice;
    do {
        cout << "\n请选择操作:" << endl;
        cout << "1. 使用默认示例" << endl;
        cout << "2. 自定义输入进程" << endl;
        cout << "3. 分析不同时间片大小" << endl;
        cout << "4. 演示不同场景" << endl;
        cout << "5. 退出" << endl;
        cout << "选择: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // 示例1：固定时间片
                vector<Process> processes = {
                    Process(1, 0, 5),
                    Process(2, 1, 3),
                    Process(3, 2, 8),
                    Process(4, 3, 6),
                    Process(5, 4, 4)
                };

                int timeQuantum = 3;
                RRScheduler scheduler(processes, timeQuantum);
                scheduler.simulate();
                scheduler.printStatistics();
                scheduler.generateReport();
                break;
            }

            case 2: {
                vector<Process> processes = inputProcesses();
                int timeQuantum;
                cout << "请输入时间片大小: ";
                cin >> timeQuantum;

                RRScheduler scheduler(processes, timeQuantum);
                scheduler.simulate();
                scheduler.printStatistics();
                scheduler.generateReport();
                break;
            }

            case 3: {
                analyzeTimeQuantum();
                break;
            }

            case 4: {
                demonstrateScenarios();
                break;
            }

            case 5: {
                cout << "感谢使用时间片轮转调度算法模拟器!" << endl;
                break;
            }

            default: {
                cout << "无效选择，请重新输入!" << endl;
                break;
            }
        }
    } while (choice != 5);

    return 0;
}
