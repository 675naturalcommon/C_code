#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_REQUESTS 100
#define MAX_TRACK 200

// 函数声明
void inputRequests(int requests[], int *n, int *head);
void generateRandomRequests(int requests[], int *n, int *head);
void printRequests(int requests[], int n, int head);
void runDiskSchedulingAlgorithm(int requests[], int n, int head);
void printAccessChain(int sequence[], int moves[], int count, int head);
void sortRequests(int requests[], int n, int sortedRequests[]);

// 算法函数声明
void fcfs(int requests[], int n, int head);
void sstf(int requests[], int n, int head);
void scan(int requests[], int n, int head, int direction);
void cscan(int requests[], int n, int head, int direction);
void look(int requests[], int n, int head, int direction);
void clook(int requests[], int n, int head, int direction);
void compareAlgorithms(int requests[], int n, int head);

int main() {
    int requests[MAX_REQUESTS];
    int n = 0;
    int head = 0;
    int inputMethod;

    printf("=== 磁盘调度算法模拟程序 ===\n\n");

    // 输入请求序列
    printf("请选择输入方式:\n");
    printf("1. 手动输入\n");
    printf("2. 随机生成\n");
    printf("选择: ");
    scanf("%d", &inputMethod);

    if (inputMethod == 1) {
        inputRequests(requests, &n, &head);
    } else if (inputMethod == 2) {
        generateRandomRequests(requests, &n, &head);
    } else {
        printf("无效选择!\n");
        return -1;
    }

    // 显示输入的请求序列
    printf("\n=== 输入的请求序列 ===\n");
    printRequests(requests, n, head);

    // 运行磁盘调度算法
    printf("\n\n=== 开始运行磁盘调度算法 ===\n");
    runDiskSchedulingAlgorithm(requests, n, head);

    printf("\n=== 所有算法运行完成 ===\n");
    return 0;
}

// 手动输入请求序列
void inputRequests(int requests[], int *n, int *head) {
    printf("请输入磁道请求访问序列（第一个为当前磁头位置，后续为请求序列）:\n");
    char line[1000];
    getchar(); // 清除换行符
    fgets(line, sizeof(line), stdin);

    char *token = strtok(line, " \t\n");
    int count = 0;

    while (token != NULL && count < MAX_REQUESTS) {
        int value = atoi(token);
        if (value < 0 || value >= MAX_TRACK) {
            printf("磁道号 %d 超出范围! 请重新输入\n", value);
            return inputRequests(requests, n, head);
        }

        if (count == 0) *head = value;
        else requests[count - 1] = value;
        count++;
        token = strtok(NULL, " \t\n");
    }

    *n = count - 1;
    printf("当前磁头位置: %d\n", *head);
    printf("请求序列: ");
    for (int i = 0; i < *n; i++) printf("%d ", requests[i]);
    printf("\n");
}

// 随机生成请求序列
void generateRandomRequests(int requests[], int *n, int *head) {
    srand((unsigned int)time(NULL));

    *head = rand() % MAX_TRACK;
    *n = rand() % 10 + 5;  // 5-14个请求

    printf("随机生成的磁头位置: %d\n", *head);
    printf("请求数量: %d\n请求序列: ", *n);

    for (int i = 0; i < *n; i++) {
        requests[i] = rand() % MAX_TRACK;
        printf("%d ", requests[i]);
    }
    printf("\n");
}

