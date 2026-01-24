#include <stdio.h>

/**
 * 第1章：C语言基础入门
 * 1.4 算术运算符
 */

int main() {
    // 基本算术运算
    int a = 10, b = 5;

    printf("基本算术运算：\n");
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);
    printf("%d / %d = %d\n", a, b, a / b);  // 整数除法
    printf("%d %% %d = %d\n", a, b, a % b);  // 取余运算

    // 浮点数除法
    float x = 10.0, y = 3.0;
    printf("\n浮点数除法：\n");
    printf("%.1f / %.1f = %.2f\n", x, y, x / y);

    // 混合类型运算
    int m = 7;
    float n = 2.5;
    printf("\n混合类型运算：\n");
    printf("%d + %.1f = %.2f\n", m, n, m + n);

    // 自增自减运算符
    int p = 5;
    printf("\n自增自减运算符：\n");
    printf("p = %d\n", p);
    printf("p++ = %d\n", p++);
    printf("++p = %d\n", ++p);
    printf("p-- = %d\n", p--);
    printf("--p = %d\n", --p);

    return 0;
}
