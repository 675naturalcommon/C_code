#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define PROCESS_NUM 5
#define RESOURCE_NUM 3

// 全局变量定义
int Available[RESOURCE_NUM];                    // 系统可用资源
int Max[PROCESS_NUM][RESOURCE_NUM];             // 进程最大需求
int Allocation[PROCESS_NUM][RESOURCE_NUM];      // 已分配资源
int Need[PROCESS_NUM][RESOURCE_NUM];            // 还需要资源
int Work[RESOURCE_NUM];                         // 工作向量
bool Finish[PROCESS_NUM];                       // 完成标记
int SafeSequence[PROCESS_NUM];                  // 安全序列

// 函数声明
void initializeSystem();
bool safetyAlgorithm();
bool resourceRequest(int process, int request[]);
void displayStatus();
void calculateNeed();
void inputSystemState();
void displaySafeSequence(int sequence[], int count);

int main() {
    int choice;
    int process;
    int request[RESOURCE_NUM];

    printf("========== 银行家算法模拟系统 ==========\n");

    // 初始化系统
    initializeSystem();

    while(1) {
        printf("\n========== 菜单 ==========\n");
        printf("1. 显示系统状态\n");
        printf("2. 安全性检查\n");
        printf("3. 资源请求\n");
        printf("4. 重新初始化系统\n");
        printf("0. 退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayStatus();
                break;

            case 2:
                if(safetyAlgorithm()) {
                    printf("\n✓ 系统处于安全状态\n");
                } else {
                    printf("\n✗ 系统处于不安全状态\n");
                }
                break;

            case 3:
                printf("请输入请求资源的进程号(0-%d): ", PROCESS_NUM-1);
                scanf("%d", &process);
                if(process < 0 || process >= PROCESS_NUM) {
                    printf("进程号无效！\n");
                    break;
                }
                printf("请输入请求的资源量(%d类资源): ", RESOURCE_NUM);
                for(int i = 0; i < RESOURCE_NUM; i++) {
                    scanf("%d", &request[i]);
                }

                if(resourceRequest(process, request)) {
                    printf("\n✓ 资源分配成功！\n");
                } else {
                    printf("\n✗ 资源分配失败！\n");
                }
                break;

            case 4:
                initializeSystem();
                printf("系统已重新初始化！\n");
                break;

            case 0:
                printf("感谢使用银行家算法模拟系统！\n");
                exit(0);

            default:
                printf("无效选择！\n");
        }
    }

    return 0;
}

/**
 * 初始化系统状态
 * 可以预设一些测试数据
 */
void initializeSystem() {
    // 预设测试数据 - 系统可用资源
    int presetAvailable[RESOURCE_NUM] = {3, 3, 2};

    // 预设测试数据 - 最大需求矩阵
    int presetMax[PROCESS_NUM][RESOURCE_NUM] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // 预设测试数据 - 分配矩阵
    int presetAllocation[PROCESS_NUM][RESOURCE_NUM] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // 复制预设数据到全局变量
    for(int i = 0; i < RESOURCE_NUM; i++) {
        Available[i] = presetAvailable[i];
    }

    for(int i = 0; i < PROCESS_NUM; i++) {
        for(int j = 0; j < RESOURCE_NUM; j++) {
            Max[i][j] = presetMax[i][j];
            Allocation[i][j] = presetAllocation[i][j];
        }
    }

    // 计算需求矩阵
    calculateNeed();

    printf("系统初始化完成！\n");
}

/**
 * 计算需求矩阵 Need = Max - Allocation
 */
