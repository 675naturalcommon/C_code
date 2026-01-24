#include <stdio.h>

/**
 * 第1章：C语言基础入门
 * 1.3 数据类型
 */

int main() {
    // 整型数据
    int integerVar = 42;
    short shortVar = 100;
    long longVar = 1234567890;

    printf("整型数据：\n");
    printf("int: %d\n", integerVar);
    printf("short: %hd\n", shortVar);
    printf("long: %ld\n", longVar);

    // 浮点型数据
    float floatVar = 3.14f;
    double doubleVar = 2.71828;

    printf("\n浮点型数据：\n");
    printf("float: %.2f\n", floatVar);
    printf("double: %.5lf\n", doubleVar);

    // 字符型数据
    char charVar = 'A';
    char stringVar[] = "Hello C";

    printf("\n字符型数据：\n");
    printf("char: %c\n", charVar);
    printf("string: %s\n", stringVar);

    // 布尔型数据
    int trueValue = 1;
    int falseValue = 0;

    printf("\n布尔型数据：\n");
    printf("true: %d\n", trueValue);
    printf("false: %d\n", falseValue);

    return 0;
}
