#include <stdio.h>

/**
 * 第3章：函数与模块化编程
 * 3.1 函数基础
 */

// 函数声明
void greet();

int main() {
    // 函数调用
    greet();

    return 0;
}

// 函数定义
void greet() {
    printf("欢迎使用C语言函数！\n");
    printf("这是一个简单的 greeting 函数。\n");
}
