#define _CRT_SECURE_NO_WARNINGS


//deepseek生成


//#include <stdio.h>
//#include <stdlib.h>
//
////快速排序的分区函数
//int partition(int arr[], int low, int high)
//{
//   int pivot = arr[high];
//   int i = low - 1;
//
//   for (int j = low; j < high; j++)
//   {
//       if (arr[j] <= pivot)
//       {
//           i++;
//           // 交换arr[i]和arr[j]
//           int temp = arr[i];
//           arr[i] = arr[j];
//           arr[j] = temp;
//       }
//   }
//
//   // 交换arr[i+1]和arr[high]
//   int temp = arr[i + 1];
//   arr[i + 1] = arr[high];
//   arr[high] = temp;
//
//   return i + 1;
//}
//
//// 快速排序函数
//void quickSort(int arr[], int low, int high)
//{
//   if (low < high)
//   {
//       int pi = partition(arr, low, high);
//
//       quickSort(arr, low, pi - 1);
//       quickSort(arr, pi + 1, high);
//   }
//}
//
//// 冒泡排序函数（作为备选）
//void bubbleSort(int arr[], int size)
//{
//   for (int i = 0; i < size - 1; i++)
//   {
//       for (int j = 0; j < size - i - 1; j++)
//       {
//           if (arr[j] > arr[j + 1])
//           {
//               // 交换arr[j]和arr[j+1]
//               int temp = arr[j];
//               arr[j] = arr[j + 1];
//               arr[j + 1] = temp;
//           }
//       }
//   }
//}
//
//int main()
//{
//   int n, m;
//
//   // 读取n和m
//   scanf("%d %d", &n, &m);
//
//   // 分配内存
//   int* arr1 = (int*)malloc(n * sizeof(int));
//   int* arr2 = (int*)malloc(m * sizeof(int));
//   int* result = (int*)malloc((n + m) * sizeof(int));
//
//   // 读取第一个序列
//   for (int i = 0; i < n; i++)
//   {
//       scanf("%d", &arr1[i]);
//   }
//
//   // 读取第二个序列
//   for (int i = 0; i < m; i++)
//   {
//       scanf("%d", &arr2[i]);
//   }
//
//   // 将两个数组的元素合并到第三个数组
//   int k = 0;
//   for (int i = 0; i < n; i++)
//   {
//       result[k++] = arr1[i];
//   }
//   for (int i = 0; i < m; i++)
//   {
//       result[k++] = arr2[i];
//   }
//
//   // 对合并后的数组进行排序
//   // 方法1：使用快速排序
//   quickSort(result, 0, n + m - 1);
//
//   // 方法2：或者使用冒泡排序（对于小规模数据可用）
//   // bubbleSort(result, n + m);
//
//   // 方法3：使用C标准库的qsort函数（最简单）
//   // #include <stdlib.h> 已包含
//   // qsort(result, n + m, sizeof(int), compare);
//   // 需要定义比较函数：
//   // int compare(const void* a, const void* b) {
//   //     return (*(int*)a - *(int*)b);
//   // }
//
//   // 输出合并后的序列
//   for (int i = 0; i < n + m; i++)
//   {
//       printf("%d", result[i]);
//       if (i < n + m - 1)
//       {
//           printf(" ");
//       }
//   }
//   printf("\n");
//
//   // 释放内存
//   free(arr1);
//   free(arr2);
//   free(result);
//
//   return 0;
//}