void calculateNeed() {
    for(int i = 0; i < PROCESS_NUM; i++) {
        for(int j = 0; j < RESOURCE_NUM; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

/**
 * 安全性检查算法
 * @return true-安全 false-不安全
 */
bool safetyAlgorithm() {
    int count = 0;  // 安全序列计数
    bool found;

    // 初始化工作向量和完成标记
    for(int i = 0; i < RESOURCE_NUM; i++) {
        Work[i] = Available[i];
    }

    for(int i = 0; i < PROCESS_NUM; i++) {
        Finish[i] = false;
    }

    printf("\n--- 安全性检查过程 ---\n");

    // 寻找安全序列
    for(int k = 0; k < PROCESS_NUM; k++) {
        found = false;

        for(int i = 0; i < PROCESS_NUM; i++) {
            if(!Finish[i]) {
                // 检查 Need[i] <= Work
                bool canAllocate = true;
                for(int j = 0; j < RESOURCE_NUM; j++) {
                    if(Need[i][j] > Work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if(canAllocate) {
                    // 找到可分配的进程
                    printf("找到进程 P%d: Need <= Work, 可以分配\n", i);

                    // 模拟资源分配
                    for(int j = 0; j < RESOURCE_NUM; j++) {
                        Work[j] += Allocation[i][j];
                    }

                    Finish[i] = true;
                    SafeSequence[count++] = i;
                    found = true;

                    printf("   Work = Available + Allocation[P%d] = (", i);
                    for(int j = 0; j < RESOURCE_NUM; j++) {
                        printf("%d", Work[j]);
                        if(j < RESOURCE_NUM - 1) printf(", ");
                    }
                    printf(")\n");

                    break;
                }
            }
        }

        if(!found) {
            break;  // 没有找到可分配的进程
        }
    }

    // 检查是否所有进程都完成
    if(count == PROCESS_NUM) {
        printf("\n安全序列: ");
        displaySafeSequence(SafeSequence, count);
        return true;
    } else {
        printf("\n无法找到安全序列！\n");
        return false;
    }
}

/**
 * 资源请求算法
 * @param process 请求进程号
 * @param request 请求资源向量
 * @return true-分配成功 false-分配失败
 */
bool resourceRequest(int process, int request[]) {
    printf("\n--- 处理进程 P%d 的资源请求 ---\n", process);

    // 步骤1: 检查 Request <= Need
    for(int i = 0; i < RESOURCE_NUM; i++) {
        if(request[i] > Need[process][i]) {
            printf("错误: 请求资源超过最大需求！\n");
            return false;
        }
    }

    // 步骤2: 检查 Request <= Available
    for(int i = 0; i < RESOURCE_NUM; i++) {
        if(request[i] > Available[i]) {
            printf("错误: 请求资源超过可用资源！\n");
            return false;
        }
    }

    // 步骤3: 试探性分配
    printf("进行试探性分配...\n");

    // 保存原始状态以便回滚
    int oldAvailable[RESOURCE_NUM];
    int oldAllocation[PROCESS_NUM][RESOURCE_NUM];
    int oldNeed[PROCESS_NUM][RESOURCE_NUM];

    for(int i = 0; i < RESOURCE_NUM; i++) {
        oldAvailable[i] = Available[i];
        Available[i] -= request[i];

        for(int j = 0; j < PROCESS_NUM; j++) {
            oldAllocation[j][i] = Allocation[j][i];
            oldNeed[j][i] = Need[j][i];
        }
    }

    for(int i = 0; i < RESOURCE_NUM; i++) {
        Allocation[process][i] += request[i];
        Need[process][i] -= request[i];
    }

    printf("分配后系统状态:\n");
    displayStatus();

    // 步骤4: 执行安全性检查
    if(safetyAlgorithm()) {
        printf("分配后系统安全，确认分配！\n");
        return true;
    } else {
        printf("分配后系统不安全，回滚分配！\n");

        // 回滚到原始状态
        for(int i = 0; i < RESOURCE_NUM; i++) {
            Available[i] = oldAvailable[i];
            for(int j = 0; j < PROCESS_NUM; j++) {
                Allocation[j][i] = oldAllocation[j][i];
                Need[j][i] = oldNeed[j][i];
            }
        }
        return false;
    }
}

/**
 * 显示系统状态
 */
void displayStatus() {
    printf("\n========== 系统状态 ==========\n");

    // 显示可用资源
    printf("可用资源 Available: ");
    for(int i = 0; i < RESOURCE_NUM; i++) {
        printf("%d ", Available[i]);
    }
    printf("\n\n");

    // 显示表头
    printf("进程\tMax\t\tAllocation\tNeed\n");
    printf("    \t");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < RESOURCE_NUM; j++) {
            printf("%c ", 'A' + j);
        }
        printf("\t");
    }
    printf("\n");

    // 显示每个进程的信息
    for(int i = 0; i < PROCESS_NUM; i++) {
        printf("P%d\t", i);

        // 显示最大需求
        for(int j = 0; j < RESOURCE_NUM; j++) {
            printf("%d ", Max[i][j]);
        }
        printf("\t");

        // 显示已分配
        for(int j = 0; j < RESOURCE_NUM; j++) {
            printf("%d ", Allocation[i][j]);
        }
        printf("\t");

        // 显示需求
        for(int j = 0; j < RESOURCE_NUM; j++) {
            printf("%d ", Need[i][j]);
        }
        printf("\n");
    }
}

/**
 * 显示安全序列
 * @param sequence 安全序列数组
 * @param count 序列长度
 */
void displaySafeSequence(int sequence[], int count) {
    for(int i = 0; i < count; i++) {
        printf("P%d", sequence[i]);
        if(i < count - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

