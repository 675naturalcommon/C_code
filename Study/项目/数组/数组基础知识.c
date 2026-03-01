/*
 * C语言数组基础知识详解
 *
 * 数组是C语言中最重要的数据结构之一，用于存储相同类型的多个元素
 */

#include <stdio.h>

// 1. 数组的基本概念
void array_basic_concepts() {
    printf("=== 数组基本概念 ===\n");

    // 数组的定义：存储相同类型数据的集合
    // 语法：数据类型 数组名[数组长度];

    int numbers[5];  // 定义一个包含5个整数的数组

    // 数组的特点：
    // - 所有元素类型相同
    // - 元素在内存中连续存储
    // - 通过下标访问元素（从0开始）
    // - 数组名代表数组首元素的地址

    printf("数组是相同类型数据的集合\n");
    printf("数组元素在内存中连续存储\n");
    printf("数组下标从0开始\n\n");
}

// 2. 数组的声明和初始化
void array_declaration_initialization() {
    printf("=== 数组声明和初始化 ===\n");

    // 方式1：先声明后赋值
    int arr1[3];
    arr1[0] = 10;
    arr1[1] = 20;
    arr1[2] = 30;

    printf("arr1: %d, %d, %d\n", arr1[0], arr1[1], arr1[2]);

    // 方式2：声明时初始化（完全初始化）
    int arr2[3] = {1, 2, 3};
    printf("arr2: %d, %d, %d\n", arr2[0], arr2[1], arr2[2]);

    // 方式3：声明时初始化（部分初始化）
    int arr3[5] = {1, 2};  // 前两个元素为1,2，其余为0
    printf("arr3: %d, %d, %d, %d, %d\n",
           arr3[0], arr3[1], arr3[2], arr3[3], arr3[4]);

    // 方式4：自动确定数组长度
    int arr4[] = {1, 2, 3, 4, 5};  // 编译器自动计算长度为5
    printf("arr4长度自动确定为: 5\n");

    // 方式5：使用指定初始化器（C99特性）
    int arr5[10] = {[2] = 100, [5] = 200, [9] = 300};
    printf("arr5[2]=%d, arr5[5]=%d, arr5[9]=%d\n", arr5[2], arr5[5], arr5[9]);

    printf("\n");
}

// 3. 数组元素的访问和操作
void array_access_operations() {
    printf("=== 数组元素访问和操作 ===\n");

    int scores[5] = {85, 92, 78, 96, 88};

    // 访问单个元素
    printf("第一个成绩: %d\n", scores[0]);
    printf("最后一个成绩: %d\n", scores[4]);

    // 修改元素值
    scores[2] = 85;  // 将第三个成绩改为85
    printf("修改后的第三个成绩: %d\n", scores[2]);

    // 遍历数组（使用for循环）
    printf("所有成绩: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", scores[i]);
    }
    printf("\n");

    // 计算数组元素个数
    int size = sizeof(scores) / sizeof(scores[0]);
    printf("数组元素个数: %d\n", size);

    printf("\n");
}

// 4. 数组的内存布局
void array_memory_layout() {
    printf("=== 数组内存布局 ===\n");

    int arr[3] = {10, 20, 30};

    printf("数组元素地址:\n");
    for(int i = 0; i < 3; i++) {
        printf("arr[%d] 地址: %p, 值: %d\n",
               i, (void*)&arr[i], arr[i]);
    }

    // 验证数组元素在内存中连续存储
    printf("地址差值: %ld 字节\n",
           (long)&arr[1] - (long)&arr[0]);

    printf("\n");
}

// 5. 数组的边界检查
void array_boundary_check() {
    printf("=== 数组边界检查 ===\n");

    int arr[3] = {1, 2, 3};

    // C语言不进行数组边界检查
    // 访问越界元素可能导致未定义行为
    printf("arr[2] = %d (有效)\n", arr[2]);
    printf("arr[3] = %d (越界访问，结果不可预测)\n", arr[3]);

    // 重要：程序员必须自己确保不越界访问
    printf("程序员必须负责数组边界检查！\n\n");
}

// 6. 字符数组（字符串）
void character_arrays() {
    printf("=== 字符数组和字符串 ===\n");

    // 字符数组的声明和初始化
    char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char str2[] = "World";  // 自动添加'\0'
    char str3[10] = "Hello";

    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);

    // 字符串操作
    char name[20] = "Alice";
    printf("原始名字: %s\n", name);

    // 修改字符串内容
    name[0] = 'B';
    name[1] = 'o';
    name[2] = 'b';
    name[3] = '\0';  // 重要：手动添加字符串结束符
    printf("修改后名字: %s\n", name);

    printf("\n");
}

// 7. 数组作为函数参数
void print_array(int arr[], int size) {
    printf("数组内容: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void modify_array(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        arr[i] *= 2;  // 修改原数组
    }
}

void array_as_function_parameter() {
    printf("=== 数组作为函数参数 ===\n");

    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("修改前: ");
    print_array(numbers, size);

    modify_array(numbers, size);

    printf("修改后: ");
    print_array(numbers, size);

    printf("注意：数组作为参数传递的是地址，函数内修改会影响原数组\n\n");
}

// 8. 多维数组基础
void multi_dimensional_arrays() {
    printf("=== 多维数组基础 ===\n");

    // 二维数组声明和初始化
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    printf("二维数组内容:\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
        }
    }

    // 三维数组示例
    int cube[2][2][2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };

    printf("\n");
}

int main() {
    printf("C语言数组基础知识学习\n");
    printf("====================\n\n");

    array_basic_concepts();
    array_declaration_initialization();
    array_access_operations();
    array_memory_layout();
    array_boundary_check();
    character_arrays();
    array_as_function_parameter();
    multi_dimensional_arrays();

    printf("数组学习要点总结:\n");
    printf("1. 数组是相同类型元素的集合\n");
    printf("2. 元素在内存中连续存储\n");
    printf("3. 下标从0开始，注意边界检查\n");
    printf("4. 数组名代表首元素地址\n");
    printf("5. 字符数组用于存储字符串\n");
    printf("6. 数组作为函数参数传递的是地址\n");

    return 0;
}
