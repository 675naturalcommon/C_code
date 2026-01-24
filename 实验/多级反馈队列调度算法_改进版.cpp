#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

/* ========= 进程结构 ========= */
struct PCB {
    char name[10];
    int pid;
    int arriveTime;
    int serviceTime;
    int remainingTime;
    int queueLevel;
    int lastScheduledCount;
    int startTime;
    int finishTime;
    bool joined; // <--- 新增：标记是否已进入系统队列
    PCB* next;
};

/* ========= 队列结构（链表实现） ========= */
struct Queue {
    PCB* head;
    PCB* tail;
    int timeSlice;
    int size;
};

/* ========= 全局变量 ========= */
Queue queues[5];
int currentTime = 0;
int processCount = 5;
int completedCount = 0;
PCB* allProcesses[10];  // 存储所有进程指针

/* ========= 随机整数 ========= */
int randBetween(int l, int r) {
    return rand() % (r - l + 1) + l;
}

/* ========= 初始化队列 ========= */
void initQueues() {
    bool used[17] = {false};
    for (int i = 0; i < 5; i++) {
        queues[i].head = queues[i].tail = NULL;
        queues[i].size = 0;
        int t;
        do {
            t = randBetween(1, 16);
        } while (used[t]);
        used[t] = true;
        queues[i].timeSlice = t;
    }
}

/* ========= 入队 ========= */
void enqueue(int level, PCB* p) {
    p->queueLevel = level;
    p->next = NULL;
    if (!queues[level].head) {
        queues[level].head = queues[level].tail = p;
    } else {
        queues[level].tail->next = p;
        queues[level].tail = p;
    }
    queues[level].size++;
}

/* ========= 出队 ========= */
PCB* dequeue(int level) {
    PCB* p = queues[level].head;
    if (!p) return NULL;
    queues[level].head = p->next;
    if (!queues[level].head)
        queues[level].tail = NULL;
    queues[level].size--;
    p->next = NULL;
    return p;
}

/* ========= 显示系统状态 ========= */
void showSystemState(const char* event = NULL) {
    if (event) {
        cout << "\n" << string(60, '=') << endl;
        cout << "事件: " << event << endl;
        cout << string(60, '=') << endl;
    }

    cout << "\n【系统时间：" << currentTime << "】\n";
    cout << "队列级别\t时间片大小\t进程数量\t进程列表\n";
    cout << "--------\t----------\t--------\t--------\n";

    for (int i = 0; i < 5; i++) {
        cout << "队列" << i+1 << "\t\t" << queues[i].timeSlice
             << "\t\t" << queues[i].size << "\t\t";

        if (queues[i].size == 0) {
            cout << "空";
        } else {
            PCB* p = queues[i].head;
            int pos = 1;
            while (p) {
                cout << p->name << "(位置:" << pos++ << ",剩余:" << p->remainingTime << ") ";
                p = p->next;
            }
        }
        cout << endl;
    }
}

/* ========= 显示进程信息 ========= */
void showProcessInfo(PCB* p, const char* action) {
    cout << "\n" << string(40, '-') << endl;
    cout << action << " - " << p->name
         << "(PID:" << p->pid
         << ") 到达:" << p->arriveTime
         << " 总需:" << p->serviceTime
         << " 剩余:" << p->remainingTime << endl;
    cout << "当前队列: " << (p->queueLevel + 1)
         << ", 连续调度次数: " << p->lastScheduledCount << endl;
    cout << string(40, '-') << endl;
}

/* ========= 创建进程 ========= */
PCB* createProcess(int index) {
    PCB* p = new PCB;
    sprintf(p->name, "P%d", index);
    p->pid = randBetween(0, 3500);
    p->arriveTime = randBetween(0, 100);
    p->serviceTime = randBetween(20, 100);
    p->remainingTime = p->serviceTime;
    p->queueLevel = 0;
    p->lastScheduledCount = 0;
    p->startTime = -1;
    p->finishTime = -1;
    p->joined = false; // <--- 初始化为 false
    p->next = NULL;
    return p;
}

