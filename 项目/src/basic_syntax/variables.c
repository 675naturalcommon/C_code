#include <stdio.h>

/**
 * 第1章：C语言基础入门
 * 1.2 变量与数据类型
 */

int main() {
    // 变量声明与初始化
    int age = 20;
    float height = 175.5;
    char gender = 'M';
    char name[20] = "张三";

    // 输出变量值
    printf("姓名：%s\n", name);
    printf("年龄：%d岁\n", age);
    printf("身高：%.1f厘米\n", height);
    printf("性别：%c\n", gender);

    // 变量重新赋值
    age = 21;
    printf("一年后的年龄：%d岁\n", age);

    return 0;
}
