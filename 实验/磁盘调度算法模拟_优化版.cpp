#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_REQUESTS 100
#define MAX_TRACK 200

// 数据结构体
typedef struct {
    int requests[MAX_REQUESTS];
    int n;
    int head;
} DiskRequest;

typedef struct {
    int sequence[MAX_REQUESTS];
    int moves[MAX_REQUESTS];
    int count;
} AccessChain;

// 函数声明
void inputRequests(DiskRequest *req);
void generateRandomRequests(DiskRequest *req);
void printRequests(const DiskRequest *req);
void runDiskSchedulingAlgorithm(const DiskRequest *req);
void printAccessChain(const AccessChain *chain, int head);
void sortRequests(const int requests[], int n, int sortedRequests[]);
void copyRequests(const DiskRequest *src, DiskRequest *dst);

// 算法函数声明
void fcfs(const DiskRequest *req, AccessChain *chain);
void sstf(const DiskRequest *req, AccessChain *chain);
void scan(const DiskRequest *req, AccessChain *chain, int direction);
void cscan(const DiskRequest *req, AccessChain *chain, int direction);
void look(const DiskRequest *req, AccessChain *chain, int direction);
void clook(const DiskRequest *req, AccessChain *chain, int direction);
void compareAlgorithms(const DiskRequest *req);

int main() {
    DiskRequest req;
    int inputMethod;

    printf("=== 磁盘调度算法模拟程序 ===\n\n");

    // 输入请求序列
    printf("请选择输入方式:\n");
    printf("1. 手动输入\n");
    printf("2. 随机生成\n");
    printf("选择: ");
    scanf("%d", &inputMethod);

    if (inputMethod == 1) {
        inputRequests(&req);
    } else if (inputMethod == 2) {
        generateRandomRequests(&req);
    } else {
        printf("无效选择!\n");
        return -1;
    }

    // 显示输入的请求序列
    printf("\n=== 输入的请求序列 ===\n");
    printRequests(&req);

    // 运行磁盘调度算法
    printf("\n\n=== 开始运行磁盘调度算法 ===\n");
    runDiskSchedulingAlgorithm(&req);

    printf("\n=== 所有算法运行完成 ===\n");
    return 0;
}

// 复制请求数据
void copyRequests(const DiskRequest *src, DiskRequest *dst) {
    dst->n = src->n;
    dst->head = src->head;
    memcpy(dst->requests, src->requests, sizeof(int) * src->n);
}

// 手动输入请求序列
void inputRequests(DiskRequest *req) {
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
            return inputRequests(req);
        }

        if (count == 0) req->head = value;
        else req->requests[count - 1] = value;
        count++;
        token = strtok(NULL, " \t\n");
    }

    req->n = count - 1;
    printf("当前磁头位置: %d\n", req->head);
    printf("请求序列: ");
    for (int i = 0; i < req->n; i++) printf("%d ", req->requests[i]);
    printf("\n");
}

// 随机生成请求序列
void generateRandomRequests(DiskRequest *req) {
    srand((unsigned int)time(NULL));

    req->head = rand() % MAX_TRACK;
    req->n = rand() % 10 + 5;  // 5-14个请求

    printf("随机生成的磁头位置: %d\n", req->head);
    printf("请求数量: %d\n请求序列: ", req->n);

    for (int i = 0; i < req->n; i++) {
        req->requests[i] = rand() % MAX_TRACK;
        printf("%d ", req->requests[i]);
    }
    printf("\n");
}

// 打印请求序列
void printRequests(const DiskRequest *req) {
    printf("当前磁头位置: %d\n", req->head);
    printf("请求序列 (%d个): ", req->n);
    for (int i = 0; i < req->n; i++) {
        printf("%d ", req->requests[i]);
    }
    printf("\n");
}