/* ========= 检查新到达的进程 ========= */
void checkNewArrivals() {
    for (int i = 0; i < processCount; i++) {
        PCB* p = allProcesses[i];
        // 修改判断条件：只有到达时间匹配 且 还没加入过系统 的进程才入队
        if (p->arriveTime == currentTime && !p->joined) {

            p->queueLevel = 0;
            p->lastScheduledCount = 0;
            p->joined = true; // <--- 标记为已加入，防止重复入队
            enqueue(0, p);

            showProcessInfo(p, "新进程进入系统");
            showSystemState("新进程进入后队列状态");
        }
    }
}

/* ========= 调度主循环 ========= */
void schedule() {
    cout << "\n" << string(60, '=') << endl;
    cout << "开始多级反馈队列调度模拟" << endl;
    cout << string(60, '=') << endl;

    int maxTime = 1000;  // 防止无限循环

    while (completedCount < processCount && currentTime < maxTime) {
        // 检查新到达的进程
        checkNewArrivals();

        // 查找最高优先级非空队列
        int selectedQueue = -1;
        for (int i = 0; i < 5; i++) {
            if (queues[i].size > 0) {
                selectedQueue = i;
                break;
            }
        }

        if (selectedQueue == -1) {
            // 所有队列为空，时间推进
            currentTime++;
            continue;
        }

        // 从队列中取出进程
        PCB* p = dequeue(selectedQueue);

        // 记录开始时间
        if (p->startTime == -1) {
            p->startTime = currentTime;
        }

        int slice = queues[selectedQueue].timeSlice;
        int runTime = (p->remainingTime < slice) ? p->remainingTime : slice;

        cout << "\n时间 " << currentTime << ": 调度 " << p->name
             << " 从队列" << (selectedQueue + 1)
             << " 执行 " << runTime << " 单位时间" << endl;

        // 模拟时间流逝
        for (int t = 0; t < runTime; t++) {
            currentTime++;
            p->remainingTime--;
            checkNewArrivals();  // 检查在此期间到达的新进程
        }

        if (p->remainingTime == 0) {
            // 进程完成
            p->finishTime = currentTime;
            completedCount++;

            showProcessInfo(p, "进程离开系统");
            showSystemState("进程离开后队列状态");

            cout << "✓ 进程 " << p->name << " 已完成!" << endl;
            cout << "  开始时间: " << p->startTime
                 << ", 完成时间: " << p->finishTime
                 << ", 周转时间: " << (p->finishTime - p->arriveTime) << endl;
        } else {
            // 进程未完成，需要重新加入队列
            if (selectedQueue == 4) {
                // 最后一级队列
                p->lastScheduledCount++;
                if (p->lastScheduledCount >= 2) {
                    cout << "⚠️  特殊规则触发: " << p->name
                         << " 在最后一级队列中连续调度" << p->lastScheduledCount
                         << "次仍未完成，返回第一级队列!" << endl;
                    p->lastScheduledCount = 0;
                    enqueue(0, p);
                } else {
                    cout << "  " << p->name << " 时间片用完，留在队列5" << endl;
                    enqueue(4, p);
                }
            } else {
                // 降级到下一级队列
                cout << "  " << p->name << " 时间片用完，降级到队列" << (selectedQueue + 2) << endl;
                enqueue(selectedQueue + 1, p);
            }
            showSystemState("进程重新加入后队列状态");
        }
    }

    // 调度结束
    cout << "\n" << string(60, '=') << endl;
    if (completedCount == processCount) {
        cout << "所有进程已完成调度!" << endl;
    } else {
        cout << "达到最大时间限制 " << maxTime << "，调度提前结束!" << endl;
    }
    cout << string(60, '=') << endl;
}

