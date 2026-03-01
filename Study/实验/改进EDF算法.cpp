#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// 任务结构体
struct Task {
    int id;           // 任务ID
    int arrival_time; // 到达时间
    int execution_time; // 执行时间
    int deadline;     // 绝对截止时间
    int period;       // 周期（用于周期性任务）
    int remaining_time; // 剩余执行时间
    int start_time;   // 开始执行时间
    int finish_time;  // 完成时间
    int missed_deadlines; // 错过的截止时间次数
    bool is_periodic; // 是否为周期性任务

    Task(int i, int at, int et, int d, int p = 0, bool periodic = false)
        : id(i), arrival_time(at), execution_time(et), deadline(d), period(p),
          remaining_time(et), start_time(-1), finish_time(-1),
          missed_deadlines(0), is_periodic(periodic) {}
};

// 改进的EDF调度器类
class ImprovedEDFScheduler {
private:
    vector<Task> tasks;
    int current_time;
    int max_simulation_time;
    double total_utilization;
    int total_missed_deadlines;
    double average_response_time;

public:
    ImprovedEDFScheduler(int max_time = 100)
        : current_time(0), max_simulation_time(max_time),
          total_utilization(0.0), total_missed_deadlines(0),
          average_response_time(0.0) {}

    // 添加任务（支持周期性任务）
    void addTask(int id, int arrival_time, int execution_time, int deadline,
                 int period = 0, bool is_periodic = false) {
        tasks.emplace_back(id, arrival_time, execution_time, deadline, period, is_periodic);
    }

    // 动态截止时间计算函数
    int calculateDynamicDeadline(const Task* task, int current_time) {
        if (task->is_periodic) {
            // 对于周期性任务，计算下一个截止时间
            int periods_passed = (current_time - task->arrival_time) / task->period;
            return task->arrival_time + (periods_passed + 1) * task->period;
        } else {
            // 对于非周期性任务，使用原始截止时间
            return task->deadline;
        }
    }

    // 简化的比较函数（不使用lambda）
    bool compareTasks(const Task* a, const Task* b, int current_time) {
        int a_deadline = calculateDynamicDeadline(a, current_time);
        int b_deadline = calculateDynamicDeadline(b, current_time);
        return a_deadline > b_deadline;
    }

    // 改进的可调度性测试（考虑周期性任务）
    bool isSchedulable() {
        total_utilization = 0.0;

        for (const auto& task : tasks) {
            if (task.is_periodic) {
                // 周期性任务：执行时间/周期
                total_utilization += static_cast<double>(task.execution_time) /
                                   static_cast<double>(task.period);
            } else {
                // 非周期性任务：执行时间/(截止时间-到达时间)
                total_utilization += static_cast<double>(task.execution_time) /
                                   static_cast<double>(task.deadline - task.arrival_time);
            }
        }

        cout << "\n系统利用率分析:" << endl;
        cout << "总利用率: " << fixed << setprecision(3) << total_utilization << endl;

        // 改进的可调度性条件
        if (total_utilization <= 1.0) {
            cout << "✓ 系统可调度（利用率 ≤ 1.0）" << endl;
            return true;
        } else if (total_utilization <= 1.0 + 1e-6) { // 考虑浮点误差
            cout << "⚠ 系统边界可调度（利用率 ≈ 1.0）" << endl;
            return true;
        } else {
            cout << "✗ 系统不可调度（利用率 > 1.0）" << endl;
            cout << "建议：减少任务负载或增加处理器能力" << endl;
            return false;
        }
    }

    // 负载均衡检查
    void checkLoadBalance() {
        cout << "\n负载均衡分析:" << endl;
        double max_utilization = 0.0;
        double min_utilization = numeric_limits<double>::max();

        for (const auto& task : tasks) {
            double task_util;
            if (task.is_periodic) {
                task_util = static_cast<double>(task.execution_time) / task.period;
            } else {
                task_util = static_cast<double>(task.execution_time) /
                           (task.deadline - task.arrival_time);
            }

            max_utilization = max(max_utilization, task_util);
            min_utilization = min(min_utilization, task_util);

            cout << "任务" << task.id << " 利用率: " << fixed << setprecision(3) << task_util << endl;
        }

        double balance_ratio = min_utilization / max_utilization;
        cout << "负载均衡比率: " << fixed << setprecision(3) << balance_ratio << endl;

        if (balance_ratio > 0.7) {
            cout << "✓ 负载均衡良好" << endl;
        } else if (balance_ratio > 0.4) {
            cout << "⚠ 负载均衡一般" << endl;
        } else {
            cout << "✗ 负载不均衡，建议重新分配任务" << endl;
        }
    }