// 运行所有磁盘调度算法
void runDiskSchedulingAlgorithm(const DiskRequest *req) {
    DiskRequest tempReq;
    AccessChain chain;

    // 1. 先来先服务算法 (FCFS)
    printf("\n=== 先来先服务算法 (FCFS) ===\n");
    copyRequests(req, &tempReq);
    fcfs(&tempReq, &chain);
    printAccessChain(&chain, req->head);

    // 2. 最短寻道时间优先算法 (SSTF)
    printf("\n=== 最短寻道时间优先算法 (SSTF) ===\n");
    copyRequests(req, &tempReq);
    sstf(&tempReq, &chain);
    printAccessChain(&chain, req->head);

    // 3. 扫描算法 (SCAN) - 向磁道号增加方向移动
    printf("\n=== 扫描算法 (SCAN) - 向磁道号增加方向移动 ===\n");
    copyRequests(req, &tempReq);
    scan(&tempReq, &chain, 1);
    printAccessChain(&chain, req->head);

    // 4. 扫描算法 (SCAN) - 向磁道号减少方向移动
    printf("\n=== 扫描算法 (SCAN) - 向磁道号减少方向移动 ===\n");
    copyRequests(req, &tempReq);
    scan(&tempReq, &chain, 2);
    printAccessChain(&chain, req->head);

    // 5. 循环扫描算法 (CSCAN) - 向磁道号增加方向移动
    printf("\n=== 循环扫描算法 (CSCAN) - 向磁道号增加方向移动 ===\n");
    copyRequests(req, &tempReq);
    cscan(&tempReq, &chain, 1);
    printAccessChain(&chain, req->head);

    // 6. 循环扫描算法 (CSCAN) - 向磁道号减少方向移动
    printf("\n=== 循环扫描算法 (CSCAN) - 向磁道号减少方向移动 ===\n");
    copyRequests(req, &tempReq);
    cscan(&tempReq, &chain, 2);
    printAccessChain(&chain, req->head);

    // 7. LOOK算法 (SCAN改良版) - 向磁道号增加方向移动
    printf("\n=== LOOK算法 (SCAN改良版) - 向磁道号增加方向移动 ===\n");
    copyRequests(req, &tempReq);
    look(&tempReq, &chain, 1);
    printAccessChain(&chain, req->head);

    // 8. LOOK算法 (SCAN改良版) - 向磁道号减少方向移动
    printf("\n=== LOOK算法 (SCAN改良版) - 向磁道号减少方向移动 ===\n");
    copyRequests(req, &tempReq);
    look(&tempReq, &chain, 2);
    printAccessChain(&chain, req->head);

    // 9. CLOOK算法 (CSCAN改良版) - 向磁道号增加方向移动
    printf("\n=== CLOOK算法 (CSCAN改良版) - 向磁道号增加方向移动 ===\n");
    copyRequests(req, &tempReq);
    clook(&tempReq, &chain, 1);
    printAccessChain(&chain, req->head);

    // 10. CLOOK算法 (CSCAN改良版) - 向磁道号减少方向移动
    printf("\n=== CLOOK算法 (CSCAN改良版) - 向磁道号减少方向移动 ===\n");
    copyRequests(req, &tempReq);
    clook(&tempReq, &chain, 2);
    printAccessChain(&chain, req->head);

    // 11. 算法比较
    printf("\n=== 算法性能比较 ===\n");
    compareAlgorithms(req);
}

// 打印访问链
void printAccessChain(const AccessChain *chain, int head) {
    int totalMove = 0;

    // 1. 显示初始位置
    printf("初始位置: %d\n", head);

    // 2. 显示访问每个磁道时，磁头移动的数量
    printf("\n访问过程:\n");
    printf("序号\t目标磁道\t移动距离\t方向\n");
    printf("------------------------------------------------\n");

    int current = head;
    for (int i = 0; i < chain->count; i++) {
        int target = chain->sequence[i];
        int move = chain->moves[i];
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
    printf("平均寻道长度: %.2f\n", (float)totalMove / chain->count);
}

// 排序请求序列
void sortRequests(const int requests[], int n, int sortedRequests[]) {
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
void fcfs(const DiskRequest *req, AccessChain *chain) {
    int current = req->head;
    chain->count = req->n;

    for (int i = 0; i < req->n; i++) {
        chain->moves[i] = abs(current - req->requests[i]);
        chain->sequence[i] = req->requests[i];
        current = req->requests[i];
    }
}

// 最短寻道时间优先算法
void sstf(const DiskRequest *req, AccessChain *chain) {
    int visited[MAX_REQUESTS] = {0};
    int current = req->head;
    chain->count = 0;

    while (chain->count < req->n) {
        int minDistance = MAX_TRACK * 2;
        int minIndex = -1;

        for (int i = 0; i < req->n; i++) {
            if (!visited[i]) {
                int distance = abs(current - req->requests[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = i;
                }
            }
        }

        visited[minIndex] = 1;
        chain->moves[chain->count] = minDistance;
        chain->sequence[chain->count] = req->requests[minIndex];
        current = req->requests[minIndex];
        chain->count++;
    }
}

// 扫描算法 (SCAN)
void scan(const DiskRequest *req, AccessChain *chain, int direction) {
    int sortedRequests[MAX_REQUESTS];
    sortRequests(req->requests, req->n, sortedRequests);

    int current = req->head;
    chain->count = 0;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] >= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        if (current < MAX_TRACK - 1) {
            chain->moves[chain->count] = abs(current - (MAX_TRACK - 1));
            chain->sequence[chain->count] = MAX_TRACK - 1;
            current = MAX_TRACK - 1;
            chain->count++;
        }

        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] < req->head) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }
    } else {  // 减少方向
        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        if (current > 0) {
            chain->moves[chain->count] = abs(current - 0);
            chain->sequence[chain->count] = 0;
            current = 0;
            chain->count++;
        }

        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] > req->head) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }
    }
}