/* ========= 打印统计信息 ========= */
void printStatistics() {
    cout << "\n最终统计信息:" << endl;
    cout << "名称\tPID\t到达\t服务\t开始\t完成\t周转\t等待" << endl;
    cout << "----\t---\t----\t----\t----\t----\t----\t----" << endl;

    double totalTurnaround = 0;
    double totalWaiting = 0;

    for (int i = 0; i < processCount; i++) {
        PCB* p = allProcesses[i];
        int turnaround = p->finishTime - p->arriveTime;
        int waiting = turnaround - p->serviceTime;

        totalTurnaround += turnaround;
        totalWaiting += waiting;

        cout << p->name << "\t" << p->pid << "\t"
             << p->arriveTime << "\t" << p->serviceTime << "\t"
             << p->startTime << "\t" << p->finishTime << "\t"
             << turnaround << "\t" << waiting << endl;
    }

    cout << "\n平均周转时间: " << fixed << setprecision(2)
         << (totalTurnaround / processCount) << endl;
    cout << "平均等待时间: " << fixed << setprecision(2)
         << (totalWaiting / processCount) << endl;
    cout << "总调度时间: " << currentTime << " 单位时间" << endl;

    cout << "\n队列配置总结:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "队列" << (i + 1) << ": 时间片大小 = " << queues[i].timeSlice
             << ", 优先级 = " << (i + 1) << endl;
    }
}

/* ========= 主函数 ========= */
int main() {
    srand((unsigned)time(NULL));

    cout << "╔══════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                   多级反馈队列调度算法模拟器 (改进版)                       ║" << endl;
    cout << "║                 Multilevel Feedback Queue Scheduler (Improved)               ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝" << endl;

    cout << "\n算法规则说明:" << endl;
    cout << "1. 系统包含5级队列，优先级从高到低（队列1最高，队列5最低）" << endl;
    cout << "2. 每级队列时间片大小为1~16之间的随机数，且各不相同" << endl;
    cout << "3. 新进程进入最高优先级队列（队列1）" << endl;
    cout << "4. 当前队列时间片用完后，进程进入下一级队列参与调度" << endl;
    cout << "5. 最后一级队列（队列5）中的进程时间片耗尽时，返回本级队列继续排队" << endl;
    cout << "6. 最后一级队列中的进程，如果连续被调度两次仍未运行结束，则返回至第一级队列" << endl;
    cout << "7. 高优先级队列中的进程优先于低优先级队列中的进程" << endl;

    cout << "\n进程生成规则:" << endl;
    cout << "- 进程PID: 0~3500之间的随机整数" << endl;
    cout << "- 到达时间: 0~100之间的随机数" << endl;
    cout << "- 服务时间: 20~100之间的随机数" << endl;
    cout << "- 至少模拟5个进程" << endl;

    cout << "\n" << string(80, '=') << endl;
    cout << "开始生成随机进程和队列配置..." << endl;
    cout << string(80, '=') << endl;

    // 初始化队列
    initQueues();

    // 创建进程
    processCount = 5 + randBetween(0, 2);  // 5-7个进程
    for (int i = 0; i < processCount; i++) {
        allProcesses[i] = createProcess(i + 1);
    }

    // 显示初始配置
    cout << "\n系统初始化完成 - 当前时间: " << currentTime << endl;
    cout << string(60, '=') << endl;

    cout << "\n队列配置:" << endl;
    cout << "队列级别\t优先级\t时间片大小" << endl;
    cout << "--------\t------\t----------" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "队列" << (i + 1) << "\t\t" << (i + 1) << "\t" << queues[i].timeSlice << endl;
    }

    cout << "\n进程基本信息:" << endl;
    cout << "名称\tPID\t到达时间\t服务时间\t剩余时间" << endl;
    cout << "----\t---\t--------\t--------\t--------" << endl;
    for (int i = 0; i < processCount; i++) {
        PCB* p = allProcesses[i];
        cout << p->name << "\t" << p->pid << "\t" << p->arriveTime
             << "\t\t" << p->serviceTime << "\t\t" << p->remainingTime << endl;
    }

    showSystemState("初始队列状态");

    // 开始调度
    schedule();

    // 打印统计信息
    printStatistics();

    // 清理内存
    for (int i = 0; i < processCount; i++) {
        delete allProcesses[i];
    }

    cout << "\n模拟完成!" << endl;
    system("pause");
    return 0;
}

