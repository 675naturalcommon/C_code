#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FRAMES 10
#define MAX_SEQUENCE 50

typedef enum {
    FIFO,
    OPT,
    LRU,
    LFU,
    CLOCK,
    IMPROVED_CLOCK
} AlgorithmType;

typedef struct {
    AlgorithmType type;
    char name[20];
    int pageFaults;
    int replacements;
    float pageFaultRate;
} AlgorithmResult;

void inputParameters(int *frameCount, int *seqLength, int sequence[]);
void generateRandomSequence(int frameCount, int *seqLength, int sequence[]);
void fifoAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result);
void optAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result);
void lruAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result);
void lfuAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result);
void clockAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result);
void improvedClockAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result);
void printComparison(AlgorithmResult results[], int count);

int main() {
    int frameCount, seqLength;
    int sequence[MAX_SEQUENCE];
    int inputMethod;

    printf("=== 页面置换算法模拟系统 ===\n\n");

    printf("请输入物理块数 (1-%d): ", MAX_FRAMES);
    scanf("%d", &frameCount);

    if (frameCount < 1 || frameCount > MAX_FRAMES) {
        printf("物理块数超出范围!\n");
        return -1;
    }

    printf("\n请选择访问序列输入方式:\n");
    printf("1. 手动输入\n");
    printf("2. 随机生成\n");
    printf("选择: ");
    scanf("%d", &inputMethod);

    if (inputMethod == 1) {
        printf("\n请输入访问序列长度 (1-%d): ", MAX_SEQUENCE);
        scanf("%d", &seqLength);

        if (seqLength < 1 || seqLength > MAX_SEQUENCE) {
            printf("序列长度超出范围!\n");
            return -1;
        }

        printf("请输入访问序列 (用空格分隔):\n");
        for (int i = 0; i < seqLength; i++) {
            scanf("%d", &sequence[i]);
        }
    } else if (inputMethod == 2) {
        srand((unsigned int)time(NULL));

        printf("\n请输入访问序列长度 (1-%d): ", MAX_SEQUENCE);
        scanf("%d", &seqLength);

        if (seqLength < 1 || seqLength > MAX_SEQUENCE) {
            printf("序列长度超出范围!\n");
            return -1;
        }

        int maxPage = frameCount * 2;
        if (maxPage < 5) maxPage = 5;

        printf("随机生成的访问序列 (页面号范围: 0-%d):\n", maxPage - 1);
        for (int i = 0; i < seqLength; i++) {
            sequence[i] = rand() % maxPage;
            printf("%d ", sequence[i]);
        }
        printf("\n");
    } else {
        printf("无效选择!\n");
        return -1;
    }

    printf("\n=== 初始信息 ===\n");
    printf("物理块数: %d\n", frameCount);
    printf("访问序列: ");
    for (int i = 0; i < seqLength; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n序列长度: %d\n", seqLength);

    AlgorithmResult results[6];
    char algorithmNames[6][20] = {"FIFO", "OPT", "LRU", "LFU", "Clock", "改进Clock"};

    printf("\n=== 开始运行页面置换算法 ===\n");

    // FIFO算法
    printf("\n--- 运行FIFO算法 ---\n");
    fifoAlgorithm(frameCount, seqLength, sequence, &results[0]);
    strcpy(results[0].name, "FIFO");
    results[0].type = FIFO;
    results[0].pageFaultRate = (float)results[0].pageFaults / seqLength * 100;

    // OPT算法
    printf("\n--- 运行OPT算法 ---\n");
    optAlgorithm(frameCount, seqLength, sequence, &results[1]);
    strcpy(results[1].name, "OPT");
    results[1].type = OPT;
    results[1].pageFaultRate = (float)results[1].pageFaults / seqLength * 100;

    // LRU算法
    printf("\n--- 运行LRU算法 ---\n");
    lruAlgorithm(frameCount, seqLength, sequence, &results[2]);
    strcpy(results[2].name, "LRU");
    results[2].type = LRU;
    results[2].pageFaultRate = (float)results[2].pageFaults / seqLength * 100;

    // LFU算法
    printf("\n--- 运行LFU算法 ---\n");
    lfuAlgorithm(frameCount, seqLength, sequence, &results[3]);
    strcpy(results[3].name, "LFU");
    results[3].type = LFU;
    results[3].pageFaultRate = (float)results[3].pageFaults / seqLength * 100;

    // Clock算法
    printf("\n--- 运行Clock算法 ---\n");
    clockAlgorithm(frameCount, seqLength, sequence, &results[4]);
    strcpy(results[4].name, "Clock");
    results[4].type = CLOCK;
    results[4].pageFaultRate = (float)results[4].pageFaults / seqLength * 100;

    // 改进Clock算法
    printf("\n--- 运行改进Clock算法 ---\n");
    improvedClockAlgorithm(frameCount, seqLength, sequence, &results[5]);
    strcpy(results[5].name, "改进Clock");
    results[5].type = IMPROVED_CLOCK;
    results[5].pageFaultRate = (float)results[5].pageFaults / seqLength * 100;

    printf("\n=== 算法比较 ===\n");
    printComparison(results, 6);

    return 0;
}

void fifoAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result) {
    int frames[MAX_FRAMES];
    int front = 0;

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    result->pageFaults = 0;
    result->replacements = 0;

    printf("步骤\t访问页面\t物理块状态\t\t缺页\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];
        int found = 0;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result->pageFaults++;

            int emptySlot = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
            } else {
                result->replacements++;
                frames[front] = page;
                front = (front + 1) % frameCount;
            }
        }

        printf("%2d\t%4d\t\t", i + 1, page);
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == -1)
                printf(" - ");
            else
                printf("%2d ", frames[j]);
        }
        printf("\t\t%s\n", found ? "否" : "是");
    }

    printf("FIFO算法完成: 缺页次数=%d, 置换次数=%d, 缺页率=%.2f%%\n",
           result->pageFaults, result->replacements, (float)result->pageFaults / seqLength * 100);
}

void optAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result) {
    int frames[MAX_FRAMES];

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
    }

    result->pageFaults = 0;
    result->replacements = 0;

    printf("步骤\t访问页面\t物理块状态\t\t缺页\t置换页面\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];
        int found = 0;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result->pageFaults++;

            int emptySlot = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf(" - ");
                    else
                        printf("%2d ", frames[j]);
                }
                printf("\t\t是\t-\n");
            } else {
                result->replacements++;

                int replaceIndex = -1;
                int farthest = -1;

                for (int j = 0; j < frameCount; j++) {
                    int nextUse = seqLength;

                    for (int k = i + 1; k < seqLength; k++) {
                        if (sequence[k] == frames[j]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }

                int replacedPage = frames[replaceIndex];
                frames[replaceIndex] = page;

                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf(" - ");
                    else
                        printf("%2d ", frames[j]);
                }
                printf("\t\t是\t%d\n", replacedPage);
            }
        } else {
            printf("%2d\t%4d\t\t", i + 1, page);
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1)
                    printf(" - ");
                else
                    printf("%2d ", frames[j]);
            }
            printf("\t\t否\t-\n");
        }
    }

    printf("OPT算法完成: 缺页次数=%d, 置换次数=%d, 缺页率=%.2f%%\n",
           result->pageFaults, result->replacements, (float)result->pageFaults / seqLength * 100);
}

void lruAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result) {
    int frames[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = -1;
    }

    result->pageFaults = 0;
    result->replacements = 0;

    printf("步骤\t访问页面\t物理块状态\t\t缺页\t置换页面\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];
        int found = 0;
        int foundIndex = -1;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                foundIndex = j;
                break;
            }
        }

        if (found) {
            lastUsed[foundIndex] = i;
            printf("%2d\t%4d\t\t", i + 1, page);
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1)
                    printf(" - ");
                else
                    printf("%2d ", frames[j]);
            }
            printf("\t\t否\t-\n");
        } else {
            result->pageFaults++;

            int emptySlot = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
                lastUsed[emptySlot] = i;
                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf(" - ");
                    else
                        printf("%2d ", frames[j]);
                }
                printf("\t\t是\t-\n");
            } else {
                result->replacements++;

                int lruIndex = 0;
                int minTime = lastUsed[0];

                for (int j = 1; j < frameCount; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        lruIndex = j;
                    }
                }

                int replacedPage = frames[lruIndex];
                frames[lruIndex] = page;
                lastUsed[lruIndex] = i;

                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf(" - ");
                    else
                        printf("%2d ", frames[j]);
                }
                printf("\t\t是\t%d\n", replacedPage);
            }
        }
    }

    printf("LRU算法完成: 缺页次数=%d, 置换次数=%d, 缺页率=%.2f%%\n",
           result->pageFaults, result->replacements, (float)result->pageFaults / seqLength * 100);
}

void lfuAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result) {
    int frames[MAX_FRAMES];
    int frequency[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        frequency[i] = 0;
        lastUsed[i] = -1;
    }

    result->pageFaults = 0;
    result->replacements = 0;

    printf("步骤\t访问页面\t物理块状态(频率)\t\t缺页\t置换页面\n");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];
        int found = 0;
        int foundIndex = -1;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                foundIndex = j;
                frequency[j]++;
                lastUsed[j] = i;
                break;
            }
        }

        if (!found) {
            result->pageFaults++;

            int emptySlot = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
                frequency[emptySlot] = 1;
                lastUsed[emptySlot] = i;
                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf("   -  ");
                    else
                        printf("%2d(%d) ", frames[j], frequency[j]);
                }
                printf("\t\t是\t-\n");
            } else {
                result->replacements++;

                int lfuIndex = 0;
                int minFreq = frequency[0];
                int minTime = lastUsed[0];

                for (int j = 1; j < frameCount; j++) {
                    if (frequency[j] < minFreq || (frequency[j] == minFreq && lastUsed[j] < minTime)) {
                        minFreq = frequency[j];
                        minTime = lastUsed[j];
                        lfuIndex = j;
                    }
                }

                int replacedPage = frames[lfuIndex];
                frames[lfuIndex] = page;
                frequency[lfuIndex] = 1;
                lastUsed[lfuIndex] = i;

                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf("   -  ");
                    else
                        printf("%2d(%d) ", frames[j], frequency[j]);
                }
                printf("\t\t是\t%d\n", replacedPage);
            }
        } else {
            printf("%2d\t%4d\t\t", i + 1, page);
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1)
                    printf("   -  ");
                else
                    printf("%2d(%d) ", frames[j], frequency[j]);
            }
            printf("\t\t否\t-\n");
        }
    }

    printf("LFU算法完成: 缺页次数=%d, 置换次数=%d, 缺页率=%.2f%%\n",
           result->pageFaults, result->replacements, (float)result->pageFaults / seqLength * 100);
}

void clockAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result) {
    int frames[MAX_FRAMES];
    int referenceBits[MAX_FRAMES]; // 访问位 (0/1)
    int clockHand = 0; // 时钟指针

    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        referenceBits[i] = 0;
    }

    result->pageFaults = 0;
    result->replacements = 0;

    printf("步骤\t访问页面\t物理块状态(访问位)\t\t缺页\t置换页面\n");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];
        int found = 0;
        int foundIndex = -1;

        // 检查页面是否已在物理块中
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                foundIndex = j;
                referenceBits[j] = 1; // 设置访问位为1
                break;
            }
        }

        if (!found) {
            result->pageFaults++;

            int emptySlot = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
                referenceBits[emptySlot] = 1; // 新页面访问位设为1
                clockHand = (emptySlot + 1) % frameCount; // 指针移动到下一个位置
                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf("   -  ");
                    else
                        printf("%2d(%d) ", frames[j], referenceBits[j]);
                }
                printf("\t\t是\t-\n");
            } else {
                result->replacements++;

                // Clock算法：寻找访问位为0的页面
                int replaced = 0;
                int startHand = clockHand;
                int replacedPage = -1;
                int replacedIndex = -1;

                // 第一轮扫描：寻找访问位为0的页面
                while (!replaced) {
                    if (referenceBits[clockHand] == 0) {
                        replaced = 1;
                        replacedIndex = clockHand;
                        replacedPage = frames[clockHand];
                        frames[clockHand] = page;
                        referenceBits[clockHand] = 1; // 新页面访问位设为1
                    } else {
                        // 访问位置位为0，继续扫描
                        referenceBits[clockHand] = 0;
                    }
                    clockHand = (clockHand + 1) % frameCount;
                }

                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf("   -  ");
                    else
                        printf("%2d(%d) ", frames[j], referenceBits[j]);
                }
                printf("\t\t是\t%d\n", replacedPage);
            }
        } else {
            printf("%2d\t%4d\t\t", i + 1, page);
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1)
                    printf("   -  ");
                else
                    printf("%2d(%d) ", frames[j], referenceBits[j]);
            }
            printf("\t\t否\t-\n");
        }
    }

    printf("Clock算法完成: 缺页次数=%d, 置换次数=%d, 缺页率=%.2f%%\n",
           result->pageFaults, result->replacements, (float)result->pageFaults / seqLength * 100);
}

