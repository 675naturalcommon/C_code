#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 数组nums包含从0到n的所有整数,但其中缺了一个,请编写代码找出那个缺失的整数.在O(n)时间内完成

// int findMissingNumber(int nums[], int n)
// {
//     int xor = n;
//     for (int i = 0; i < n; i++)
//     {
//         xor ^= i ^ nums[i];
//     }
//     return xor;
// }

// int main()
// {
//     int num1[] = {0, 1, 3};
//     int n1 = sizeof(num1) / sizeof(num1[0]);
//     printf("缺失的数字是%d\n", findMissingNumber(num1, n1));
//     return 0;
// }

// 数学求和法
// int findMissingNumber(int nums[], int n)
// {
//     // 计算0~n项数的和
//     int total = (n) * (n + 1) / 2;
//     // 计算数组元素的和
//     int sum = 0;
//     for (int i = 0; i < n; i++)
//     {
//         sum += nums[i];
//     }
//     // 0~n项数的和减去数组元素的和即为缺失的数字
//     return total - sum;
// }

// int main()
// {
//     int num[] = {0, 1, 3};
//     int n = sizeof(num) / sizeof(num[0]);
//     printf("缺失的数字是%d\n", findMissingNumber(num, n));

//     return 0;
// }