// 循环扫描算法 (CSCAN)
void cscan(const DiskRequest *req, AccessChain *chain, int direction) {
    int sortedRequests[MAX_REQUESTS];
    sortRequests(req->requests, req->n, sortedRequests);

    int current = req->head;
    chain->count = 0;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] >= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        if (current < MAX_TRACK - 1) {
            chain->moves[chain->count] = abs(current - (MAX_TRACK - 1));
            chain->sequence[chain->count] = MAX_TRACK - 1;
            current = MAX_TRACK - 1;
            chain->count++;
        }

        chain->moves[chain->count] = 0;
        chain->sequence[chain->count] = 0;
        current = 0;
        chain->count++;

        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] < req->head) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }
    } else {  // 减少方向
        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        if (current > 0) {
            chain->moves[chain->count] = abs(current - 0);
            chain->sequence[chain->count] = 0;
            current = 0;
            chain->count++;
        }

        chain->moves[chain->count] = 0;
        chain->sequence[chain->count] = MAX_TRACK - 1;
        current = MAX_TRACK - 1;
        chain->count++;

        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] > req->head) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }
    }
}

// LOOK算法 (SCAN改良版)
void look(const DiskRequest *req, AccessChain *chain, int direction) {
    int sortedRequests[MAX_REQUESTS];
    sortRequests(req->requests, req->n, sortedRequests);

    int current = req->head;
    chain->count = 0;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] >= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] < req->head) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }
    } else {  // 减少方向
        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] > req->head) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }
    }
}

// CLOOK算法 (CSCAN改良版)
void clook(const DiskRequest *req, AccessChain *chain, int direction) {
    int sortedRequests[MAX_REQUESTS];
    sortRequests(req->requests, req->n, sortedRequests);

    int current = req->head;
    chain->count = 0;

    if (direction == 1) {  // 增加方向
        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] >= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        // 跳转到最小请求
        int minRequest = MAX_TRACK;
        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] < req->head && sortedRequests[i] < minRequest) {
                minRequest = sortedRequests[i];
            }
        }

        if (minRequest < MAX_TRACK) {
            chain->moves[chain->count] = 0;
            chain->sequence[chain->count] = minRequest;
            current = minRequest;
            chain->count++;

            for (int i = 0; i < req->n; i++) {
                if (sortedRequests[i] < req->head && sortedRequests[i] >= minRequest) {
                    if (sortedRequests[i] == minRequest && chain->count > 1) continue;
                    chain->moves[chain->count] = abs(current - sortedRequests[i]);
                    chain->sequence[chain->count] = sortedRequests[i];
                    current = sortedRequests[i];
                    chain->count++;
                }
            }
        }
    } else {  // 减少方向
        for (int i = req->n - 1; i >= 0; i--) {
            if (sortedRequests[i] <= current) {
                chain->moves[chain->count] = abs(current - sortedRequests[i]);
                chain->sequence[chain->count] = sortedRequests[i];
                current = sortedRequests[i];
                chain->count++;
            }
        }

        // 跳转到最大请求
        int maxRequest = -1;
        for (int i = 0; i < req->n; i++) {
            if (sortedRequests[i] > req->head && sortedRequests[i] > maxRequest) {
                maxRequest = sortedRequests[i];
            }
        }

        if (maxRequest > -1) {
            chain->moves[chain->count] = 0;
            chain->sequence[chain->count] = maxRequest;
            current = maxRequest;
            chain->count++;

            for (int i = req->n - 1; i >= 0; i--) {
                if (sortedRequests[i] > req->head && sortedRequests[i] <= maxRequest) {
                    if (sortedRequests[i] == maxRequest && chain->count > 1) continue;
                    chain->moves[chain->count] = abs(current - sortedRequests[i]);
                    chain->sequence[chain->count] = sortedRequests[i];
                    current = sortedRequests[i];
                    chain->count++;
                }
            }
        }
    }
}

