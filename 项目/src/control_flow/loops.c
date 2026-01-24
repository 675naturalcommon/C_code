#include <stdio.h>

/**
 * 第2章：程序控制结构
 * 2.2 循环结构
 */

int main() {
    // while循环
    int count = 1;
    printf("while循环：\n");
    while (count <= 5) {
        printf("%d ", count);
        count++;
    }
    printf("\n\n");

    // do-while循环
    int num = 1;
    printf("do-while循环：\n");
    do {
        printf("%d ", num);
        num++;
    } while (num <= 5);
    printf("\n\n");

    // for循环
    printf("for循环：\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n\n");

    // 循环控制语句
    printf("循环控制语句：\n");
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            break;  // 跳出循环
        }
        printf("%d ", i);
    }
    printf("\n");

    printf("continue示例：\n");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 跳过偶数
        }
        printf("%d ", i);
    }
    printf("\n");

    return 0;
}