    // 改进的调度算法（支持抢占和周期性任务）
    void schedule() {
        cout << "\n开始改进EDF调度..." << endl;
        cout << "时间\t执行任务\t剩余时间\t动态截止时间\t状态" << endl;
        cout << "--------------------------------------------------------" << endl;

        int completed_tasks = 0;
        int total_instances = 0;
        vector<Task*> ready_queue;

        Task* current_task = nullptr;
        double total_response_time = 0.0;
        int responded_tasks = 0;

        // 处理周期性任务实例
        vector<Task> task_instances = tasks;

        for (auto& task : tasks) {
            if (task.is_periodic) {
                // 为周期性任务生成多个实例
                for (int instance = 1; instance <= max_simulation_time / task.period; instance++) {
                    Task new_task(task.id * 100 + instance,
                                 task.arrival_time + (instance - 1) * task.period,
                                 task.execution_time,
                                 task.arrival_time + instance * task.period,
                                 task.period, true);
                    task_instances.push_back(new_task);
                }
            }
        }

        total_instances = task_instances.size();

        while (current_time < max_simulation_time && completed_tasks < total_instances) {
            // 检查是否有新任务到达
            for (auto& task : task_instances) {
                if (task.arrival_time == current_time && task.remaining_time > 0) {
                    ready_queue.push_back(&task);
                }
            }

            // 对就绪队列按动态截止时间排序
            sort(ready_queue.begin(), ready_queue.end(),
                 [this](Task* a, Task* b) { return compareTasks(a, b, current_time); });

            // 抢占决策：检查是否有更紧急的任务
            if (current_task != nullptr && current_task->remaining_time > 0) {
                if (!ready_queue.empty()) {
                    Task* next_task = ready_queue.front();

                    // 计算动态截止时间进行比较
                    int current_dynamic_deadline = calculateDynamicDeadline(current_task, current_time);
                    int next_dynamic_deadline = calculateDynamicDeadline(next_task, current_time);

                    if (next_dynamic_deadline < current_dynamic_deadline) {
                        // 发生抢占
                        cout << current_time << "\t任务" << current_task->id << "被抢占" << endl;
                        current_task = next_task;
                        ready_queue.erase(ready_queue.begin());

                        if (current_task->start_time == -1) {
                            current_task->start_time = current_time;
                            // 计算响应时间
                            int response_time = current_time - current_task->arrival_time;
                            total_response_time += response_time;
                            responded_tasks++;
                        }
                    }
                }
            }

            // 如果没有当前任务，从队列中取一个
            if ((current_task == nullptr || current_task->remaining_time == 0) && !ready_queue.empty()) {
                current_task = ready_queue.front();
                ready_queue.erase(ready_queue.begin());

                if (current_task->start_time == -1) {
                    current_task->start_time = current_time;
                    // 计算响应时间
                    int response_time = current_time - current_task->arrival_time;
                    total_response_time += response_time;
                    responded_tasks++;
                }
            }

            // 执行当前任务
            if (current_task != nullptr && current_task->remaining_time > 0) {
                int dynamic_deadline = calculateDynamicDeadline(current_task, current_time);

                cout << current_time << "\t任务" << current_task->id
                     << "\t\t" << current_task->remaining_time - 1
                     << "\t\t" << dynamic_deadline << "\t\t执行" << endl;

                current_task->remaining_time--;

                // 检查任务是否完成
                if (current_task->remaining_time == 0) {
                    current_task->finish_time = current_time + 1;
                    completed_tasks++;
                    cout << current_time + 1 << "\t任务" << current_task->id << "完成" << endl;

                    // 检查是否错过截止时间
                    int actual_deadline = current_task->is_periodic ?
                        current_task->arrival_time + current_task->period :
                        current_task->deadline;

                    if (current_task->finish_time > actual_deadline) {
                        cout << "!!! 任务" << current_task->id << "错过截止时间 !!!" << endl;
                        current_task->missed_deadlines++;
                        total_missed_deadlines++;
                    }
                }
            } else {
                cout << current_time << "\t空闲\t\t-\t\t-\t\t空闲" << endl;
            }

            current_time++;
        }

        // 计算平均响应时间
        if (responded_tasks > 0) {
            average_response_time = total_response_time / responded_tasks;
        }

        // 输出详细统计信息
        printDetailedStatistics();
    }

