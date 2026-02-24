#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// int main()
// {
//     printf("%s\n", __FILE__);
//     printf("%d\n", __LINE__);
//     printf("%s\n", __DATE__);
//     printf("%s\n", __TIME__);

//     return 0;
// }

// #define 定义常量
// #define PI 3.1415926
// #define STR "Hello, world!"
// #define reg register
// #define do_forever for(;;)
// //对于for循环,判断部分什么都不写的时候表示恒为真

// int main()
// {
//     register int i = 0; //建议将i中的值放到寄存器中
//     //寄存器的数量有限,编译器自动会决定将变量是否放在寄存器中
//     reg int n;
//     do_forever; //死循环

//     printf("%f\n", PI);
//     printf("%s\n", STR);

//     return 0;
// }

// #define CASE break;case
// int main()
// {
//     int i = 0;
//     switch (i)
//     {
//         case 0:
//         CASE 1:
//     }
//     return 0;
// }

// #define DEBUG_PRINT printf(" FILE:%s\n LINE:%d\n DATE:%s\n TIME:%s\n", \
//                            __FILE__,                                   \
//                            __LINE__,                                   \
//                            __DATE__,                                   \
//                            __TIME__)

// int main()
// {
//     DEBUG_PRINT;
//     return 0;
// }

// #define 后面不要跟分号,容易出问题

// #define 定义宏
// #define MAX(a, b) ((a) > (b) ? (a) : (b))

// #define SQUARE(x) ((x) * (x))

// int main()
// {
//     int a = 10, b = 20;
//     // int r = MAX(a, b);
//     // printf("%d\n", r);
//     int r = SQUARE(a + 1);
//     //如果#define SQUARE(x) x*x,在计算SQUARE(a+1)的时候,会替换成a+1*a+1,结果是21,会导致错误
//     printf("%d\n", r);
//     return 0;
// }

// #define DOUBLE(x) ((x) + (x))

// int main()
// {
//     int a = 10;
//     int r = 5 * DOUBLE(a);
//     printf("%d\n", r);
//     return 0;
// }

// 带有副作用的宏参数
// int main()
// {
//     int a = 10;
//     // int b = a + 1;
//     // b = 11,a = 10
//     // int b = ++a;
//     // b = 11,a = 11 b变成了11,a也变成了11,带有副作用
//     // int b = a++;
//     // b = 10,a = 11

//     return 0;
// }

// 写一个宏,求两个数的最大值
// #define MAX(a, b) ((a) > (b) ? (a) : (b))

// //函数的实现方式
// int max(int a, int b)
// {
//     return ((a) > (b) ? (a) : (b));
// }

// int main()
// {
//     int a = 10, b = 20;
//     int r = MAX(a++, b++);
//     // int r = ((a++) > (b++) ? (a++) : (b++));
//     printf("r = %d\n", r);
//     printf("a = %d\n", a);
//     printf("b = %d\n", b);
//     return 0;
// }

// #define MALLOC(n, type) (type *)malloc(n * sizeof(type))

// int main()
// {
//     // int *p = (int *)malloc(10 , sizeof(int));
//     int *p = MALLOC(10, int);
//     // int *p = (int *)malloc(10 * sizeof(int));

//     return 0;
// }

// #运算符

// #define PRINT(n, format) printf("The value of " #n " is " format "\n", n)
// int main()
// {
//     // printf("Hello, world!\n");
//     // printf("Hello," " world!\n");

//     int a = 10;
//     // printf("The value of a is %d\n", a);
//     PRINT(a, "%d");

//     float b = 3.14;
//     // printf("The value of b is %f\n", b);
//     PRINT(b, "%f");

//     return 0;
// }

// ##运算符
// ##可以把位于它两边的符号合成一个符号,它允许宏定义从分离的文本片段创建标识符.##被称为记号粘合
// 这样的连接必须产生一个合法标识符.负责其结果就是未定义的

// #define GENERIC_MAX(type)           \
//     type type##_max(type x, type y) \
//     {                               \
//         return (x > y) ? x : y;     \
//     }

// GENERIC_MAX(int);

// int main()
// {
//     int ret = int_max(10, 20);
//     printf("%d\n", ret);
//     return 0;
// }

// #undef取消定义符号,用于移除一个宏定义

// #define M 100
// int main()
// {
//     printf("%d\n", M);
// #undef M;              // 取消定义M
//     printf("%d\n", M); // 报错,未定义符号

//     return 0;
// }

// 常见的条件编译指令
// int main()
// {
// #if 0
//     printf("Hello, world!\n");
// #endif

//     return 0;
// }

// #define M 100

// int main()
// {
// #if M == 0
//     printf("M is zero\n");
// #elif M == 10
//     printf("M is ten\n");
// #elif M == 100
//     printf("M is one hundred\n");
// #else
//     printf("M is not zero, ten or one hundred\n");
// #endif

//     return 0;
// }

// #define M 100

// int main()
// {
// #if defined(M)
//     printf("M is defined\n");
// #endif

// #ifdef M
//     printf("M is defined\n");
// #endif

//     // #if 0
//     //     printf("Hello, world!\n");
//     // #endif

//     return 0;
// }

// #define M 100
// int main()
// {
//     // #if !defined(M)
//     //     printf("M is not defined\n");
//     // #else
//     //     printf("M is defined\n");
//     // #endif

//     // #ifndef M
//     //     printf("M is not defined\n");
//     // #else
//     //     printf("M is defined\n");
//     // #endif

//     return 0;
// }

// EOF
// define

// int main()
// {

//     return 0;
// }

// #pragma once的功能是防止头文件被多次包含,防止出现重复定义的问题.