#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESS 10

// 进程结构体
typedef struct {
    int id;
    int arriveTime;
    int serviceTime;
    int startTime;
    int finishTime;
    int turnaroundTime;
    float weightedTurnaroundTime;
    int waitingTime;
    float responseRatio;  // 新增：响应比
} Process;

// 函数声明
void inputProcesses(Process processes[], int n);
void generateRandomProcesses(Process processes[], int n);
void HRRN(Process processes[], int n);
void sortByArriveTime(Process processes[], int n);
void calculateTimes(Process processes[], int n);
void printResults(Process processes[], int n);
void printGanttChart(Process processes[], int n);
void printResponseRatioTable(Process processes[], int n, int currentTime);  // 新增：响应比表格

int main() {
    Process processes[MAX_PROCESS];
    int n, inputMethod;

    printf("=== 高响应比优先调度算法 (HRRN) ===\n\n");
    printf("请输入进程数量 (1-%d): ", MAX_PROCESS);
    scanf("%d", &n);

    if (n < 1 || n > MAX_PROCESS) {
        printf("进程数量超出范围!\n");
        return -1;
    }

    printf("\n请选择输入方式:\n");
    printf("1. 手动输入\n");
    printf("2. 随机生成\n");
    printf("选择: ");
    scanf("%d", &inputMethod);

    if (inputMethod == 1) {
        inputProcesses(processes, n);
    } else if (inputMethod == 2) {
        generateRandomProcesses(processes, n);
    } else {
        printf("无效选择!\n");
        return -1;
    }

    // 显示初始进程信息
    printf("\n=== 初始进程信息 ===\n");
    printf("PID\t到达时间\t服务时间\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].arriveTime, processes[i].serviceTime);
    }

    // 执行HRRN算法
    HRRN(processes, n);

    return 0;
}

// 输入进程信息
void inputProcesses(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("输入进程P%d的到达时间: ", i + 1);
        scanf("%d", &processes[i].arriveTime);
        printf("输入进程P%d的服务时间: ", i + 1);
        scanf("%d", &processes[i].serviceTime);
    }
}

// 随机生成进程信息
void generateRandomProcesses(Process processes[], int n) {
    srand((unsigned int)time(NULL));

    printf("\n随机生成的进程信息:\n");
    printf("PID\t到达时间\t服务时间\n");
    printf("------------------------\n");

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arriveTime = rand() % 10;  // 到达时间0-9
        processes[i].serviceTime = rand() % 10 + 1;  // 服务时间1-10
        printf("P%d\t%d\t\t%d\n", processes[i].id, processes[i].arriveTime, processes[i].serviceTime);
    }
}

