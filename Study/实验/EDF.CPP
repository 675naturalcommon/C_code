#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

// 任务结构体
struct Task {
    int id;           // 任务ID
    int arrival_time; // 到达时间
    int execution_time; // 执行时间
    int deadline;     // 截止时间
    int remaining_time; // 剩余执行时间
    int start_time;   // 开始执行时间
    int finish_time;  // 完成时间

    Task(int i, int at, int et, int d)
        : id(i), arrival_time(at), execution_time(et), deadline(d),
          remaining_time(et), start_time(-1), finish_time(-1) {}
};

// EDF调度器类
class EDFScheduler {
private:
    vector<Task> tasks;
    int current_time;

public:
    EDFScheduler() : current_time(0) {}

    // 添加任务
    void addTask(int id, int arrival_time, int execution_time, int deadline) {
        tasks.emplace_back(id, arrival_time, execution_time, deadline);
    }

    // EDF比较函数（用于优先队列）
    struct CompareDeadline {
        bool operator()(const Task* a, const Task* b) {
            // 截止时间越早优先级越高
            return a->deadline > b->deadline;
        }
    };

    // 执行调度
    void schedule() {
        cout << "开始EDF调度..." << endl;
        cout << "时间\t执行任务\t剩余时间\t截止时间" << endl;
        cout << "----------------------------------------" << endl;

        int completed_tasks = 0;
        int total_tasks = tasks.size();
        vector<Task*> ready_queue;
        priority_queue<Task*, vector<Task*>, CompareDeadline> pq;

        Task* current_task = nullptr;

        while (completed_tasks < total_tasks) {
            // 检查是否有新任务到达
            for (auto& task : tasks) {
                if (task.arrival_time == current_time && task.remaining_time > 0) {
                    ready_queue.push_back(&task);
                    pq.push(&task);
                }
            }

            // 如果当前有任务在执行，检查是否需要抢占
            if (current_task != nullptr && current_task->remaining_time > 0) {
                // 检查是否有更早截止时间的任务
                if (!pq.empty() && pq.top()->deadline < current_task->deadline) {
                    // 发生抢占
                    cout << current_time << "\t任务" << current_task->id << "被抢占" << endl;
                    pq.push(current_task); // 将当前任务放回队列
                    current_task = pq.top();
                    pq.pop();

                    if (current_task->start_time == -1) {
                        current_task->start_time = current_time;
                    }
                }
            }

            // 如果没有当前任务，从队列中取一个
            if ((current_task == nullptr || current_task->remaining_time == 0) && !pq.empty()) {
                current_task = pq.top();
                pq.pop();

                if (current_task->start_time == -1) {
                    current_task->start_time = current_time;
                }
            }

            // 执行当前任务
            if (current_task != nullptr && current_task->remaining_time > 0) {
                cout << current_time << "\t任务" << current_task->id
                     << "\t\t" << current_task->remaining_time - 1
                     << "\t\t" << current_task->deadline << endl;

                current_task->remaining_time--;

                // 检查任务是否完成
                if (current_task->remaining_time == 0) {
                    current_task->finish_time = current_time + 1;
                    completed_tasks++;
                    cout << current_time + 1 << "\t任务" << current_task->id << "完成" << endl;

                    // 检查是否错过截止时间
                    if (current_task->finish_time > current_task->deadline) {
                        cout << "!!! 任务" << current_task->id << "错过截止时间 !!!" << endl;
                    }
                }
            } else {
                cout << current_time << "\t空闲" << endl;
            }

            current_time++;
        }

        // 输出调度结果统计
        printStatistics();
    }

    // 打印统计信息
    void printStatistics() {
        cout << "\n调度结果统计:" << endl;
        cout << "任务ID\t到达时间\t执行时间\t截止时间\t开始时间\t完成时间\t是否按时" << endl;
        cout << "----------------------------------------------------------------" << endl;

        for (const auto& task : tasks) {
            bool on_time = task.finish_time <= task.deadline;
            cout << task.id << "\t" << task.arrival_time << "\t\t"
                 << task.execution_time << "\t\t" << task.deadline << "\t\t"
                 << task.start_time << "\t\t" << task.finish_time << "\t\t"
                 << (on_time ? "是" : "否") << endl;
        }
    }

    // 检查调度可行性（可调度性测试）
    bool isSchedulable() {
        double utilization = 0.0;
        for (const auto& task : tasks) {
            utilization += static_cast<double>(task.execution_time) /
                          static_cast<double>(task.deadline - task.arrival_time);
        }

        cout << "\n系统利用率: " << fixed << setprecision(2) << utilization << endl;

        // EDF在单处理器上的可调度条件：利用率 <= 1
        if (utilization <= 1.0) {
            cout << "系统可调度（利用率 ≤ 1）" << endl;
            return true;
        } else {
            cout << "警告：系统可能不可调度（利用率 > 1）" << endl;
            return false;
        }
    }
};

// 示例使用
int main() {
    EDFScheduler scheduler;

    // 添加示例任务：任务ID, 到达时间, 执行时间, 截止时间
    scheduler.addTask(1, 0, 3, 7);  // 任务1：到达时间0，执行3个单位，截止时间7
    scheduler.addTask(2, 2, 2, 6);  // 任务2：到达时间2，执行2个单位，截止时间6
    scheduler.addTask(3, 4, 2, 8);  // 任务3：到达时间4，执行2个单位，截止时间8

    // 检查可调度性
    scheduler.isSchedulable();

    // 执行调度
    scheduler.schedule();

    return 0;
}