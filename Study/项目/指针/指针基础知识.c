/*
 * C语言指针基础知识详解
 *
 * 指针是C语言的灵魂，理解指针是掌握C语言的关键
 */

#include <stdio.h>

// 1. 指针的基本概念
void pointer_basic_concepts() {
    printf("=== 指针基本概念 ===\n");

    int num = 42;
    int *ptr = &num;  // ptr指向num的地址

    printf("变量num的值: %d\n", num);
    printf("变量num的地址: %p\n", (void*)&num);
    printf("指针ptr的值（存储的地址）: %p\n", (void*)ptr);
    printf("指针ptr指向的值: %d\n", *ptr);
    printf("指针ptr自己的地址: %p\n", (void*)&ptr);

    printf("\n指针概念总结:\n");
    printf("1. &运算符：获取变量的地址\n");
    printf("2. *运算符：解引用，获取指针指向的值\n");
    printf("3. 指针变量存储的是内存地址\n");
    printf("4. 指针本身也有自己的地址\n\n");
}

// 2. 指针的声明和初始化
void pointer_declaration_initialization() {
    printf("=== 指针声明和初始化 ===\n");

    int a = 10, b = 20;

    // 方式1：声明后赋值
    int *ptr1;
    ptr1 = &a;
    printf("ptr1指向a: %d\n", *ptr1);

    // 方式2：声明时初始化
    int *ptr2 = &b;
    printf("ptr2指向b: %d\n", *ptr2);

    // 方式3：指向NULL（空指针）
    int *ptr3 = NULL;
    if(ptr3 == NULL) {
        printf("ptr3是空指针\n");
    }

    // 方式4：指向同一变量的多个指针
    int *ptr4 = &a;
    int *ptr5 = &a;
    printf("ptr4和ptr5都指向a: %d, %d\n", *ptr4, *ptr5);

    printf("\n");
}

// 3. 指针运算
void pointer_arithmetic() {
    printf("=== 指针运算 ===\n");

    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // 指向数组首元素

    printf("数组地址: %p\n", (void*)arr);
    printf("ptr初始指向: %p, 值: %d\n", (void*)ptr, *ptr);

    // 指针加法
    ptr = ptr + 1;
    printf("ptr + 1 指向: %p, 值: %d\n", (void*)ptr, *ptr);

    // 指针减法
    ptr = ptr - 1;
    printf("ptr - 1 指向: %p, 值: %d\n", (void*)ptr, *ptr);

    // 指针递增
    ptr++;
    printf("ptr++ 指向: %p, 值: %d\n", (void*)ptr, *ptr);

    // 指针递减
    ptr--;
    printf("ptr-- 指向: %p, 值: %d\n", (void*)ptr, *ptr);

    // 指针相减（计算元素个数）
    int *start = &arr[0];
    int *end = &arr[4];
    printf("start和end之间的元素个数: %ld\n", end - start);

    // 指针比较
    if(start < end) {
        printf("start指针在end指针之前\n");
    }

    printf("\n指针运算规则:\n");
    printf("1. ptr + n 移动 n * sizeof(类型) 字节\n");
    printf("2. ptr - n 移动 n * sizeof(类型) 字节\n");
    printf("3. ptr1 - ptr2 得到元素个数差值\n");
    printf("4. 指针可以比较大小（同一数组内）\n\n");
}

// 4. 指针与数组的关系
void pointers_and_arrays() {
    printf("=== 指针与数组的关系 ===\n");

    int arr[5] = {1, 2, 3, 4, 5};

    printf("数组名arr: %p\n", (void*)arr);
    printf("&arr[0]: %p\n", (void*)&arr[0]);
    printf("arr == &arr[0]: %s\n", arr == &arr[0] ? "true" : "false");

    // 使用指针访问数组元素
    int *ptr = arr;
    printf("\n使用指针访问数组:\n");
    for(int i = 0; i < 5; i++) {
        printf("arr[%d] = %d, *(ptr + %d) = %d\n",
               i, arr[i], i, *(ptr + i));
    }

    // 数组名是指针常量
    printf("\n数组名特性:\n");
    printf("arr + 1: %p\n", (void*)(arr + 1));
    printf("&arr + 1: %p\n", (void*)(&arr + 1));
    printf("注意：arr + 1 移动一个元素，&arr + 1 移动整个数组\n");

    printf("\n");
}

// 5. 指针与字符串
void pointers_and_strings() {
    printf("=== 指针与字符串 ===\n");

    // 方式1：字符数组
    char str1[] = "Hello";
    printf("字符数组: %s\n", str1);

    // 方式2：字符指针
    char *str2 = "World";
    printf("字符指针: %s\n", str2);

    // 区别：字符数组可以修改，字符指针指向的字符串常量不能修改
    str1[0] = 'h';  // 正确
    // str2[0] = 'w';  // 错误！运行时错误

    printf("修改后str1: %s\n", str1);

    // 使用指针遍历字符串
    char *ptr = str1;
    printf("使用指针遍历: ");
    while(*ptr != '\0') {
        printf("%c ", *ptr);
        ptr++;
    }
    printf("\n");

    printf("\n字符串指针要点:\n");
    printf("1. char str[] 在栈上分配，可修改\n");
    printf("2. char *str 指向字符串常量，不可修改\n");
    printf("3. 使用指针可以高效遍历字符串\n\n");
}