//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//// 宏定义，用于交换两个元素
//#define SWAP(a, b, size) do { \
//    size_t __size = (size); \
//    char *__a = (a), *__b = (b); \
//    do { \
//        char __tmp = *__a; \
//        *__a++ = *__b; \
//        *__b++ = __tmp; \
//    } while (--__size > 0); \
//} while (0)
//
//// 分区函数 - 使用Lomuto分区方案
//static void* partition(void* base, size_t nmemb, size_t size,
//    int (*compar)(const void*, const void*),
//    void* swap_buffer) 
//{
//    char* arr = (char*)base;
//    char* pivot = arr + (nmemb - 1) * size;  // 选择最后一个元素作为基准
//
//    int i = -1;  // 小于基准的边界索引
//
//    for (size_t j = 0; j < nmemb - 1; j++)
//    {
//        char* elem = arr + j * size;
//        if (compar(elem, pivot) <= 0) 
//        {
//            i++;
//            SWAP(arr + i * size, elem, size);
//        }
//    }
//
//    // 将基准放到正确位置
//    SWAP(arr + (i + 1) * size, pivot, size);
//    return arr + (i + 1) * size;
//}
//
//// 优化的分区函数 - 使用Hoare分区方案（更高效）
//static int hoare_partition(void* base, size_t nmemb, size_t size,
//    int (*compar)(const void*, const void*)) 
//{
//    char* arr = (char*)base;
//    char* pivot = arr;  // 选择第一个元素作为基准
//
//    int left = 0;
//    int right = nmemb - 1;
//
//    while (1) 
//    {
//        // 从左向右找第一个大于基准的元素
//        while (left <= right && compar(arr + left * size, pivot) < 0) 
//        {
//            left++;
//        }
//
//        // 从右向左找第一个小于基准的元素
//        while (left <= right && compar(arr + right * size, pivot) > 0) 
//        {
//            right--;
//        }
//
//        if (left >= right) 
//        {
//            break;
//        }
//
//        // 交换左右元素
//        SWAP(arr + left * size, arr + right * size, size);
//        left++;
//        right--;
//    }
//
//    return right;
//}
//
//// 插入排序 - 对小数组更高效
//static void insertion_sort(void* base, size_t nmemb, size_t size,
//    int (*compar)(const void*, const void*))
//{
//    char* arr = (char*)base;
//    char* key = malloc(size);
//
//    for (size_t i = 1; i < nmemb; i++)
//    {
//        char* current = arr + i * size;
//        memcpy(key, current, size);
//
//        int j = i - 1;
//        while (j >= 0 && compar(arr + j * size, key) > 0) 
//        {
//            memcpy(arr + (j + 1) * size, arr + j * size, size);
//            j--;
//        }
//        memcpy(arr + (j + 1) * size, key, size);
//    }
//
//    free(key);
//}
//
//// 三数取中法选择基准 - 避免最坏情况
//static void* median_of_three(void* base, size_t nmemb, size_t size,
//    int (*compar)(const void*, const void*))
//{
//    char* arr = (char*)base;
//    size_t mid = nmemb / 2;
//
//    char* first = arr;
//    char* middle = arr + mid * size;
//    char* last = arr + (nmemb - 1) * size;
//
//    // 对三个元素排序，取中值
//    if (compar(first, middle) > 0) 
//    {
//        SWAP(first, middle, size);
//    }
//    if (compar(first, last) > 0) 
//    {
//        SWAP(first, last, size);
//    }
//    if (compar(middle, last) > 0) 
//    {
//        SWAP(middle, last, size);
//    }
//
//    // 将中值交换到第一个位置
//    SWAP(first, middle, size);
//
//    return first;
//}
//
//// 快速排序主函数
//void my_qsort(void* base, size_t nmemb, size_t size,
//    int (*compar)(const void*, const void*)) 
//{
//    // 小数组使用插入排序
//    if (nmemb <= 7) 
//    {
//        insertion_sort(base, nmemb, size, compar);
//        return;
//    }
//
//    char* arr = (char*)base;
//
//    // 使用三数取中法选择基准并放到开始位置
//    median_of_three(base, nmemb, size, compar);
//
//    // 使用Hoare分区方案
//    int pivot_index = hoare_partition(base, nmemb, size, compar);
//
//    // 递归排序左半部分
//    if (pivot_index > 0)
//    {
//        my_qsort(base, pivot_index + 1, size, compar);
//    }
//
//    // 递归排序右半部分
//    if ((size_t)pivot_index + 1 < nmemb - 1)
//    {
//        my_qsort(arr + (pivot_index + 1) * size,
//            nmemb - pivot_index - 1, size, compar);
//    }
//}
//
//// ============ 测试代码 ============
//
//// 比较函数示例
//int compare_int(const void* a, const void* b) 
//{
//    return (*(int*)a - *(int*)b);
//}
//
//int compare_double(const void* a, const void* b) 
//{
//    double diff = *(double*)a - *(double*)b;
//    return (diff > 0) - (diff < 0);  // 避免精度问题
//}
//
//int compare_string(const void* a, const void* b) 
//{
//    return strcmp(*(const char**)a, *(const char**)b);
//}
//
//// 结构体示例
//typedef struct {
//    int id;
//    char name[20];
//    double score;
//} Student;
//
//int compare_student_by_id(const void* a, const void* b)
//{
//    return ((Student*)a)->id - ((Student*)b)->id;
//}
//
//int compare_student_by_score(const void* a, const void* b)
//{
//    double diff = ((Student*)a)->score - ((Student*)b)->score;
//    return (diff > 0) - (diff < 0);
//}
//
//// 打印数组
//void print_int_array(int arr[], int n) 
//{
//    for (int i = 0; i < n; i++) 
//    {
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
//}
//
//void print_student_array(Student arr[], int n) 
//{
//    for (int i = 0; i < n; i++) 
//    {
//        printf("ID: %d, Name: %s, Score: %.2f\n",arr[i].id, arr[i].name, arr[i].score);
//    }
//}
//
//// 性能测试
//void performance_test() 
//{
//    printf("\n=== 性能测试 ===\n");
//
//    srand(time(NULL));
//    const int SIZE = 10000;
//    int* arr1 = malloc(SIZE * sizeof(int));
//    int* arr2 = malloc(SIZE * sizeof(int));
//
//    // 生成随机数据
//    for (int i = 0; i < SIZE; i++) 
//    {
//        arr1[i] = arr2[i] = rand() % 10000;
//    }
//
//    clock_t start, end;
//
//    // 测试标准库qsort
//    start = clock();
//    qsort(arr1, SIZE, sizeof(int), compare_int);
//    end = clock();
//    printf("标准库qsort耗时: %.6f秒\n",
//        (double)(end - start) / CLOCKS_PER_SEC);
//
//    // 重置数据
//    for (int i = 0; i < SIZE; i++) 
//    {
//        arr1[i] = arr2[i] = rand() % 10000;
//    }
//
//    // 测试自定义qsort
//    start = clock();
//    my_qsort(arr2, SIZE, sizeof(int), compare_int);
//    end = clock();
//    printf("自定义my_qsort耗时: %.6f秒\n",
//        (double)(end - start) / CLOCKS_PER_SEC);
//
//    // 验证排序结果
//    int correct = 1;
//    for (int i = 1; i < SIZE; i++) 
//    {
//        if (arr2[i] < arr2[i - 1]) 
//        {
//            correct = 0;
//            break;
//        }
//    }
//    printf("排序结果: %s\n", correct ? "正确" : "错误");
//
//    free(arr1);
//    free(arr2);
//}
//
//int main() {
//    printf("测试1: 整型数组排序\n");
//    int int_arr[] = { 64, 34, 25, 12, 22, 11, 90, 5 };
//    int n = sizeof(int_arr) / sizeof(int_arr[0]);
//
//    printf("排序前: ");
//    print_int_array(int_arr, n);
//
//    my_qsort(int_arr, n, sizeof(int), compare_int);
//
//    printf("排序后: ");
//    print_int_array(int_arr, n);
//
//    printf("\n测试2: 结构体数组排序\n");
//    Student students[] = {
//        {3, "Alice", 85.5},
//        {1, "Bob", 92.0},
//        {4, "Charlie", 78.5},
//        {2, "David", 88.0}
//    };
//    int student_count = sizeof(students) / sizeof(students[0]);
//
//    printf("按ID排序:\n");
//    my_qsort(students, student_count, sizeof(Student), compare_student_by_id);
//    print_student_array(students, student_count);
//
//    printf("\n按分数排序:\n");
//    my_qsort(students, student_count, sizeof(Student), compare_student_by_score);
//    print_student_array(students, student_count);
//
//    printf("\n测试3: 字符串数组排序\n");
//    const char* str_arr[] = { "banana", "apple", "cherry", "date", "fig" };
//    int str_count = sizeof(str_arr) / sizeof(str_arr[0]);
//
//    printf("排序前:\n");
//    for (int i = 0; i < str_count; i++) 
//    {
//        printf("%s ", str_arr[i]);
//    }
//
//    my_qsort(str_arr, str_count, sizeof(char*), compare_string);
//
//    printf("\n排序后:\n");
//    for (int i = 0; i < str_count; i++) 
//    {
//        printf("%s ", str_arr[i]);
//    }
//    printf("\n");
//
//    // 性能测试
//    performance_test();
//
//    return 0;
//}