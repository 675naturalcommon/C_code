#define _CRT_SECURE_NO_WARNINGS

// 给你一个数组nums和一个值val,你需要原地移除所有数值等于val的元素,并返回移除后数组的新长度
// 不要使用额外的数组空间,你必须仅用O(1)额外空间并原地修改输入数组
// 元素的顺序可以改变,你不需要考虑数组中超出新长度后面的元素
//
// 输入:nums = [3,2,2,3],val = 3
// 输出:2,nums = [2,2]
// 解释:函数应该返回新的长度2,并且nums中的前两个元素均为2,你不需要考虑数组中超出新长度
// 后面的元素.例如,函数返回的新长度为2,而nums = [2,2,3,3]或nums = [2,2,0,0],也会被视作正确答案

int removeElement(int *nums, int numsSize, int val)
{
    int left = 0;
    for (int right = 0; right < numsSize; right++)
    {
        if (nums[right] != val)
        {
            nums[left] = nums[right];
            left++;
        }
    }
    return left;
}

int removeElement(int *nums, int numsSize, int val)
{
    int left = 0;
    int right = 0;
    for (right = 0; right < numsSize; right++)
    {
        if (nums[right] != val)
        {
            nums[left] = nums[right];
            left++;
        }
    }
    return left;
}

// 给你两个按非递减顺序排列的整数数组nums1和nums2,另有两个整数m和n,
// 分别表示nums1和nums2中的元素数目.
// 请你合并nums2到nums1中,使合并后的数组同样按非递减顺序排列.

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
    {
        nums1[m + i] = nums2[i];
    }
    for (i = 0; i < m + n; i++)
    {
        for (int j = 0; j < m + n - i - 1; j++)
        {
            int temp = 0;
            if (nums1[j] > nums1[j + 1])
            {
                temp = nums1[j];
                nums1[j] = nums1[j + 1];
                nums1[j + 1] = temp;
            }
        }
    }
}

void merge(int *nums1, int nums1Size, int m, int *nums2, int nums2Size, int n)
{
    int p1 = m - 1;
    int p2 = n - 1;
    int p = m + n - 1;
    while (p1 >= 0 && p2 >= 0)
    {
        if (nums1[p1] > nums2[p2])
        {
            nums1[p--] = nums1[p1--];
        }
        else
        {
            nums1[p--] = nums2[p2--];
        }
    }
    while (p2 >= 0)
    {
        nums1[p--] = nums2[p2--];
    }
}
