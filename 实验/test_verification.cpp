#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_REQUESTS 100

// 简单的FCFS算法验证
void testFCFS() {
    printf("=== 测试FCFS算法 ===\n");

    int requests[] = {55, 58, 60, 70, 18};
    int n = 5;
    int head = 50;

    printf("磁头起始位置: %d\n", head);
    printf("请求序列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // 手动计算FCFS
    int current = head;
    int totalMove = 0;
    printf("访问顺序: %d", head);
    for (int i = 0; i < n; i++) {
        int move = abs(current - requests[i]);
        printf(" -> %d", requests[i]);
        totalMove += move;
        current = requests[i];
    }
    printf("\n");

    printf("移动距离: ");
    current = head;
    for (int i = 0; i < n; i++) {
        printf("%d ", abs(current - requests[i]));
        current = requests[i];
    }
    printf("\n");

    printf("总移动距离: %d\n", totalMove);
    printf("平均寻道长度: %.2f\n", (float)totalMove / n);

    // 验证结果
    // 预期移动: |50-55|=5, |55-58|=3, |58-60|=2, |60-70|=10, |70-18|=52
    // 总移动: 5+3+2+10+52 = 72
    int expectedTotal = 5 + 3 + 2 + 10 + 52;
    if (totalMove == expectedTotal) {
        printf("✓ FCFS算法计算正确\n");
    } else {
        printf("✗ FCFS算法计算错误: 期望 %d, 实际 %d\n", expectedTotal, totalMove);
    }
}

// 简单的SSTF算法验证
void testSSTF() {
    printf("\n=== 测试SSTF算法 ===\n");

    int requests[] = {55, 58, 60, 70, 18};
    int n = 5;
    int head = 50;

    printf("磁头起始位置: %d\n", head);
    printf("请求序列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", requests[i]);
    }
    printf("\n");

    // 手动计算SSTF
    int visited[MAX_REQUESTS] = {0};
    int current = head;
    int totalMove = 0;
    int count = 0;

    printf("访问顺序: %d", head);

    while (count < n) {
        int minDistance = 1000;
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
        totalMove += minDistance;
        current = requests[minIndex];
        count++;

        printf(" -> %d", requests[minIndex]);
    }
    printf("\n");

    printf("总移动距离: %d\n", totalMove);
    printf("平均寻道长度: %.2f\n", (float)totalMove / n);

    // SSTF应该选择最近的磁道
    // 从50开始: 最近的55(5), 然后58(3), 60(2), 70(10), 最后18(52)
    // 总移动: 5+3+2+10+52 = 72 (与FCFS相同，因为顺序相同)
    int expectedTotal = 5 + 3 + 2 + 10 + 52;
    if (totalMove == expectedTotal) {
        printf("✓ SSTF算法计算正确\n");
    } else {
        printf("✗ SSTF算法计算错误: 期望 %d, 实际 %d\n", expectedTotal, totalMove);
    }
}

int main() {
    printf("=== 磁盘调度算法验证测试 ===\n\n");

    testFCFS();
    testSSTF();

    printf("\n=== 测试完成 ===\n");

    return 0;
}
