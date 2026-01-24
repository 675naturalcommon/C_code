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
    int waitingTime;  // 新增：等待时间
} Process;

// 函数声明
void inputProcesses(Process processes[], int n);
void generateRandomProcesses(Process processes[], int n);
void FCFS(Process processes[], int n);
void SJF(Process processes[], int n);
void sortByArriveTime(Process processes[], int n);
void sortByServiceTime(Process processes[], int n);
void calculateTimes(Process processes[], int n);
void printResults(Process processes[], int n);
void printGanttChart(Process processes[], int n);  // 新增：甘特图
void compareAlgorithms(Process processes[], int n);  // 新增：算法比较

int main() {
    Process processes[MAX_PROCESS];
    int n, choice, inputMethod;

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

    printf("\n请选择调度算法:\n");
    printf("1. FCFS (先来先服务)\n");
    printf("2. SJF (短作业优先)\n");
    printf("3. 比较两种算法\n");
    printf("选择: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        FCFS(processes, n);
        break;
    case 2:
        SJF(processes, n);
        break;
    case 3:
        compareAlgorithms(processes, n);
        break;
    default:
        printf("无效选择!\n");
    }

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

// FCFS调度算法
void FCFS(Process processes[], int n) {
    printf("\n=== FCFS调度算法 ===\n");
    sortByArriveTime(processes, n);  // 按到达时间排序
    calculateTimes(processes, n);    // 计算各项时间
    printResults(processes, n);      // 输出结果
}

// SJF调度算法
void SJF(Process processes[], int n) {
    printf("\n=== SJF调度算法 ===\n");

    // 改进的SJF：考虑到达时间
    Process temp[MAX_PROCESS];
    memcpy(temp, processes, sizeof(Process) * n);

    // 按到达时间排序
    sortByArriveTime(temp, n);

    int currentTime = 0;
    int completed = 0;
    int visited[MAX_PROCESS] = {0};

    while (completed < n) {
        int shortestIndex = -1;
        int shortestTime = 1000;  // 一个大数

        // 找到当前已到达且未执行的进程中服务时间最短的
        for (int i = 0; i < n; i++) {
            if (!visited[i] && temp[i].arriveTime <= currentTime) {
                if (temp[i].serviceTime < shortestTime) {
                    shortestTime = temp[i].serviceTime;
                    shortestIndex = i;
                }
            }
        }

        // 如果没有进程到达，推进时间到下一个进程的到达时间
        if (shortestIndex == -1) {
            int nextArrival = 1000;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && temp[i].arriveTime < nextArrival) {
                    nextArrival = temp[i].arriveTime;
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // 执行选中的进程
        temp[shortestIndex].startTime = currentTime;
        temp[shortestIndex].finishTime = currentTime + temp[shortestIndex].serviceTime;
        temp[shortestIndex].turnaroundTime = temp[shortestIndex].finishTime - temp[shortestIndex].arriveTime;
        temp[shortestIndex].weightedTurnaroundTime = (float)temp[shortestIndex].turnaroundTime / temp[shortestIndex].serviceTime;
        temp[shortestIndex].waitingTime = temp[shortestIndex].startTime - temp[shortestIndex].arriveTime;

        currentTime = temp[shortestIndex].finishTime;
        visited[shortestIndex] = 1;
        completed++;
    }

    // 计算平均值
    float totalTurnaround = 0, totalWeighted = 0, totalWaiting = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaround += temp[i].turnaroundTime;
        totalWeighted += temp[i].weightedTurnaroundTime;
        totalWaiting += temp[i].waitingTime;
    }

    printf("\n平均周转时间: %.2f\n", totalTurnaround / n);
    printf("平均带权周转时间: %.2f\n", totalWeighted / n);
    printf("平均等待时间: %.2f\n", totalWaiting / n);

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

// 按服务时间排序
void sortByServiceTime(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].serviceTime > processes[j + 1].serviceTime) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// 计算各项时间
void calculateTimes(Process processes[], int n) {
    int currentTime = 0;
    float totalTurnaround = 0, totalWeighted = 0, totalWaiting = 0;

    for (int i = 0; i < n; i++) {
        // 开始时间
        if (currentTime < processes[i].arriveTime) {
            processes[i].startTime = processes[i].arriveTime;
        }
        else {
            processes[i].startTime = currentTime;
        }

        // 完成时间
        processes[i].finishTime = processes[i].startTime + processes[i].serviceTime;

        // 周转时间
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arriveTime;

        // 带权周转时间
        processes[i].weightedTurnaroundTime = (float)processes[i].turnaroundTime / processes[i].serviceTime;

        // 等待时间
        processes[i].waitingTime = processes[i].startTime - processes[i].arriveTime;

        // 更新当前时间
        currentTime = processes[i].finishTime;

        // 累加用于计算平均值
        totalTurnaround += processes[i].turnaroundTime;
        totalWeighted += processes[i].weightedTurnaroundTime;
        totalWaiting += processes[i].waitingTime;
    }

    // 输出平均值
    printf("\n平均周转时间: %.2f\n", totalTurnaround / n);
    printf("平均带权周转时间: %.2f\n", totalWeighted / n);
    printf("平均等待时间: %.2f\n", totalWaiting / n);
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

// 比较两种算法
void compareAlgorithms(Process processes[], int n) {
    printf("\n=== 算法比较 ===\n");

    // 备份原始进程数据
    Process original[MAX_PROCESS];
    memcpy(original, processes, sizeof(Process) * n);

    // FCFS算法
    printf("\n--- FCFS算法 ---\n");
    FCFS(processes, n);

    // 恢复原始数据
    memcpy(processes, original, sizeof(Process) * n);

    // SJF算法
    printf("\n--- SJF算法 ---\n");
    SJF(processes, n);

    printf("\n=== 比较总结 ===\n");
    printf("FCFS算法：简单公平，但可能导致短作业等待时间过长\n");
    printf("SJF算法：能有效减少平均等待时间，但需要预知作业执行时间\n");
}