// 比较所有算法
void compareAlgorithms(const DiskRequest *req) {
    printf("算法名称\t\t总移动距离\t平均寻道长度\n");
    printf("------------------------------------------------\n");

    // 计算FCFS
    int current = req->head;
    int totalFCFS = 0;
    for (int i = 0; i < req->n; i++) {
        totalFCFS += abs(current - req->requests[i]);
        current = req->requests[i];
    }
    printf("FCFS\t\t\t%d\t\t%.2f\n", totalFCFS, (float)totalFCFS / req->n);

    // 计算SSTF
    int visited[MAX_REQUESTS] = {0};
    current = req->head;
    int totalSSTF = 0;
    int count = 0;
    while (count < req->n) {
        int minDistance = MAX_TRACK * 2;
        int minIndex = -1;
        for (int i = 0; i < req->n; i++) {
            if (!visited[i]) {
                int distance = abs(current - req->requests[i]);
                if (distance < minDistance) {
                    minDistance = distance;
                    minIndex = i;
                }
            }
        }
        visited[minIndex] = 1;
        totalSSTF += minDistance;
        current = req->requests[minIndex];
        count++;
    }
    printf("SSTF\t\t\t%d\t\t%.2f\n", totalSSTF, (float)totalSSTF / req->n);

    // 计算SCAN增加方向
    int sortedRequests[MAX_REQUESTS];
    sortRequests(req->requests, req->n, sortedRequests);
    current = req->head;
    int totalSCAN1 = 0;
    for (int i = 0; i < req->n; i++) {
        if (sortedRequests[i] >= current) {
            totalSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    if (current < MAX_TRACK - 1) {
        totalSCAN1 += abs(current - (MAX_TRACK - 1));
        current = MAX_TRACK - 1;
    }
    for (int i = req->n - 1; i >= 0; i--) {
        if (sortedRequests[i] < req->head) {
            totalSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("SCAN(增加方向)\t\t%d\t\t%.2f\n", totalSCAN1, (float)totalSCAN1 / req->n);

    // 计算SCAN减少方向
    current = req->head;
    int totalSCAN2 = 0;
    for (int i = req->n - 1; i >= 0; i--) {
        if (sortedRequests[i] <= current) {
            totalSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    if (current > 0) {
        totalSCAN2 += abs(current - 0);
        current = 0;
    }
    for (int i = 0; i < req->n; i++) {
        if (sortedRequests[i] > req->head) {
            totalSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("SCAN(减少方向)\t\t%d\t\t%.2f\n", totalSCAN2, (float)totalSCAN2 / req->n);

    // 计算CSCAN增加方向
    current = req->head;
    int totalCSCAN1 = 0;
    for (int i = 0; i < req->n; i++) {
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
    for (int i = 0; i < req->n; i++) {
        if (sortedRequests[i] < req->head) {
            totalCSCAN1 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("CSCAN(增加方向)\t\t%d\t\t%.2f\n", totalCSCAN1, (float)totalCSCAN1 / req->n);

    // 计算CSCAN减少方向
    current = req->head;
    int totalCSCAN2 = 0;
    for (int i = req->n - 1; i >= 0; i--) {
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
    for (int i = req->n - 1; i >= 0; i--) {
        if (sortedRequests[i] > req->head) {
            totalCSCAN2 += abs(current - sortedRequests[i]);
            current = sortedRequests[i];
        }
    }
    printf("CSCAN(减少方向)\t\t%d\t\t%.2f\n", totalCSCAN2, (float)totalCSCAN2 / req->n);

    // LOOK和CLOOK近似值
    printf("LOOK(增加方向)\t\t≈%d\t\t≈%.2f\n", totalSCAN1, (float)totalSCAN1 / req->n);
    printf("LOOK(减少方向)\t\t≈%d\t\t≈%.2f\n", totalSCAN2, (float)totalSCAN2 / req->n);
    printf("CLOOK(增加方向)\t\t≈%d\t\t≈%.2f\n", totalCSCAN1, (float)totalCSCAN1 / req->n);
    printf("CLOOK(减少方向)\t\t≈%d\t\t≈%.2f\n", totalCSCAN2, (float)totalCSCAN2 / req->n);
}
