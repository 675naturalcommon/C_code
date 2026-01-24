#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TRACK 200

// 测试SCAN算法（增加方向）
void testSCAN() {
    printf("=== 测试SCAN算法（增加方向） ===\n");

    int requests[] = {55, 58, 60, 70, 18};
    int n = 5;
    int head = 50;
    int direction = 1;  // 增加方向

    printf("磁头起始位置: %d\n", head);
    printf("请求序列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n方向: %s\n", direction == 1 ? "增加" : "减少");

    // 手动计算SCAN（增加方向）
    // 1. 对请求排序
    int sortedRequests[] = {18, 55, 58, 60, 70};
    int sortedN = 5;

    // 2. 从head=50开始，向增加方向移动
    int current = head;
    int totalMove = 0;

    printf("访问顺序: %d", current);

    // 先处理大于等于当前磁头位置的请求
    for (int i = 0; i < sortedN; i++) {
        if (sortedRequests[i] >= current) {
            int move = abs(current - sortedRequests[i]);
            totalMove += move;
            current = sortedRequests[i];
            printf(" -> %d", current);
        }
    }

    // 移动到最大磁道（199）
    if (current < MAX_TRACK - 1) {
        int move = abs(current - (MAX_TRACK - 1));
        totalMove += move;
        current = MAX_TRACK - 1;
        printf(" -> %d", current);
    }

    // 反向处理剩余的请求
    for (int i = sortedN - 1; i >= 0; i--) {
        if (sortedRequests[i] < head) {
            int move = abs(current - sortedRequests[i]);
            totalMove += move;
            current = sortedRequests[i];
            printf(" -> %d", current);
        }
    }

    printf("\n总移动距离: %d\n", totalMove);
    printf("平均寻道长度: %.2f\n", (float)totalMove / n);

    // 验证计算
    // 从50开始: 55(5), 58(3), 60(2), 70(10), 199(129), 18(181)
    // 总移动: 5+3+2+10+129+181 = 330
    int expectedTotal = 5 + 3 + 2 + 10 + 129 + 181;
    if (totalMove == expectedTotal) {
        printf("✓ SCAN算法（增加方向）计算正确\n");
    } else {
        printf("✗ SCAN算法（增加方向）计算错误: 期望 %d, 实际 %d\n", expectedTotal, totalMove);
    }
}

// 测试SCAN算法（减少方向）
void testSCAN_decrease() {
    printf("\n=== 测试SCAN算法（减少方向） ===\n");

    int requests[] = {55, 58, 60, 70, 18};
    int n = 5;
    int head = 50;
    int direction = 2;  // 减少方向

    printf("磁头起始位置: %d\n", head);
    printf("请求序列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n方向: %s\n", direction == 1 ? "增加" : "减少");

    // 手动计算SCAN（减少方向）
    // 1. 对请求排序
    int sortedRequests[] = {18, 55, 58, 60, 70};
    int sortedN = 5;

    // 2. 从head=50开始，向减少方向移动
    int current = head;
    int totalMove = 0;

    printf("访问顺序: %d", current);

    // 先处理小于等于当前磁头位置的请求
    for (int i = sortedN - 1; i >= 0; i--) {
        if (sortedRequests[i] <= current) {
            int move = abs(current - sortedRequests[i]);
            totalMove += move;
            current = sortedRequests[i];
            printf(" -> %d", current);
        }
    }

    // 移动到最小磁道（0）
    if (current > 0) {
        int move = abs(current - 0);
        totalMove += move;
        current = 0;
        printf(" -> %d", current);
    }

    // 反向处理剩余的请求
    for (int i = 0; i < sortedN; i++) {
        if (sortedRequests[i] > head) {
            int move = abs(current - sortedRequests[i]);
            totalMove += move;
            current = sortedRequests[i];
            printf(" -> %d", current);
        }
    }

    printf("\n总移动距离: %d\n", totalMove);
    printf("平均寻道长度: %.2f\n", (float)totalMove / n);

    // 验证计算
    // 从50开始: 18(32), 0(18), 55(55), 58(3), 60(2), 70(10)
    // 总移动: 32+18+55+3+2+10 = 120
    int expectedTotal = 32 + 18 + 55 + 3 + 2 + 10;
    if (totalMove == expectedTotal) {
        printf("✓ SCAN算法（减少方向）计算正确\n");
    } else {
        printf("✗ SCAN算法（减少方向）计算错误: 期望 %d, 实际 %d\n", expectedTotal, totalMove);
    }
}

int main() {
    printf("=== SCAN算法验证测试 ===\n\n");

    testSCAN();
    testSCAN_decrease();

    printf("\n=== 测试完成 ===\n");

    return 0;
}
