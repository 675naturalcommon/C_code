#include <stdio.h>

/**
 * 第3章：函数与模块化编程
 * 3.2 递归函数
 */

// 递归函数：计算阶乘
unsigned long factorial(unsigned int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int num = 5;
    printf("%d 的阶乘是 %lu\n", num, factorial(num));

    return 0;
}
