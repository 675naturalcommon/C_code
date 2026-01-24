/*
 * C语言数组高级应用详解
 *
 * 本文件包含数组的高级用法和实际应用场景
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. 动态数组（使用malloc和realloc）
void dynamic_arrays() {
    printf("=== 动态数组 ===\n");

    int size;
    printf("请输入数组大小: ");
    scanf("%d", &size);

    // 动态分配内存
    int *dynamic_arr = (int*)malloc(size * sizeof(int));

    if(dynamic_arr == NULL) {
        printf("内存分配失败！\n");
        return;
    }

    // 初始化动态数组
    for(int i = 0; i < size; i++) {
        dynamic_arr[i] = i * 10;
    }

    printf("动态数组内容: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");

    // 重新分配内存（扩大数组）
    int new_size = size + 3;
    int *temp = (int*)realloc(dynamic_arr, new_size * sizeof(int));

    if(temp != NULL) {
        dynamic_arr = temp;
        // 初始化新增的元素
        for(int i = size; i < new_size; i++) {
            dynamic_arr[i] = i * 10;
        }

        printf("扩展后的数组: ");
        for(int i = 0; i < new_size; i++) {
            printf("%d ", dynamic_arr[i]);
        }
        printf("\n");
    }

    // 释放内存
    free(dynamic_arr);
    printf("动态数组内存已释放\n\n");
}

// 2. 数组排序算法
void bubble_sort(int arr[], int size) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                // 交换元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void array_sorting() {
    printf("=== 数组排序 ===\n");

    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("排序前: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    bubble_sort(numbers, size);

    printf("排序后: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
}

// 3. 数组查找算法
int linear_search(int arr[], int size, int target) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == target) {
            return i;  // 找到目标，返回索引
        }
    }
    return -1;  // 未找到
}

int binary_search(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;

        if(arr[mid] == target) {
            return mid;
        } else if(arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void array_searching() {
    printf("=== 数组查找 ===\n");

    int numbers[] = {11, 12, 22, 25, 34, 64, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int target;

    printf("数组内容: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // 线性查找
    printf("请输入要查找的数字: ");
    scanf("%d", &target);

    int linear_result = linear_search(numbers, size, target);
    if(linear_result != -1) {
        printf("线性查找: 数字 %d 在索引 %d 处\n", target, linear_result);
    } else {
        printf("线性查找: 数字 %d 未找到\n", target);
    }

    // 二分查找（要求数组有序）
    int binary_result = binary_search(numbers, size, target);
    if(binary_result != -1) {
        printf("二分查找: 数字 %d 在索引 %d 处\n", target, binary_result);
    } else {
        printf("二分查找: 数字 %d 未找到\n", target);
    }

    printf("\n");
}

// 4. 数组与字符串操作
void string_operations() {
    printf("=== 字符串操作 ===\n");

    char str1[50] = "Hello";
    char str2[] = " World";
    char str3[50];
    char str4[] = "Programming";

    // 字符串连接
    strcat(str1, str2);
    printf("连接后: %s\n", str1);

    // 字符串复制
    strcpy(str3, str1);
    printf("复制后: %s\n", str3);

    // 字符串比较
    int cmp_result = strcmp(str1, "Hello World");
    if(cmp_result == 0) {
        printf("字符串相等\n");
    } else {
        printf("字符串不相等\n");
    }

    // 字符串长度
    printf("str1长度: %zu\n", strlen(str1));

    // 字符串查找
    char *found = strstr(str4, "gram");
    if(found != NULL) {
        printf("在str4中找到子串: %s\n", found);
    }

    printf("\n");
}

// 5. 多维数组高级应用
void advanced_multi_dimensional_arrays() {
    printf("=== 多维数组高级应用 ===\n");

    // 二维数组作为矩阵
    int matrix1[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int matrix2[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int result[2][2] = {0};

    // 矩阵乘法
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 3; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    printf("矩阵乘法结果:\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // 三维数组应用：RGB图像处理
    int image[2][2][3] = {
        {{255, 0, 0}, {0, 255, 0}},    // 红色和绿色像素
        {{0, 0, 255}, {255, 255, 0}}   // 蓝色和黄色像素
    };

    printf("\nRGB图像数据:\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("像素(%d,%d): R=%d, G=%d, B=%d\n",
                   i, j, image[i][j][0], image[i][j][1], image[i][j][2]);
        }
    }

    printf("\n");
}

// 6. 数组与结构体结合
typedef struct {
    char name[20];
    int age;
    float score;
} Student;

void arrays_with_structures() {
    printf("=== 数组与结构体 ===\n");

    Student students[3] = {
        {"Alice", 20, 85.5},
        {"Bob", 21, 92.0},
        {"Charlie", 19, 78.5}
    };

    printf("学生信息:\n");
    for(int i = 0; i < 3; i++) {
        printf("学生%d: 姓名=%s, 年龄=%d, 成绩=%.1f\n",
               i+1, students[i].name, students[i].age, students[i].score);
    }

    // 计算平均成绩
    float total_score = 0;
    for(int i = 0; i < 3; i++) {
        total_score += students[i].score;
    }
    printf("平均成绩: %.2f\n\n", total_score / 3);
}

// 7. 数组作为栈和队列
#define MAX_SIZE 5

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
}

int is_stack_empty(Stack *s) {
    return s->top == -1;
}

int is_stack_full(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, int value) {
    if(!is_stack_full(s)) {
        s->data[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if(!is_stack_empty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

void stack_implementation() {
    printf("=== 数组实现栈 ===\n");

    Stack s;
    init_stack(&s);

    // 入栈操作
    printf("入栈操作:\n");
    for(int i = 1; i <= 5; i++) {
        push(&s, i * 10);
        printf("入栈: %d\n", i * 10);
    }

    // 尝试入栈（栈满）
    push(&s, 60);
    printf("尝试入栈60（栈满）\n");

    // 出栈操作
    printf("出栈操作:\n");
    while(!is_stack_empty(&s)) {
        printf("出栈: %d\n", pop(&s));
    }

    printf("\n");
}

// 8. 数组性能优化技巧
void array_performance_tips() {
    printf("=== 数组性能优化技巧 ===\n");

    // 技巧1：局部性原理 - 顺序访问
    int arr[1000];

    // 好的方式：顺序访问（缓存友好）
    printf("顺序访问（缓存友好）\n");
    for(int i = 0; i < 1000; i++) {
        arr[i] = i;
    }

    // 技巧2：避免不必要的边界检查
    // 在性能关键代码中，可以手动进行边界检查

    // 技巧3：使用寄存器变量
    register int sum = 0;
    for(int i = 0; i < 1000; i++) {
        sum += arr[i];
    }
    printf("数组总和: %d\n", sum);

    printf("性能优化要点:\n");
    printf("1. 利用局部性原理，顺序访问数组\n");
    printf("2. 在循环外计算数组长度\n");
    printf("3. 使用寄存器变量存储频繁访问的数据\n");
    printf("4. 避免在循环中进行函数调用\n\n");
}

int main() {
    printf("C语言数组高级应用学习\n");
    printf("=====================\n\n");

    dynamic_arrays();
    array_sorting();
    array_searching();
    string_operations();
    advanced_multi_dimensional_arrays();
    arrays_with_structures();
    stack_implementation();
    array_performance_tips();

    printf("数组高级应用总结:\n");
    printf("1. 动态数组提供灵活的内存管理\n");
    printf("2. 排序和查找是数组的常见操作\n");
    printf("3. 字符串是特殊的字符数组\n");
    printf("4. 多维数组用于表示矩阵和图像\n");
    printf("5. 数组可以与其他数据结构结合\n");
    printf("6. 理解性能优化技巧很重要\n");

    return 0;
}
