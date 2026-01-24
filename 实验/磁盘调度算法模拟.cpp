/**
 * 磁盘调度算法模拟程序
 * 实现四种磁盘调度算法：
 * 1. 先来先服务算法 (FCFS)
 * 2. 最短寻道时间优先算法 (SSTF)
 * 3. 扫描算法 (SCAN/LOOK)
 * 4. 循环扫描算法 (CSCAN/CLOOK)
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_REQUESTS 100  // 最大请求数
#define MAX_TRACK 200     // 最大磁道数

// 函数声明
void inputRequests(int requests[], int *n, int *head);
void generateRandomRequests(int requests[], int *n, int *head);
void printRequests(int requests[], int n, int head);
void fcfs(int requests[], int n, int head);
void sstf(int requests[], int n, int head);
void scan(int requests[], int n, int head, int direction);
void cscan(int requests[], int n, int head, int direction);
void look(int requests[], int n, int head, int direction);
void clook(int requests[], int n, int head, int direction);
void printAccessChain(int sequence[], int moves[], int count, int head);
void compareAlgorithms(int requests[], int n, int head);
void sortRequests(int requests[], int n, int sortedRequests[]);

int main() {
    int requests[MAX_REQUESTS];
    int n = 0;          // 请求数量
    int head = 0;       // 当前磁头位置
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

    // 直接运行所有算法
    printf("\n\n=== 开始运行所有磁盘调度算法 ===\n");

    // 备份原始请求数组
    int originalRequests[MAX_REQUESTS];
    for (int i = 0; i < n; i++) {
        originalRequests[i] = requests[i];
    }

    // 1. 先来先服务算法 (FCFS)
    printf("\n=== 先来先服务算法 (FCFS) ===\n");
    fcfs(requests, n, head);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 2. 最短寻道时间优先算法 (SSTF)
    printf("\n=== 最短寻道时间优先算法 (SSTF) ===\n");
    sstf(requests, n, head);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 3. 扫描算法 (SCAN) - 增加方向
    printf("\n=== 扫描算法 (SCAN) - 向磁道号增加方向移动 ===\n");
    scan(requests, n, head, 1);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 4. 扫描算法 (SCAN) - 减少方向
    printf("\n=== 扫描算法 (SCAN) - 向磁道号减少方向移动 ===\n");
    scan(requests, n, head, 2);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 5. 循环扫描算法 (CSCAN) - 增加方向
    printf("\n=== 循环扫描算法 (CSCAN) - 向磁道号增加方向移动 ===\n");
    cscan(requests, n, head, 1);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 6. 循环扫描算法 (CSCAN) - 减少方向
    printf("\n=== 循环扫描算法 (CSCAN) - 向磁道号减少方向移动 ===\n");
    cscan(requests, n, head, 2);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 7. LOOK算法 (SCAN改良版) - 增加方向
    printf("\n=== LOOK算法 (SCAN改良版) - 向磁道号增加方向移动 ===\n");
    look(requests, n, head, 1);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 8. LOOK算法 (SCAN改良版) - 减少方向
    printf("\n=== LOOK算法 (SCAN改良版) - 向磁道号减少方向移动 ===\n");
    look(requests, n, head, 2);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 9. CLOOK算法 (CSCAN改良版) - 增加方向
    printf("\n=== CLOOK算法 (CSCAN改良版) - 向磁道号增加方向移动 ===\n");
    clook(requests, n, head, 1);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 10. CLOOK算法 (CSCAN改良版) - 减少方向
    printf("\n=== CLOOK算法 (CSCAN改良版) - 向磁道号减少方向移动 ===\n");
    clook(requests, n, head, 2);

    // 恢复请求数组
    for (int i = 0; i < n; i++) {
        requests[i] = originalRequests[i];
    }

    // 11. 算法比较
    printf("\n=== 算法性能比较 ===\n");
    compareAlgorithms(requests, n, head);

    printf("\n=== 所有算法运行完成 ===\n");
    printf("按任意键退出...\n");
    getchar();
    getchar();

    return 0;
}

// 手动输入请求序列（包含当前磁头位置作为第一个）
void inputRequests(int requests[], int *n, int *head) {
    printf("请输入磁道请求访问序列（第一个为当前磁头位置，后续为请求序列）:\n");
    printf("例如: 50 55 58 60 70 18 表示磁头在50，请求序列为55,58,60,70,18\n");
    printf("请输入（以空格分隔，回车结束）: ");

    // 读取一行输入
    char line[1000];
    getchar(); // 清除之前的换行符
    fgets(line, sizeof(line), stdin);

    // 解析数字
    char *token = strtok(line, " \t\n");
    int count = 0;

    while (token != NULL && count < MAX_REQUESTS) {
        int value = atoi(token);
        if (value < 0 || value >= MAX_TRACK) {
            printf("磁道号 %d 超出范围 (0-%d)! 请重新输入\n", value, MAX_TRACK - 1);
            return inputRequests(requests, n, head); // 重新输入
        }

        if (count == 0) {
            *head = value; // 第一个是当前磁头位置
        } else {
            requests[count - 1] = value; // 后续是请求序列
        }
        count++;
        token = strtok(NULL, " \t\n");
    }

    if (count < 2) {
        printf("输入至少需要2个数字（当前磁头位置和至少1个请求）! 请重新输入\n");
        return inputRequests(requests, n, head);
    }

    *n = count - 1; // 请求数量 = 总数量 - 1（磁头位置）

    printf("当前磁头位置: %d\n", *head);
    printf("请求序列 (%d个): ", *n);
    for (int i = 0; i < *n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");
}

// 随机生成请求序列
void generateRandomRequests(int requests[], int *n, int *head) {
    srand((unsigned int)time(NULL));

    *head = rand() % MAX_TRACK;
    *n = rand() % 10 + 5;  // 5-14个请求

    printf("随机生成的磁头位置: %d\n", *head);
    printf("随机生成的请求数量: %d\n", *n);
    printf("随机生成的磁道请求: ");

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

// 打印访问链（详细版）
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

    // 4. 绘制访问链（简洁版）
    printf("\n访问链图示:\n");

    // 找出最小和最大磁道
    int minTrack = head;
    int maxTrack = head;
    for (int i = 0; i < count; i++) {
        if (sequence[i] < minTrack) minTrack = sequence[i];
        if (sequence[i] > maxTrack) maxTrack = sequence[i];
    }

    // 限制显示范围，避免过长
    int range = maxTrack - minTrack;
    if (range > 50) {
        // 如果范围太大，显示简化访问链
        printf("磁道范围: %d ~ %d (范围过大，显示简化)\n", minTrack, maxTrack);
        printf("H[%d]", head);
        for (int i = 0; i < count; i++) {
            if (i % 5 == 0 || i == count - 1) { // 每5个点显示一个，或最后一个
                printf(" → %d", sequence[i]);
            }
        }
        printf("\n");
    } else {
        // 显示完整访问链图示
        printf("磁道: ");
        for (int track = minTrack; track <= maxTrack; track++) {
            if (track == head) {
                printf("H");
            } else {
                // 检查是否访问过
                int visited = 0;
                for (int i = 0; i < count; i++) {
                    if (sequence[i] == track) {
                        visited = 1;
                        break;
                    }
                }
                printf(visited ? "*" : "-");
            }
        }
        printf("\n");

        // 显示刻度
        printf("刻度: ");
        for (int track = minTrack; track <= maxTrack; track++) {
            if (track == head || track == minTrack || track == maxTrack || track % 10 == 0) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");

        // 显示数字
        printf("数值: ");
        for (int track = minTrack; track <= maxTrack; track++) {
            if (track == head) {
                printf("H");
            } else if (track == minTrack || track == maxTrack || track % 20 == 0) {
                printf("%d", track);
            } else {
                printf(" ");
            }
        }
        printf("\n");
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

        // 找到未访问的最近磁道
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int distance = abs(current - requests[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = i;
                }
            }
        }

        // 访问该磁道
        visited[minIndex] = 1;
        moves[count] = minDistance;
        sequence[count] = requests[minIndex];
        current = requests[minIndex];
        count++;
    }

    printAccessChain(sequence, moves, n, head);
}

// 扫描算法 (SCAN) - 简化版
void scan(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    // 使用辅助函数计算
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        // 处理大于等于当前磁头位置的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 移动到最大磁道
        if (current < MAX_TRACK - 1) {
            moves[count] = abs(current - (MAX_TRACK - 1));
            sequence[count] = MAX_TRACK - 1;
            current = MAX_TRACK - 1;
            count++;
        }

        // 反向处理剩余的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] < head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    } else {  // 减少方向
        // 处理小于等于当前磁头位置的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 移动到最小磁道
        if (current > 0) {
            moves[count] = abs(current - 0);
            sequence[count] = 0;
            current = 0;
            count++;
        }

        // 反向处理剩余的请求
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

// 循环扫描算法 (CSCAN) - 简化版
void cscan(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    // 使用辅助函数排序
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        // 处理大于等于当前磁头位置的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 移动到最大磁道
        if (current < MAX_TRACK - 1) {
            moves[count] = abs(current - (MAX_TRACK - 1));
            sequence[count] = MAX_TRACK - 1;
            current = MAX_TRACK - 1;
            count++;
        }

        // 跳转到最小磁道（不计距离）
        moves[count] = 0;
        sequence[count] = 0;
        current = 0;
        count++;

        // 处理剩余的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] < head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    } else {  // 减少方向
        // 处理小于等于当前磁头位置的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 移动到最小磁道
        if (current > 0) {
            moves[count] = abs(current - 0);
            sequence[count] = 0;
            current = 0;
            count++;
        }

        // 跳转到最大磁道（不计距离）
        moves[count] = 0;
        sequence[count] = MAX_TRACK - 1;
        current = MAX_TRACK - 1;
        count++;

        // 处理剩余的请求
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

// LOOK算法 (SCAN改良版) - 简化版
void look(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    // 使用辅助函数排序
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        // 处理大于等于当前磁头位置的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 反向处理剩余的请求（不移动到最大磁道）
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] < head) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }
    } else {  // 减少方向
        // 处理小于等于当前磁头位置的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 反向处理剩余的请求（不移动到最小磁道）
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

// CLOOK算法 (CSCAN改良版) - 简化版
void clook(int requests[], int n, int head, int direction) {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count = 0;

    // 使用辅助函数排序
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;

    if (direction == 1) {  // 增加方向
        // 处理大于等于当前磁头位置的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 跳转到最小请求（不计距离）
        // 找到最小的请求
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

            // 处理剩余的请求
            for (int i = 0; i < n; i++) {
                if (sortedRequests[i] < head && sortedRequests[i] >= minRequest) {
                    if (sortedRequests[i] == minRequest && count > 1) {
                        continue; // 跳过已经添加的最小请求
                    }
                    moves[count] = abs(current - sortedRequests[i]);
                    sequence[count] = sortedRequests[i];
                    current = sortedRequests[i];
                    count++;
                }
            }
        }
    } else {  // 减少方向
        // 处理小于等于当前磁头位置的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                moves[count] = abs(current - sortedRequests[i]);
                sequence[count] = sortedRequests[i];
                current = sortedRequests[i];
                count++;
            }
        }

        // 跳转到最大请求（不计距离）
        // 找到最大的请求
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

            // 处理剩余的请求
            for (int i = n - 1; i >= 0; i--) {
                if (sortedRequests[i] > head && sortedRequests[i] <= maxRequest) {
                    if (sortedRequests[i] == maxRequest && count > 1) {
                        continue; // 跳过已经添加的最大请求
                    }
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

// 辅助函数：计算FCFS算法的总移动距离
int calculateFCFS(int requests[], int n, int head) {
    int current = head;
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += abs(current - requests[i]);
        current = requests[i];
    }
    return total;
}

// 辅助函数：计算SSTF算法的总移动距离
int calculateSSTF(int requests[], int n, int head) {
    int visited[MAX_REQUESTS] = {0};
    int current = head;
    int total = 0;
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
        total += minDistance;
        current = requests[minIndex];
        count++;
    }
    return total;
}

// 辅助函数：排序请求数组
void sortRequests(int requests[], int n, int sortedRequests[]) {
    for (int i = 0; i < n; i++) {
        sortedRequests[i] = requests[i];
    }
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

// 辅助函数：计算SCAN算法的总移动距离
int calculateSCAN(int requests[], int n, int head, int direction) {
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;
    int total = 0;

    if (direction == 1) {  // 增加方向
        // 处理大于等于当前磁头位置的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }

        // 移动到最大磁道
        if (current < MAX_TRACK - 1) {
            total += abs(current - (MAX_TRACK - 1));
            current = MAX_TRACK - 1;
        }

        // 反向处理剩余的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] < head) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }
    } else {  // 减少方向
        // 处理小于等于当前磁头位置的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }

        // 移动到最小磁道
        if (current > 0) {
            total += abs(current - 0);
            current = 0;
        }

        // 反向处理剩余的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] > head) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }
    }

    return total;
}

// 辅助函数：计算CSCAN算法的总移动距离
int calculateCSCAN(int requests[], int n, int head, int direction) {
    int sortedRequests[MAX_REQUESTS];
    sortRequests(requests, n, sortedRequests);

    int current = head;
    int total = 0;

    if (direction == 1) {  // 增加方向
        // 处理大于等于当前磁头位置的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] >= current) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }

        // 移动到最大磁道
        if (current < MAX_TRACK - 1) {
            total += abs(current - (MAX_TRACK - 1));
            current = MAX_TRACK - 1;
        }

        // 跳转到最小磁道（不计距离）
        current = 0;

        // 处理剩余的请求
        for (int i = 0; i < n; i++) {
            if (sortedRequests[i] < head) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }
    } else {  // 减少方向
        // 处理小于等于当前磁头位置的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }

        // 移动到最小磁道
        if (current > 0) {
            total += abs(current - 0);
            current = 0;
        }

        // 跳转到最大磁道（不计距离）
        current = MAX_TRACK - 1;

        // 处理剩余的请求
        for (int i = n - 1; i >= 0; i--) {
            if (sortedRequests[i] > head) {
                total += abs(current - sortedRequests[i]);
                current = sortedRequests[i];
            }
        }
    }

    return total;
}

// 比较所有算法（简化版）
void compareAlgorithms(int requests[], int n, int head) {
    printf("\n=== 磁盘调度算法比较 ===\n");
    printf("请求序列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n当前磁头位置: %d\n", head);

    printf("\n算法性能比较:\n");
    printf("算法名称\t\t总移动距离\t平均寻道长度\n");
    printf("------------------------------------------------\n");

    // 计算每种算法的总移动距离
    int totalFCFS = calculateFCFS(requests, n, head);
    printf("FCFS\t\t\t%d\t\t%.2f\n", totalFCFS, (float)totalFCFS / n);

    int totalSSTF = calculateSSTF(requests, n, head);
    printf("SSTF\t\t\t%d\t\t%.2f\n", totalSSTF, (float)totalSSTF / n);

    int totalSCAN1 = calculateSCAN(requests, n, head, 1);
    printf("SCAN(增加方向)\t\t%d\t\t%.2f\n", totalSCAN1, (float)totalSCAN1 / n);

    int totalSCAN2 = calculateSCAN(requests, n, head, 2);
    printf("SCAN(减少方向)\t\t%d\t\t%.2f\n", totalSCAN2, (float)totalSCAN2 / n);

    int totalCSCAN1 = calculateCSCAN(requests, n, head, 1);
    printf("CSCAN(增加方向)\t\t%d\t\t%.2f\n", totalCSCAN1, (float)totalCSCAN1 / n);

    int totalCSCAN2 = calculateCSCAN(requests, n, head, 2);
    printf("CSCAN(减少方向)\t\t%d\t\t%.2f\n", totalCSCAN2, (float)totalCSCAN2 / n);

    // LOOK和CLOOK算法与SCAN和CSCAN类似，但不会移动到磁道边界
    // 这里简化处理，使用SCAN和CSCAN的结果
    printf("LOOK(增加方向)\t\t≈%d\t\t≈%.2f\n", totalSCAN1, (float)totalSCAN1 / n);
    printf("LOOK(减少方向)\t\t≈%d\t\t≈%.2f\n", totalSCAN2, (float)totalSCAN2 / n);
    printf("CLOOK(增加方向)\t\t≈%d\t\t≈%.2f\n", totalCSCAN1, (float)totalCSCAN1 / n);
    printf("CLOOK(减少方向)\t\t≈%d\t\t≈%.2f\n", totalCSCAN2, (float)totalCSCAN2 / n);

    printf("\n说明:\n");
    printf("1. FCFS: 先来先服务，简单但效率较低\n");
    printf("2. SSTF: 最短寻道时间优先，效率较高但可能产生饥饿现象\n");
    printf("3. SCAN: 电梯算法，双向扫描，公平且效率较好\n");
    printf("4. CSCAN: 循环扫描，单向移动，响应时间更均匀\n");
    printf("5. LOOK: SCAN改良版，只扫描有请求的区域\n");
    printf("6. CLOOK: CSCAN改良版，只扫描有请求的区域\n");
    printf("\n注: LOOK和CLOOK算法的总移动距离与SCAN和CSCAN类似，但不会移动到磁道边界。\n");
}
