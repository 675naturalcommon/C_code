#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <climits>

using namespace std;

// 进程结构体
struct Process {
    int id;           // 进程ID
    int arrivalTime;  // 到达时间
    int burstTime;    // 执行时间
    int deadline;     // 截止时间
    int remainingTime; // 剩余执行时间
    int laxity;       // 松弛度
    int completionTime; // 完成时间
    int waitingTime;  // 等待时间
    int turnaroundTime; // 周转时间

    Process(int id, int arrival, int burst, int deadline)
        : id(id), arrivalTime(arrival), burstTime(burst),
          deadline(deadline), remainingTime(burst), laxity(0) {}
};

class LLFScheduler {
private:
    vector<Process> processes;
    int currentTime;
    int missedDeadlines; // 错过截止时间的进程数

public:
    LLFScheduler(vector<Process> procs) : processes(procs), currentTime(0), missedDeadlines(0) {}

    // 改进的松弛度计算
    void calculateLaxity() {
        for (auto& p : processes) {
            if (p.remainingTime > 0 && currentTime >= p.arrivalTime) {
                // 计算松弛度，如果松弛度为负，说明可能错过截止时间
                p.laxity = p.deadline - currentTime - p.remainingTime;

                // 如果松弛度小于0，标记为紧急进程
                if (p.laxity < 0) {
                    cout << "警告: 进程P" << p.id << "松弛度为负(" << p.laxity
                         << ")，可能错过截止时间!" << endl;
                }
            } else {
                p.laxity = INT_MAX; // 未到达或已完成
            }
        }
    }

    // 改进的进程选择策略
    int findMinLaxityProcess() {
        int minLaxity = INT_MAX;
        int minIndex = -1;
        bool hasNegativeLaxity = false;

        // 首先检查是否有松弛度为负的紧急进程
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].remainingTime > 0 &&
                processes[i].arrivalTime <= currentTime &&
                processes[i].laxity < 0) {
                hasNegativeLaxity = true;
                if (processes[i].laxity < minLaxity) {
                    minLaxity = processes[i].laxity;
                    minIndex = i;
                }
            }
        }

        // 如果没有紧急进程，选择松弛度最小的进程
        if (!hasNegativeLaxity) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].remainingTime > 0 &&
                    processes[i].arrivalTime <= currentTime &&
                    processes[i].laxity < minLaxity) {
                    minLaxity = processes[i].laxity;
                    minIndex = i;
                }
            }
        }

        return minIndex;
    }

    // 检查是否所有进程都已完成
    bool allProcessesCompleted() {
        for (const auto& p : processes) {
            if (p.remainingTime > 0) return false;
        }
        return true;
    }

    // 改进的LLF调度
    void schedule() {
        cout << "开始改进的LLF调度..." << endl;
        cout << "时间\t进程\t松弛度\t剩余时间\t截止时间检查" << endl;
        cout << "------------------------------------------------" << endl;

        vector<pair<int, int>> timeline; // 记录时间线 (时间, 进程ID)

        while (!allProcessesCompleted()) {
            calculateLaxity();
            int currentProcess = findMinLaxityProcess();

            if (currentProcess == -1) {
                // 没有可执行的进程，时间推进
                timeline.push_back({currentTime, -1});
                cout << currentTime << "\t-\t-\t-\t空闲" << endl;
                currentTime++;
                continue;
            }

            // 检查截止时间是否会被错过
            bool deadlineMissed = false;
            if (currentTime + processes[currentProcess].remainingTime > processes[currentProcess].deadline) {
                deadlineMissed = true;
                missedDeadlines++;
                cout << "错误: 进程P" << processes[currentProcess].id
                     << "将在时间" << currentTime + processes[currentProcess].remainingTime
                     << "完成，但截止时间为" << processes[currentProcess].deadline << "!" << endl;
            }

            // 执行选中的进程
            processes[currentProcess].remainingTime--;
            timeline.push_back({currentTime, processes[currentProcess].id});

            string deadlineStatus = deadlineMissed ? "可能错过" : "正常";
            cout << currentTime << "\tP" << processes[currentProcess].id
                 << "\t" << processes[currentProcess].laxity
                 << "\t" << processes[currentProcess].remainingTime
                 << "\t" << deadlineStatus << endl;

            // 如果进程完成，记录完成时间并检查是否错过截止时间
            if (processes[currentProcess].remainingTime == 0) {
                processes[currentProcess].completionTime = currentTime + 1;
                if (processes[currentProcess].completionTime > processes[currentProcess].deadline) {
                    cout << "进程P" << processes[currentProcess].id << "错过了截止时间!" << endl;
                }
            }

            currentTime++;
        }

        // 计算性能指标
        calculatePerformance();

        // 显示时间线
        displayTimeline(timeline);
    }

    // 改进的性能指标计算
    void calculatePerformance() {
        cout << "\n性能指标分析:" << endl;
        cout << "进程ID\t到达时间\t执行时间\t截止时间\t完成时间\t周转时间\t等待时间\t是否错过截止时间" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------" << endl;

        double totalTurnaround = 0;
        double totalWaiting = 0;
        int missedDeadlineCount = 0;

        for (auto& p : processes) {
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;

            totalTurnaround += p.turnaroundTime;
            totalWaiting += p.waitingTime;

            bool missedDeadline = p.completionTime > p.deadline;
            if (missedDeadline) {
                missedDeadlineCount++;
            }

            cout << "P" << p.id << "\t" << p.arrivalTime << "\t\t"
                 << p.burstTime << "\t\t" << p.deadline << "\t\t"
                 << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t"
                 << p.waitingTime << "\t\t" << (missedDeadline ? "是" : "否") << endl;
        }

        cout << "\n统计汇总:" << endl;
        cout << "平均周转时间: " << totalTurnaround / processes.size() << endl;
        cout << "平均等待时间: " << totalWaiting / processes.size() << endl;
        cout << "错过截止时间的进程数: " << missedDeadlineCount << "/" << processes.size() << endl;
        cout << "成功率: " << (1.0 - (double)missedDeadlineCount / processes.size()) * 100 << "%" << endl;

        // 计算CPU利用率
        int totalExecutionTime = 0;
        for (const auto& p : processes) {
            totalExecutionTime += p.burstTime;
        }
        double cpuUtilization = (double)totalExecutionTime / currentTime * 100;
        cout << "CPU利用率: " << cpuUtilization << "%" << endl;
    }

    // 显示时间线
    void displayTimeline(const vector<pair<int, int>>& timeline) {
        cout << "\n执行时间线:" << endl;
        cout << "时间: ";
        for (int i = 0; i <= currentTime; i++) {
            cout << setw(3) << i << " ";
        }
        cout << endl;

        cout << "进程: ";
        for (const auto& event : timeline) {
            if (event.second == -1) {
                cout << "  - ";
            } else {
                cout << " P" << event.second << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    // 创建测试进程
    vector<Process> processes = {
        Process(1, 0, 5, 10),  // 进程1: 到达时间0，执行时间5，截止时间10
        Process(2, 1, 3, 8),   // 进程2: 到达时间1，执行时间3，截止时间8
        Process(3, 2, 4, 12),  // 进程3: 到达时间2，执行时间4，截止时间12
        Process(4, 3, 2, 7)    // 进程4: 到达时间3，执行时间2，截止时间7
    };

    LLFScheduler scheduler(processes);
    scheduler.schedule();

    return 0;
}
