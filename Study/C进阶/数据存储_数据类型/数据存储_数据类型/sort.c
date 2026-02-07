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