// 打印请求序列
void printRequests(int requests[], int n, int head) {
    printf("当前磁头位置: %d\n", head);
    printf("请求序列 (%d个): ", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");
}

// 运行所有磁盘调度算法
void runDiskSchedulingAlgorithm(int requests[], int n, int head) {
    int originalRequests[MAX_REQUESTS];
    memcpy(originalRequests, requests, sizeof(int) * n);

    // 1. 先来先服务算法 (FCFS)
    printf("\n=== 先来先服务算法 (FCFS) ===\n");
    fcfs(requests, n, head);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 2. 最短寻道时间优先算法 (SSTF)
    printf("\n=== 最短寻道时间优先算法 (SSTF) ===\n");
    sstf(requests, n, head);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 3. 扫描算法 (SCAN) - 向磁道号增加方向移动
    printf("\n=== 扫描算法 (SCAN) - 向磁道号增加方向移动 ===\n");
    scan(requests, n, head, 1);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 4. 扫描算法 (SCAN) - 向磁道号减少方向移动
    printf("\n=== 扫描算法 (SCAN) - 向磁道号减少方向移动 ===\n");
    scan(requests, n, head, 2);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 5. 循环扫描算法 (CSCAN) - 向磁道号增加方向移动
    printf("\n=== 循环扫描算法 (CSCAN) - 向磁道号增加方向移动 ===\n");
    cscan(requests, n, head, 1);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 6. 循环扫描算法 (CSCAN) - 向磁道号减少方向移动
    printf("\n=== 循环扫描算法 (CSCAN) - 向磁道号减少方向移动 ===\n");
    cscan(requests, n, head, 2);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 7. LOOK算法 (SCAN改良版) - 向磁道号增加方向移动
    printf("\n=== LOOK算法 (SCAN改良版) - 向磁道号增加方向移动 ===\n");
    look(requests, n, head, 1);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 8. LOOK算法 (SCAN改良版) - 向磁道号减少方向移动
    printf("\n=== LOOK算法 (SCAN改良版) - 向磁道号减少方向移动 ===\n");
    look(requests, n, head, 2);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 9. CLOOK算法 (CSCAN改良版) - 向磁道号增加方向移动
    printf("\n=== CLOOK算法 (CSCAN改良版) - 向磁道号增加方向移动 ===\n");
    clook(requests, n, head, 1);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 10. CLOOK算法 (CSCAN改良版) - 向磁道号减少方向移动
    printf("\n=== CLOOK算法 (CSCAN改良版) - 向磁道号减少方向移动 ===\n");
    clook(requests, n, head, 2);
    memcpy(requests, originalRequests, sizeof(int) * n);

    // 11. 算法比较
    printf("\n=== 算法性能比较 ===\n");
    compareAlgorithms(requests, n, head);
}

// 打印访问链（满足用户要求）
void printAccessChain(int sequence[], int moves[], int count, int head) {
    int totalMove = 0;

    // 1. 显示初始位置
    printf("初始位置: %d\n", head);

    // 2. 显示访问每个磁道时，磁头移动的数量
    printf("\n访问过程:\n");
    printf("序号\t目标磁道\t移动距离\t方向\n");
    printf("------------------------------------------------\n");

    int current = head;
    for (int i = 0; i < count; i++) {
        int target = sequence[i];
        int move = moves[i];
        totalMove += move;

        // 判断方向
        char direction[10];
        if (target > current) {
            strcpy(direction, "增加");
        } else if (target < current) {
            strcpy(direction, "减少");
        } else {
            strcpy(direction, "不变");
        }

        printf("%d\t%d\t\t%d\t\t%s\n", i+1, target, move, direction);
        current = target;
    }

    // 3. 显示总移动距离和平均寻道长度
    printf("\n总移动距离: %d\n", totalMove);
    printf("平均寻道长度: %.2f\n", (float)totalMove / count);
}

// 排序请求序列
void sortRequests(int requests[], int n, int sortedRequests[]) {
    memcpy(sortedRequests, requests, sizeof(int) * n);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sortedRequests[j] > sortedRequests[j + 1]) {
                int temp = sortedRequests[j];
                sortedRequests[j] = sortedRequests[j + 1];
                sortedRequests[j + 1] = temp;
            }
        }
    }
}

// 先来先服务算法
void fcfs(int requests[], int n, int head) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];

    int current = head;
    for (int i = 0; i < n; i++) {
        moves[i] = abs(current - requests[i]);
        sequence[i] = requests[i];
        current = requests[i];
    }

    printAccessChain(sequence, moves, n, head);
}

// 最短寻道时间优先算法
void sstf(int requests[], int n, int head) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int visited[MAX_REQUESTS] = {0};

    int current = head;
    int count = 0;

    while (count < n) {
        int minDistance = MAX_TRACK * 2;
        int minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(current - requests[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = i;
                }
            }
        }

        visited[minIndex] = 1;
        moves[count] = minDistance;
        sequence[count] = requests[minIndex];
        current = requests[minIndex];
        count++;
    }

    printAccessChain(sequence, moves, n, head);
}

// 扫描算法 (SCAN)
void scan(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        if (current < MAX_TRACK - 1) {
            moves[count] = abs(current - (MAX_TRACK - 1));
            sequence[count] = MAX_TRACK - 1;
            current = MAX_TRACK - 1;
            count++;
        }

        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] < head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    } else {  // 减少方向
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        if (current > 0) {
            moves[count] = abs(current - 0);
            sequence[count] = 0;
            current = 0;
            count++;
        }

        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] > head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    }

    printAccessChain(sequence, moves, count, head);
}

// 循环扫描算法 (CSCAN)
void cscan(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        if (current < MAX_TRACK - 1) {
            moves[count] = abs(current - (MAX_TRACK - 1));
            sequence[count] = MAX_TRACK - 1;
            current = MAX_TRACK - 1;
            count++;
        }

        moves[count] = 0;
        sequence[count] = 0;
        current = 0;
        count++;

        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] < head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    } else {  // 减少方向
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        if (current > 0) {
            moves[count] = abs(current - 0);
            sequence[count] = 0;
            current = 0;
            count++;
        }

        moves[count] = 0;
        sequence[count] = MAX_TRACK - 1;
        current = MAX_TRACK - 1;
        count++;

        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] > head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    }

    printAccessChain(sequence, moves, count, head);
}

// LOOK算法 (SCAN改良版)
void look(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] < head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    } else {  // 减少方向
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] > head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    }

    printAccessChain(sequence, moves, count, head);
}

