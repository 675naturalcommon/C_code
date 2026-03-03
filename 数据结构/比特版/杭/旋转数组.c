#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 给定一个数组,将数组中的元素向右移动k个位置,其中k是非负数

// 辅助函数:打印数组
void printArray(int *nums, int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%d", nums[i]);
        if (i != size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

// 方法一:三次反转法
void reverse(int *nums, int start, int end)
{
    while (start < end)
    {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void rotate_reverse(int *nums, int numSize, int k)
{
    if (numSize <= 1)
        return;

    k = k % numSize; //
    if (k == 0)
        return;

    reverse(nums, 0, numSize - 1); // 反转整个数组
    reverse(nums, 0, k - 1);       // 反转前k个元素
    reverse(nums, k, numSize - 1); // 反转后numSize-k个元素
}

// 方法二:循环移动法
int gcd(int a, int b)
{
    while (b)
    {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void rotate_cycle(int *nums, int numSize, int k)
{
    if (numSize <= 1)
        return;
    k = k % numSize;
    if (k == 0)
        return;

    int g = gcd(numSize, k);
    for (int i = 0; i < g; i++)
    {
        int temp = nums[i];
        int j = i;
        while (true)
        {
            int prev = (j - k + numSize) % numSize;
            if (prev == i)
                break;
            nums[j] = nums[prev];
            j = prev;
        }
        nums[j] = temp;
    }
}

// 方法三:块交换法
void swapBlock(int *nums, int a, int b, int len)
{
    for (int i = 0; i < len; i++)
    {
        int temp = nums[a + i];
        nums[a + i] = nums[b + i];
        nums[b + i] = temp;
    }
}

void leftRotate_block(int *nums, int n, int k)
{
    // 左移k位(0<k<n)
    int start = 0;
    int len = n;
    int rot = k;
    while (rot != 0 && rot != len)
    {
        if (rot <= len - rot)
        {
            // 左边块 <= 右边块:交换左边块与右边块的前rot个元素
            swapBlock(nums, start, start + len - rot, rot);
            start += rot;
            len -= rot;
        }
        else
        {
            // 左边块 > 右边块:交换左边块的后(len-rot)个元素与整个右边块
            swapBlock(nums, start + 2 * rot - len, start + rot, len - rot);
            int new_rot = 2 * rot - len;
            len = rot;
            rot = new_rot;
            // start不变
        }
    }
}

void rotate_block(int *nums, int numSize, int k)
{
    if (numSize <= 1)
        return;
    k = k % numSize;
    if (k == 0)
        return;
    leftRotate_block(nums, numSize, k);
}

int main()
{
    int nums1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sz = sizeof(nums1) / sizeof(nums1[0]);
    int k = 3;

    printf("原数组: ");
    printArray(nums1, sz);

    rotate_reverse(nums1, sz, k);
    printf("方法一: 反转法: ");
    printArray(nums1, sz);

    rotate_cycle(nums2, sz, k);
    printf("方法二: 循环移动法: ");
    printArray(nums2, sz);

    rotate_block(nums3, sz, k);
    printf("方法三: 块交换法: ");
    printArray(nums3, sz);

    return 0;
}