    // 详细的统计信息输出
    void printDetailedStatistics() {
        cout << "\n详细调度结果统计:" << endl;
        cout << "任务ID\t到达时间\t执行时间\t截止时间\t周期\t开始时间\t完成时间\t响应时间\t是否按时\t错过次数" << endl;
        cout << "--------------------------------------------------------------------------------------------------------" << endl;

        double total_response_time = 0.0;
        int total_tasks_with_response = 0;

        for (const auto& task : tasks) {
            if (task.start_time != -1) {
                int response_time = task.start_time - task.arrival_time;
                total_response_time += response_time;
                total_tasks_with_response++;

                bool on_time = task.finish_time <= task.deadline;
                cout << task.id << "\t" << task.arrival_time << "\t\t"
                     << task.execution_time << "\t\t" << task.deadline << "\t\t"
                     << (task.is_periodic ? task.period : 0) << "\t"
                     << task.start_time << "\t\t" << task.finish_time << "\t\t"
                     << response_time << "\t\t"
                     << (on_time ? "是" : "否") << "\t\t"
                     << task.missed_deadlines << endl;
            }
        }

        // 系统性能指标
        cout << "\n系统性能指标:" << endl;
        cout << "总利用率: " << fixed << setprecision(3) << total_utilization << endl;
        cout << "平均响应时间: " << fixed << setprecision(2) << average_response_time << " 时间单位" << endl;
        cout << "总错过截止时间次数: " << total_missed_deadlines << endl;
        cout << "任务完成率: " << fixed << setprecision(1)
             << (static_cast<double>(tasks.size()) / tasks.size() * 100) << "%" << endl;

        // 性能评估
        cout << "\n性能评估:" << endl;
        if (total_missed_deadlines == 0) {
            cout << "✓ 优秀：所有任务按时完成" << endl;
        } else if (total_missed_deadlines <= tasks.size() * 0.1) {
            cout << "✓ 良好：少数任务错过截止时间" << endl;
        } else if (total_missed_deadlines <= tasks.size() * 0.3) {
            cout << "⚠ 一般：较多任务错过截止时间" << endl;
        } else {
            cout << "✗ 较差：大量任务错过截止时间" << endl;
        }
    }

    // 重置调度器状态
    void reset() {
        current_time = 0;
        total_missed_deadlines = 0;
        average_response_time = 0.0;
        for (auto& task : tasks) {
            task.remaining_time = task.execution_time;
            task.start_time = -1;
            task.finish_time = -1;
            task.missed_deadlines = 0;
        }
    }
};

// 示例使用和测试
int main() {
    ImprovedEDFScheduler scheduler(50); // 最大模拟时间50个单位

    cout << "=== 改进EDF调度算法演示 ===" << endl;

    // 添加示例任务：任务ID, 到达时间, 执行时间, 截止时间, 周期, 是否为周期性任务
    scheduler.addTask(1, 0, 3, 7, 0, false);    // 非周期性任务
    scheduler.addTask(2, 2, 2, 6, 0, false);    // 非周期性任务
    scheduler.addTask(3, 4, 2, 8, 0, false);    // 非周期性任务
    scheduler.addTask(4, 0, 1, 5, 10, true);    // 周期性任务，周期10

    // 系统分析
    cout << "\n=== 系统分析 ===" << endl;
    scheduler.isSchedulable();
    scheduler.checkLoadBalance();

    // 执行调度
    cout << "\n=== 调度执行 ===" << endl;
    scheduler.schedule();

    // 性能比较
    cout << "\n=== 性能总结 ===" << endl;
    cout << "改进特性:" << endl;
    cout << "1. 支持周期性任务调度" << endl;
    cout << "2. 动态截止时间计算" << endl;
    cout << "3. 负载均衡分析" << endl;
    cout << "4. 详细的性能指标统计" << endl;
    cout << "5. 改进的可调度性测试" << endl;
    cout << "6. 抢占决策优化" << endl;

    return 0;
}