// CLOOK算法 (CSCAN改良版)
void clook(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 跳转到最小请求
        int minRequest = MAX_TRACK;
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] < head && sortedRequests[i] < minRequest) {
                minRequest = sortedRequests[i];
            }
        }

        if (minRequest < MAX_TRACK) {
            moves[count] = 0;
            sequence[count] = minRequest;
            current = minRequest;
            count++;

            for (int i = 0; i < n; i++) {
                if (sortedRequests[i] < head && sortedRequests[i] >= minRequest) {
                    if (sortedRequests[i] == minRequest && count > 1) continue;
                    moves[count] = abs(current - sortedRequests[i]);
                    sequence[count] = sortedRequests[i];
                    current = sortedRequests[i];
                    count++;
                }
            }
        }
    } else {  // 减少方向
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 跳转到最大请求
        int maxRequest = -1;
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] > head && sortedRequests[i] > maxRequest) {
                maxRequest = sortedRequests[i];
            }
        }

        if (maxRequest > -1) {
            moves[count] = 0;
            sequence[count] = maxRequest;
            current = maxRequest;
            count++;

            for (int i = n - 1; i >= 0; i--) {
                if (sortedRequests[i] > head && sortedRequests[i] <= maxRequest) {
                    if (sortedRequests[i] == maxRequest && count > 1) continue;
                    moves[count] = abs(current - sortedRequests[i]);
                    sequence[count] = sortedRequests[i];
                    current = sortedRequests[i];
                    count++;
                }
            }
        }
    }

    printAccessChain(sequence, moves, count, head);
}

// 比较所有算法
void compareAlgorithms(int requests[], int n, int head) {
    printf("算法名称\t\t总移动距离\t平均寻道长度\n");
    printf("------------------------------------------------\n");

    // 计算FCFS
    int current = head;
    int totalFCFS = 0;
    for (int i = 0; i < n; i++) {
        totalFCFS += abs(current - requests[i]);
        current = requests[i];
    }
    printf("FCFS\t\t\t%d\t\t%.2f\n", totalFCFS, (float)totalFCFS / n);

    // 计算SSTF
    int visited[MAX_REQUESTS] = {0};
    current = head;
    int totalSSTF = 0;
    int count = 0;
    while (count < n) {
        int minDistance = MAX_TRACK * 2;
        int minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(current - requests[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = i;
                }
            }
        }
        visited[minIndex] = 1;
        totalSSTF += minDistance;
        current = requests[minIndex];
        count++;
    }
    printf("SSTF\t\t\t%d\t\t%.2f\n", totalSSTF, (float)totalSSTF / n);

    // 计算SCAN增加方向
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);
    current = head;
    int totalSCAN1 = 0;
    for (int i = 0; i < n; i++) {
        if (sortedRequests[i] >= current) {
            totalSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    if (current < MAX_TRACK - 1) {
        totalSCAN1 += abs(current - (MAX_TRACK - 1));
        current = MAX_TRACK - 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (sortedRequests[i] < head) {
            totalSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("SCAN(增加方向)\t\t%d\t\t%.2f\n", totalSCAN1, (float)totalSCAN1 / n);

    // 计算SCAN减少方向
    current = head;
    int totalSCAN2 = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (sortedRequests[i] <= current) {
            totalSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    if (current > 0) {
        totalSCAN2 += abs(current - 0);
        current = 0;
    }
    for (int i = 0; i < n; i++) {
        if (sortedRequests[i] > head) {
            totalSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("SCAN(减少方向)\t\t%d\t\t%.2f\n", totalSCAN2, (float)totalSCAN2 / n);

    // 计算CSCAN增加方向
    current = head;
    int totalCSCAN1 = 0;
    for (int i = 0; i < n; i++) {
        if (sortedRequests[i] >= current) {
            totalCSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    if (current < MAX_TRACK - 1) {
        totalCSCAN1 += abs(current - (MAX_TRACK - 1));
        current = MAX_TRACK - 1;
    }
    current = 0;
    for (int i = 0; i < n; i++) {
        if (sortedRequests[i] < head) {
            totalCSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("CSCAN(增加方向)\t\t%d\t\t%.2f\n", totalCSCAN1, (float)totalCSCAN1 / n);

    // 计算CSCAN减少方向
    current = head;
    int totalCSCAN2 = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (sortedRequests[i] <= current) {
            totalCSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    if (current > 0) {
        totalCSCAN2 += abs(current - 0);
        current = 0;
    }
    current = MAX_TRACK - 1;
    for (int i = n - 1; i >= 0; i--) {
        if (sortedRequests[i] > head) {
            totalCSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("CSCAN(减少方向)\t\t%d\t\t%.2f\n", totalCSCAN2, (float)totalCSCAN2 / n);

    // LOOK和CLOOK近似值
    printf("LOOK(增加方向)\t\t≈%d\t\t≈%.2f\n", totalSCAN1, (float)totalSCAN1 / n);
    printf("LOOK(减少方向)\t\t≈%d\t\t≈%.2f\n", totalSCAN2, (float)totalSCAN2 / n);
    printf("CLOOK(增加方向)\t\t≈%d\t\t≈%.2f\n", totalCSCAN1, (float)totalCSCAN1 / n);
    printf("CLOOK(减少方向)\t\t≈%d\t\t≈%.2f\n", totalCSCAN2, (float)totalCSCAN2 / n);
}