void improvedClockAlgorithm(int frameCount, int seqLength, int sequence[], AlgorithmResult *result) {
    int frames[MAX_FRAMES];
    int referenceBits[MAX_FRAMES]; // 访问位 (0/1)
    int modifyBits[MAX_FRAMES];    // 修改位 (0/1) - 模拟修改位
    int clockHand = 0; // 时钟指针

    // 初始化
    for (int i = 0; i < frameCount; i++) {
        frames[i] = -1;
        referenceBits[i] = 0;
        modifyBits[i] = 0; // 初始修改位为0
    }

    result->pageFaults = 0;
    result->replacements = 0;

    printf("步骤\t访问页面\t物理块状态(访问位,修改位)\t缺页\t置换页面\n");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < seqLength; i++) {
        int page = sequence[i];
        int found = 0;
        int foundIndex = -1;

        // 检查页面是否已在物理块中
        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                found = 1;
                foundIndex = j;
                referenceBits[j] = 1; // 设置访问位为1
                // 50%的概率设置修改位为1（模拟页面被修改）
                if (rand() % 2 == 0) {
                    modifyBits[j] = 1;
                }
                break;
            }
        }

        if (!found) {
            result->pageFaults++;

            int emptySlot = -1;
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1) {
                    emptySlot = j;
                    break;
                }
            }

            if (emptySlot != -1) {
                frames[emptySlot] = page;
                referenceBits[emptySlot] = 1; // 新页面访问位设为1
                modifyBits[emptySlot] = 0;    // 初始修改位为0
                clockHand = (emptySlot + 1) % frameCount;
                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf("     -    ");
                    else
                        printf("%2d(%d,%d) ", frames[j], referenceBits[j], modifyBits[j]);
                }
                printf("\t是\t-\n");
            } else {
                result->replacements++;

                // 改进的Clock算法：四轮扫描
                int replaced = 0;
                int startHand = clockHand;
                int replacedPage = -1;
                int replacedIndex = -1;

                // 第一轮：寻找(0,0)类页面
                for (int round = 0; round < 4 && !replaced; round++) {
                    clockHand = startHand;
                    for (int j = 0; j < frameCount && !replaced; j++) {
                        int index = (clockHand + j) % frameCount;

                        if (round == 0) {
                            // 第一轮：寻找(0,0)类页面
                            if (referenceBits[index] == 0 && modifyBits[index] == 0) {
                                replaced = 1;
                                replacedIndex = index;
                                replacedPage = frames[index];
                            }
                        } else if (round == 1) {
                            // 第二轮：寻找(0,1)类页面
                            if (referenceBits[index] == 0 && modifyBits[index] == 1) {
                                replaced = 1;
                                replacedIndex = index;
                                replacedPage = frames[index];
                            }
                        } else if (round == 2) {
                            // 第三轮：访问位置位为0
                            referenceBits[index] = 0;
                        } else if (round == 3) {
                            // 第四轮：再次寻找(0,1)类页面
                            if (referenceBits[index] == 0 && modifyBits[index] == 1) {
                                replaced = 1;
                                replacedIndex = index;
                                replacedPage = frames[index];
                            }
                        }
                    }
                }

                // 确保找到了要替换的页面
                if (replacedIndex == -1) {
                    // 如果没有找到，使用第一个页面
                    replacedIndex = 0;
                    replacedPage = frames[0];
                }

                // 替换页面
                frames[replacedIndex] = page;
                referenceBits[replacedIndex] = 1; // 新页面访问位设为1
                modifyBits[replacedIndex] = 0;    // 初始修改位为0
                clockHand = (replacedIndex + 1) % frameCount;

                printf("%2d\t%4d\t\t", i + 1, page);
                for (int j = 0; j < frameCount; j++) {
                    if (frames[j] == -1)
                        printf("     -    ");
                    else
                        printf("%2d(%d,%d) ", frames[j], referenceBits[j], modifyBits[j]);
                }
                printf("\t是\t%d\n", replacedPage);
            }
        } else {
            printf("%2d\t%4d\t\t", i + 1, page);
            for (int j = 0; j < frameCount; j++) {
                if (frames[j] == -1)
                    printf("     -    ");
                else
                    printf("%2d(%d,%d) ", frames[j], referenceBits[j], modifyBits[j]);
            }
            printf("\t否\t-\n");
        }
    }

    printf("改进Clock算法完成: 缺页次数=%d, 置换次数=%d, 缺页率=%.2f%%\n",
           result->pageFaults, result->replacements, (float)result->pageFaults / seqLength * 100);
}

void printComparison(AlgorithmResult results[], int count) {
    printf("\n算法\t\t缺页次数\t置换次数\t缺页率\n");
    printf("------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10s\t%d\t\t%d\t\t%.2f%%\n",
               results[i].name,
               results[i].pageFaults,
               results[i].replacements,
               results[i].pageFaultRate);
    }

    // 找出最佳算法（缺页率最低）
    int bestIndices[10]; // 最多10个算法
    int bestCount = 0;
    float bestRate = 100.0; // 初始化为最大可能值

    for (int i = 0; i < count; i++) {
        if (results[i].pageFaultRate < bestRate) {
            bestRate = results[i].pageFaultRate;
            bestCount = 0;
            bestIndices[bestCount++] = i;
        } else if (results[i].pageFaultRate == bestRate) {
            bestIndices[bestCount++] = i;
        }
    }

    if (bestCount == 1) {
        printf("\n最佳算法: %s (缺页率: %.2f%%)\n", results[bestIndices[0]].name, bestRate);
    } else {
        printf("\n最佳算法 (并列): ");
        for (int i = 0; i < bestCount; i++) {
            printf("%s", results[bestIndices[i]].name);
            if (i < bestCount - 1) {
                printf(", ");
            }
        }
        printf(" (缺页率: %.2f%%)\n", bestRate);
    }
}