// 6. 指针的类型和void指针
void pointer_types_and_void() {
    printf("=== 指针类型和void指针 ===\n");

    int num = 100;
    float fnum = 3.14;
    char ch = 'A';

    int *int_ptr = &num;
    float *float_ptr = &fnum;
    char *char_ptr = &ch;

    printf("int指针: %p, 值: %d\n", (void*)int_ptr, *int_ptr);
    printf("float指针: %p, 值: %.2f\n", (void*)float_ptr, *float_ptr);
    printf("char指针: %p, 值: %c\n", (void*)char_ptr, *char_ptr);

    // void指针（通用指针）
    void *void_ptr;
    void_ptr = &num;
    printf("void指针指向int: %p\n", void_ptr);

    void_ptr = &fnum;
    printf("void指针指向float: %p\n", void_ptr);

    // void指针不能直接解引用，需要类型转换
    printf("void指针解引用（转换为int）: %d\n", *((int*)void_ptr));

    printf("\nvoid指针特性:\n");
    printf("1. 可以指向任何类型的数据\n");
    printf("2. 不能直接解引用\n");
    printf("3. 使用前需要类型转换\n");
    printf("4. 常用于通用函数参数\n\n");
}

// 7. 多级指针
void multi_level_pointers() {
    printf("=== 多级指针 ===\n");

    int num = 42;
    int *ptr = &num;      // 一级指针
    int **pptr = &ptr;    // 二级指针
    int ***ppptr = &pptr; // 三级指针

    printf("变量num: %d\n", num);
    printf("变量num的地址: %p\n", (void*)&num);

    printf("一级指针ptr: %p\n", (void*)ptr);
    printf("*ptr: %d\n", *ptr);
    printf("ptr的地址: %p\n", (void*)&ptr);

    printf("二级指针pptr: %p\n", (void*)pptr);
    printf("*pptr: %p\n", (void*)*pptr);
    printf("**pptr: %d\n", **pptr);

    printf("三级指针ppptr: %p\n", (void*)ppptr);
    printf("*ppptr: %p\n", (void*)*ppptr);
    printf("**ppptr: %p\n", (void*)**ppptr);
    printf("***ppptr: %d\n", ***ppptr);

    printf("\n多级指针应用:\n");
    printf("1. 动态二维数组\n");
    printf("2. 函数参数传递指针的指针\n");
    printf("3. 链表等复杂数据结构\n\n");
}

// 8. 指针的安全使用
void pointer_safety() {
    printf("=== 指针安全使用 ===\n");

    // 1. 未初始化的指针
    int *dangerous_ptr;  // 未初始化，指向随机地址
    // printf("%d\n", *dangerous_ptr);  // 危险！未定义行为

    printf("未初始化指针是危险的！\n");

    // 2. 空指针检查
    int *null_ptr = NULL;
    if(null_ptr != NULL) {
        printf("安全访问: %d\n", *null_ptr);
    } else {
        printf("指针为空，不能解引用\n");
    }

    // 3. 野指针（指向已释放内存）
    int *wild_ptr = (int*)malloc(sizeof(int));
    *wild_ptr = 100;
    free(wild_ptr);
    // printf("%d\n", *wild_ptr);  // 危险！野指针

    printf("释放内存后应将指针设为NULL\n");
    wild_ptr = NULL;

    // 4. 指针越界访问
    int arr[3] = {1, 2, 3};
    int *ptr = arr;
    printf("有效访问: arr[2] = %d\n", *(ptr + 2));
    printf("越界访问: *(ptr + 3) = %d（结果不可预测）\n", *(ptr + 3));

    printf("\n指针安全准则:\n");
    printf("1. 总是初始化指针\n");
    printf("2. 使用前检查指针是否为NULL\n");
    printf("3. 释放内存后立即设为NULL\n");
    printf("4. 确保不越界访问\n");
    printf("5. 注意指针的生命周期\n\n");
}

// 9. const与指针
void const_and_pointers() {
    printf("=== const与指针 ===\n");

    int num = 10;
    int another = 20;

    // 情况1：指向常量的指针
    const int *ptr1 = &num;
    printf("const int *ptr1: 指向的值=%d\n", *ptr1);
    // *ptr1 = 30;  // 错误！不能通过ptr1修改值
    ptr1 = &another;  // 正确！可以改变指针指向

    // 情况2：常量指针
    int *const ptr2 = &num;
    printf("int *const ptr2: 指向的值=%d\n", *ptr2);
    *ptr2 = 30;  // 正确！可以通过ptr2修改值
    // ptr2 = &another;  // 错误！不能改变指针指向

    // 情况3：指向常量的常量指针
    const int *const ptr3 = &num;
    printf("const int *const ptr3: 指向的值=%d\n", *ptr3);
    // *ptr3 = 40;  // 错误！不能修改值
    // ptr3 = &another;  // 错误！不能改变指向

    printf("修改后num的值: %d\n", num);

    printf("\nconst指针总结:\n");
    printf("1. const int *ptr - 指向的值不能修改\n");
    printf("2. int *const ptr - 指针本身不能修改\n");
    printf("3. const int *const ptr - 值和指针都不能修改\n\n");
}

int main() {
    printf("C语言指针基础知识学习\n");
    printf("=====================\n\n");

    pointer_basic_concepts();
    pointer_declaration_initialization();
    pointer_arithmetic();
    pointers_and_arrays();
    pointers_and_strings();
    pointer_types_and_void();
    multi_level_pointers();
    pointer_safety();
    const_and_pointers();

    printf("指针学习要点总结:\n");
    printf("1. 指针存储内存地址\n");
    printf("2. &取地址，*解引用\n");
    printf("3. 指针运算基于类型大小\n");
    printf("4. 数组名是指向首元素的指针\n");
    printf("5. 注意指针的安全使用\n");
    printf("6. const与指针有多种组合\n");
    printf("7. 理解多级指针的概念\n");

    return 0;
}
