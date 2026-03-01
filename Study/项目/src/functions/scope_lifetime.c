#include <stdio.h>

/**
 * 第3章：函数与模块化编程
 * 3.3 变量作用域与生命周期
 */

// 全局变量
int globalVar = 100;

void displayGlobal() {
    printf("全局变量值: %d\n", globalVar);
}

int main() {
    // 局部变量
    int localVar = 200;
    printf("局部变量值: %d\n", localVar);

    // 块作用域
    {
        int blockVar = 300;
        printf("块作用域变量值: %d\n", blockVar);
    }

    // 函数作用域
    displayGlobal();

    return 0;
}
