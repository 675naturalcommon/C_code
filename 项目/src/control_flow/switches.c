#include <stdio.h>

/**
 * 第2章：程序控制结构
 * 2.3 switch分支结构
 */

int main() {
    // 基础switch语句
    int choice = 2;
    printf("基础switch语句：\n");
    switch (choice) {
        case 1:
            printf("你选择了选项1\n");
            break;
        case 2:
            printf("你选择了选项2\n");
            break;
        case 3:
            printf("你选择了选项3\n");
            break;
        default:
            printf("无效的选择\n");
    }
    printf("\n");

    // switch语句应用 - 成绩等级
    int score = 85;
    printf("成绩等级判断：\n");
    switch (score / 10) {
        case 10:
        case 9:
            printf("优秀\n");
            break;
        case 8:
            printf("良好\n");
            break;
        case 7:
            printf("中等\n");
            break;
        case 6:
            printf("及格\n");
            break;
        default:
            printf("不及格\n");
    }
    printf("\n");

    // switch语句注意点
    printf("switch语句注意点：\n");
    int day = 3;
    switch (day) {
        case 1:
            printf("星期一\n");
            break;
        case 2:
            printf("星期二\n");
            break;
        case 3:
            printf("星期三\n");
            break;
        case 4:
            printf("星期四\n");
            break;
        case 5:
            printf("星期五\n");
            break;
        case 6:
            printf("星期六\n");
            break;
        case 7:
            printf("星期日\n");
            break;
        default:
            printf("无效的日期\n");
    }

    return 0;
}
