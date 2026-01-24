/*
 * C语言指针高级应用详解
 *
 * 本文件包含指针的高级用法和实际应用场景
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 动态内存管理
void dynamic_memory_management() {
    printf("=== 动态内存管理 ===\n");

    // malloc - 分配内存但不初始化
    int *arr1 = (int*)malloc(5 * sizeof(int));
    if(arr1 == NULL) {
        printf("malloc分配失败\n");
        return;
    }
    printf("malloc分配的内存（内容未初始化）:\n");
    for(int i = 0; i < 5; i++) {
        printf("%d ", arr1[i]);  // 随机值
    }
    printf("\n");

    // calloc - 分配内存并初始化为0
    int *arr2 = (int*)calloc(5, sizeof(int));
    if(arr2 == NULL) {
        printf("calloc分配失败\n");
        free(arr1);
        return;
    }
    printf("calloc分配的内存（初始化为0）:\n");
    for(int i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);  // 全为0
    }
    printf("\n");

    // realloc - 重新分配内存
    int *arr3 = (int*)realloc(arr1, 10 * sizeof(int));
    if(arr3 != NULL) {
        arr1 = arr3;
        printf("realloc扩展后的内存:\n");
        for(int i = 0; i < 10; i++) {
            printf("%d ", arr1[i]);
        }
        printf("\n");
    }

    // 释放内存
    free(arr1);
    free(arr2);
    printf("内存已释放\n\n");
}

// 2. 函数指针
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if(b != 0) return a / b;
    return 0;
}

void function_pointers() {
    printf("=== 函数指针 ===\n");

    // 函数指针声明
    int (*operation)(int, int);

    int x = 10, y = 5;

    // 指向add函数
    operation = add;
    printf("%d + %d = %d\n", x, y, operation(x, y));

    // 指向subtract函数
    operation = subtract;
    printf("%d - %d = %d\n", x, y, operation(x, y));

    // 指向multiply函数
    operation = multiply;
    printf("%d * %d = %d\n", x, y, operation(x, y));

    // 指向divide函数
    operation = divide;
    printf("%d / %d = %d\n", x, y, operation(x, y));

    // 函数指针数组
    int (*operations[])(int, int) = {add, subtract, multiply, divide};
    char *op_names[] = {"加法", "减法", "乘法", "除法"};

    printf("\n使用函数指针数组:\n");
    for(int i = 0; i < 4; i++) {
        printf("%s: %d\n", op_names[i], operations[i](x, y));
    }

    printf("\n");
}

// 3. 回调函数
typedef int (*CompareFunc)(int, int);

int compare_asc(int a, int b) {
    return a - b;
}

int compare_desc(int a, int b) {
    return b - a;
}

void bubble_sort_with_callback(int arr[], int size, CompareFunc compare) {
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(compare(arr[j], arr[j + 1]) > 0) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void callback_functions() {
    printf("=== 回调函数 ===\n");

    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    printf("原始数组: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // 升序排序
    bubble_sort_with_callback(numbers, size, compare_asc);
    printf("升序排序: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // 降序排序
    bubble_sort_with_callback(numbers, size, compare_desc);
    printf("降序排序: ");
    for(int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
}

// 4. 指针与结构体
typedef struct {
    char name[50];
    int age;
    float salary;
} Employee;

void pointers_and_structures() {
    printf("=== 指针与结构体 ===\n");

    Employee emp1 = {"张三", 30, 5000.0};
    Employee *emp_ptr = &emp1;

    // 使用指针访问结构体成员
    printf("员工信息:\n");
    printf("姓名: %s\n", emp_ptr->name);      // 使用->运算符
    printf("年龄: %d\n", emp_ptr->age);
    printf("工资: %.2f\n", emp_ptr->salary);

    // 修改结构体成员
    emp_ptr->age = 31;
    emp_ptr->salary = 5500.0;
    printf("\n修改后信息:\n");
    printf("年龄: %d\n", emp_ptr->age);
    printf("工资: %.2f\n", emp_ptr->salary);

    // 动态分配结构体
    Employee *dynamic_emp = (Employee*)malloc(sizeof(Employee));
    if(dynamic_emp != NULL) {
        strcpy(dynamic_emp->name, "李四");
        dynamic_emp->age = 25;
        dynamic_emp->salary = 4000.0;

        printf("\n动态分配的员工:\n");
        printf("姓名: %s\n", dynamic_emp->name);
        printf("年龄: %d\n", dynamic_emp->age);
        printf("工资: %.2f\n", dynamic_emp->salary);

        free(dynamic_emp);
    }

    printf("\n");
}

// 5. 动态二维数组
void dynamic_2d_arrays() {
    printf("=== 动态二维数组 ===\n");

    int rows = 3, cols = 4;

    // 分配行指针数组
    int **matrix = (int**)malloc(rows * sizeof(int*));
    if(matrix == NULL) {
        printf("内存分配失败\n");
        return;
    }

    // 为每一行分配内存
    for(int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if(matrix[i] == NULL) {
            printf("内存分配失败\n");
            // 释放已分配的内存
            for(int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return;
        }
    }

    // 初始化矩阵
    int count = 1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = count++;
        }
    }

    // 打印矩阵
    printf("动态二维数组:\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    for(int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    printf("\n");
}

// 6. 指针与链表
typedef struct Node {
    int data;
    struct Node *next;
} Node;

void pointers_and_linked_lists() {
    printf("=== 指针与链表 ===\n");

    // 创建链表: 1 -> 2 -> 3 -> NULL
    Node *head = NULL;
    Node *second = NULL;
    Node *third = NULL;

    // 分配节点内存
    head = (Node*)malloc(sizeof(Node));
    second = (Node*)malloc(sizeof(Node));
    third = (Node*)malloc(sizeof(Node));

    if(head == NULL || second == NULL || third == NULL) {
        printf("内存分配失败\n");
        return;
    }

    // 初始化节点
    head->data = 1;
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    // 遍历链表
    printf("链表内容: ");
    Node *current = head;
    while(current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");

    // 在链表头部插入新节点
    Node *new_node = (Node*)malloc(sizeof(Node));
    if(new_node != NULL) {
        new_node->data = 0;
        new_node->next = head;
        head = new_node;

        printf("插入后链表: ");
        current = head;
        while(current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }

    // 释放链表内存
    current = head;
    while(current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    printf("\n");
}

// 7. 指针与文件操作
void pointers_and_file_operations() {
    printf("=== 指针与文件操作 ===\n");

    FILE *file = fopen("test.txt", "w");
    if(file == NULL) {
        printf("无法创建文件\n");
        return;
    }

    // 写入数据
    char *text = "Hello, Pointer World!\nThis is a test file.";
    fputs(text, file);
    fclose(file);

    // 读取数据
    file = fopen("test.txt", "r");
    if(file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // 动态分配内存读取文件
    char *buffer = (char*)malloc(file_size + 1);
    if(buffer == NULL) {
        printf("内存分配失败\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';  // 添加字符串结束符

    printf("文件内容:\n%s\n", buffer);

    // 清理
    free(buffer);
    fclose(file);

    printf("\n");
}

// 8. 复杂指针声明解析
void complex_pointer_declarations() {
    printf("=== 复杂指针声明解析 ===\n");

    int num = 42;

    // 1. 指向整数的指针
    int *ptr1 = &num;
    printf("int *ptr1 - 指向整数的指针\n");

    // 2. 指向指针的指针（整数）
    int **ptr2 = &ptr1;
    printf("int **ptr2 - 指向指针的指针\n");

    // 3. 指向数组的指针（5个整数）
    int arr[5] = {1, 2, 3, 4, 5};
    int (*ptr3)[5] = &arr;
    printf("int (*ptr3)[5] - 指向数组的指针\n");

    // 4. 函数指针数组
    int (*func_ptr_arr[2])(int, int) = {add, subtract};
    printf("int (*func_ptr_arr[2])(int, int) - 函数指针数组\n");

    // 5. 指向函数的指针，该函数返回指向整数的指针
    int* (*func_ptr)(size_t) = malloc;
    printf("int* (*func_ptr)(size_t) - 指向函数的指针，函数返回整数指针\n");

    printf("\n复杂指针声明技巧:\n");
    printf("1. 从内向外阅读\n");
    printf("2. 先找标识符\n");
    printf("3. 注意括号优先级\n");
    printf("4. 使用typedef简化复杂声明\n\n");
}

// 9. 指针与性能优化
void pointers_and_performance() {
    printf("=== 指针与性能优化 ===\n");

    const int SIZE = 1000000;
    int *large_array = (int*)malloc(SIZE * sizeof(int));

    if(large_array == NULL) {
        printf("内存分配失败\n");
        return;
    }

    // 初始化数组
    for(int i = 0; i < SIZE; i++) {
        large_array[i] = i;
    }

    // 方法1：使用数组下标（较慢）
    clock_t start = clock();
    int sum1 = 0;
    for(int i = 0; i < SIZE; i++) {
        sum1 += large_array[i];
    }
    clock_t end = clock();
    printf("数组下标方式 - 时间: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    // 方法2：使用指针（较快）
    start = clock();
    int sum2 = 0;
    int *ptr = large_array;
    for(int i = 0; i < SIZE; i++) {
        sum2 += *ptr++;
    }
    end = clock();
    printf("指针方式 - 时间: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    printf("总和: %d (两种方法结果相同)\n", sum1);

    // 方法3：使用寄存器指针（最快）
    start = clock();
    int sum3 = 0;
    register int *reg_ptr = large_array;
    for(int i = 0; i < SIZE; i++) {
        sum3 += *reg_ptr++;
    }
    end = clock();
    printf("寄存器指针方式 - 时间: %ld ms\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    free(large_array);

    printf("\n性能优化要点:\n");
    printf("1. 指针运算比数组下标快\n");
    printf("2. 使用寄存器指针进一步提高性能\n");
    printf("3. 避免在循环中进行指针运算\n");
    printf("4. 利用局部性原理\n\n");
}

// 10. 通用数据结构的指针应用
typedef struct {
    void *data;
    size_t size;
    int type;  // 0: int, 1: float, 2: char*
} GenericContainer;

void print_generic_container(GenericContainer *container) {
    switch(container->type) {
        case 0:  // int
            printf("整数: %d\n", *((int*)container->data));
            break;
        case 1:  // float
            printf("浮点数: %.2f\n", *((float*)container->data));
            break;
        case 2:  // char*
            printf("字符串: %s\n", (char*)container->data);
            break;
        default:
            printf("未知类型\n");
    }
}

void generic_data_structures() {
    printf("=== 通用数据结构 ===\n");

    GenericContainer containers[3];

    // 整数容器
    int int_value = 42;
    containers[0].data = &int_value;
    containers[0].size = sizeof(int);
    containers[0].type = 0;

    // 浮点数容器
    float float_value = 3.14159;
    containers[1].data = &float_value;
    containers[1].size = sizeof(float);
    containers[1].type = 1;

    // 字符串容器
    char *string_value = "Hello World";
    containers[2].data = string_value;
    containers[2].size = strlen(string_value) + 1;
    containers[2].type = 2;

    printf("通用容器内容:\n");
    for(int i = 0; i < 3; i++) {
        print_generic_container(&containers[i]);
    }

    printf("\n");
}

int main() {
    printf("C语言指针高级应用学习\n");
    printf("=====================\n\n");

    dynamic_memory_management();
    function_pointers();
    callback_functions();
    pointers_and_structures();
    dynamic_2d_arrays();
    pointers_and_linked_lists();
    pointers_and_file_operations();
    complex_pointer_declarations();
    pointers_and_performance();
    generic_data_structures();

    printf("指针高级应用总结:\n");
    printf("1. 动态内存管理是C语言的核心\n");
    printf("2. 函数指针实现多态和回调\n");
    printf("3. 指针与结构体结合创建复杂数据结构\n");
    printf("4. 动态多维数组需要多级指针\n");
    printf("5. 链表是指针的经典应用\n");
    printf("6. 理解复杂指针声明很重要\n");
    printf("7. 指针可以显著提高性能\n");
    printf("8. void指针用于通用编程\n");

    return 0;
}
