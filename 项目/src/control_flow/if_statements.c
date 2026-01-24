#include <stdio.h>

/**
 * 第2章：程序控制结构
 * 2.1 条件判断语句
 */

int main() {
    // 单行if语句
    int score = 85;
    if (score >= 60) {
        printf("考试及格！\n");
    }

    // 多行if语句
    if (score >= 90) {
        printf("优秀！\n");
    } else {
        printf("还需要努力！\n");
    }

    // 多条件if语句
    if (score >= 90) {
        printf("等级：A\n");
    } else if (score >= 80) {
        printf("等级：B\n");
    } else if (score >= 70) {
        printf("等级：C\n");
    } else if (score >= 60) {
        printf("等级：D\n");
    } else {
        printf("等级：E\n");
    }

    // 嵌套if语句
    int age = 25;
    if (age >= 18) {
        printf("成年\n");
        if (age >= 60) {
            printf("老年人\n");
        } else {
            printf("青年人\n");
        }
    } else {
        printf("未成年人\n");
    }

    return 0;
}