// 高响应比优先调度算法
void HRRN(Process processes[], int n) {
    printf("\n=== 高响应比优先调度算法 (HRRN) ===\n");

    Process temp[MAX_PROCESS];
    memcpy(temp, processes, sizeof(Process) * n);

    // 按到达时间排序
    sortByArriveTime(temp, n);

    // 显示排序后的进程信息
    printf("\n=== 排序后的进程信息 ===\n");
    printf("PID\t到达时间\t服务时间\n");
    printf("------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", temp[i].id, temp[i].arriveTime, temp[i].serviceTime);
    }

    int currentTime = 0;
    int completed = 0;
    int visited[MAX_PROCESS] = {0};

    printf("\n=== 运算过程显示 ===\n");
    printf("时间\t选择进程\t响应比计算\n");
    printf("--------------------------------\n");

    while (completed < n) {
        // 计算当前时间下所有已到达且未执行进程的响应比
        int selectedIndex = -1;
        float maxResponseRatio = -1.0;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && temp[i].arriveTime <= currentTime) {
                // 计算响应比 = (等待时间 + 服务时间) / 服务时间
                int waitingTime = currentTime - temp[i].arriveTime;
                temp[i].responseRatio = (float)(waitingTime + temp[i].serviceTime) / temp[i].serviceTime;

                if (temp[i].responseRatio > maxResponseRatio) {
                    maxResponseRatio = temp[i].responseRatio;
                    selectedIndex = i;
                }
            }
        }

        // 如果没有进程到达，推进时间到下一个进程的到达时间
        if (selectedIndex == -1) {
            int nextArrival = 1000;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && temp[i].arriveTime < nextArrival) {
                    nextArrival = temp[i].arriveTime;
                }
            }
            printf("%d\t无进程\t\t等待到时间 %d\n", currentTime, nextArrival);
            currentTime = nextArrival;
            continue;
        }

        // 打印响应比计算过程
        printf("%d\tP%d\t\t", currentTime, temp[selectedIndex].id);
        int waitingTime = currentTime - temp[selectedIndex].arriveTime;
        printf("等待时间=%d, 服务时间=%d, 响应比=(%d+%d)/%d=%.2f\n",
               waitingTime, temp[selectedIndex].serviceTime,
               waitingTime, temp[selectedIndex].serviceTime,
               temp[selectedIndex].serviceTime, temp[selectedIndex].responseRatio);

        // 执行选中的进程
        temp[selectedIndex].startTime = currentTime;
        temp[selectedIndex].finishTime = currentTime + temp[selectedIndex].serviceTime;
        temp[selectedIndex].turnaroundTime = temp[selectedIndex].finishTime - temp[selectedIndex].arriveTime;
        temp[selectedIndex].weightedTurnaroundTime = (float)temp[selectedIndex].turnaroundTime / temp[selectedIndex].serviceTime;
        temp[selectedIndex].waitingTime = temp[selectedIndex].startTime - temp[selectedIndex].arriveTime;

        currentTime = temp[selectedIndex].finishTime;
        visited[selectedIndex] = 1;
        completed++;
    }

    // 计算平均值
    float totalTurnaround = 0, totalWeighted = 0, totalWaiting = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaround += temp[i].turnaroundTime;
        totalWeighted += temp[i].weightedTurnaroundTime;
        totalWaiting += temp[i].waitingTime;
    }

    printf("\n=== 调度结果统计 ===\n");
    printf("平均周转时间: %.2f\n", totalTurnaround / n);
    printf("平均带权周转时间: %.2f\n", totalWeighted / n);
    printf("平均等待时间: %.2f\n", totalWaiting / n);

    // 计算处理机利用率
    int totalServiceTime = 0;
    int totalTime = currentTime;
    for (int i = 0; i < n; i++) {
        totalServiceTime += temp[i].serviceTime;
    }
    float cpuUtilization = (float)totalServiceTime / totalTime * 100;
    printf("处理机利用率: %.2f%%\n", cpuUtilization);

    printf("\n=== 运行结果显示 ===\n");
    printResults(temp, n);
    printGanttChart(temp, n);
}

// 按到达时间排序
void sortByArriveTime(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arriveTime > processes[j + 1].arriveTime) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// 打印结果表格
void printResults(Process processes[], int n) {
    printf("\n进程调度结果:\n");
    printf("PID\t到达时间\t服务时间\t开始时间\t完成时间\t周转时间\t带权周转时间\t等待时间\n");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.2f\t\t%d\n",
            processes[i].id,
            processes[i].arriveTime,
            processes[i].serviceTime,
            processes[i].startTime,
            processes[i].finishTime,
            processes[i].turnaroundTime,
            processes[i].weightedTurnaroundTime,
            processes[i].waitingTime);
    }
}

// 打印甘特图
void printGanttChart(Process processes[], int n) {
    printf("\n甘特图:\n");
    printf("时间轴: ");

    // 找到最大完成时间
    int maxTime = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].finishTime > maxTime) {
            maxTime = processes[i].finishTime;
        }
    }

    // 打印时间轴
    for (int i = 0; i <= maxTime; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    // 打印进程执行情况
    for (int i = 0; i < n; i++) {
        printf("P%d:    ", processes[i].id);
        for (int t = 0; t <= maxTime; t++) {
            if (t >= processes[i].startTime && t < processes[i].finishTime) {
                printf("██ ");
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}

// 打印响应比表格（用于调试）
void printResponseRatioTable(Process processes[], int n, int currentTime) {
    printf("\n当前时间 %d 的响应比计算:\n", currentTime);
    printf("PID\t到达时间\t服务时间\t等待时间\t响应比\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (processes[i].arriveTime <= currentTime) {
            int waitingTime = currentTime - processes[i].arriveTime;
            float responseRatio = (float)(waitingTime + processes[i].serviceTime) / processes[i].serviceTime;
            printf("P%d\t%d\t\t%d\t\t%d\t\t%.2f\n",
                processes[i].id,
                processes[i].arriveTime,
                processes[i].serviceTime,
                waitingTime,
                responseRatio);
        }
    }
    printf("\n");
}
