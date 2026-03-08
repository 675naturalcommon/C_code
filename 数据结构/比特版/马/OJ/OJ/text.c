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

// 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回新的头节点

//     示例 1：
//     输入：head = [ 1, 2, 6, 3, 4, 5, 6 ],val = 6
//     输出：[1, 2, 3, 4, 5]

//     示例 2：
//     输入：head = [],val = 1
//     输出：[]

//     示例 3：
//     输入：head = [ 7, 7, 7, 7 ], val = 7
//     输出：[]

struct ListNode
{
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

struct ListNode *removeElements(ListNode *head, int val)
{
    // 处理空链表
    if (head == NULL)
    {
        return;
    }

    // 创建虚拟节点
    ListNode dummy;
    dummy.next = head;

    // 创建prev节点和cur节点,使prev->next = cur
    ListNode *prev = &dummy;
    ListNode *cur = head;

    while (cur != NULL) // 当前节点不为空进入循环条件
    {
        if (cur->val == val) // 当前节点中存储的值与要查找的值相等
        {
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        }
        else
        {
            // 向后移动节点指针
            prev = cur;
            cur = cur->next;
        }
    }

    return dummy.next;
}

// 创建一个新链表,并将结果对齐进行尾插
struct ListNode *removeElements(ListNode *head, int val)
{
    // 创建虚拟节点
    ListNode dummy;
    dummy.next = NULL;
    // 创建一个tail指针存储的是dummy中的地址
    ListNode *tail = &dummy;

    ListNode *cur = head;
    while (cur != NULL)
    {
        // 当前节点中存储的值不等于val
        if (cur->val != val)
        {
            // 将有效链表从原链表取下,插入新链表
            cur->next = NULL; // 断开原链表连接
            tail->next = cur;
            tail = cur;
        }
        else
        {
            // 释放值为val的节点
            free(cur);
        }
        cur = cur->next;
    }

    return dummy.next;
}

// 给你单链表的头节点head,请你反转链表,并返回反转后的链表.
// 输入：head = [1,2,3,4,5]
// 输出：[5,4,3,2,1]

struct ListNode *reverseList(struct ListNode *head)
{
    if (head == NULL)
    {
        return head;
    }

    ListNode *n1, *n2, *n3;
    n1 = NULL;
    n2 = head;
    n3 = head->next;
    while (n2)
    {
        n2->next = n1;
        n1 = n2;
        n2 = n3;
        if (n3)
        {
            n3 = n3->next;
        }
    }
    return n1;
}

// 迭代法实现
struct ListNode *reverseList(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    ListNode *prev = NULL; // 前一个结点的指针
    ListNode *cur = head;  // 当前节点的指针
    ListNode *next = NULL; // 下个节点的指针

    while (cur)
    {
        next = cur->next; // 保存下一个节点
        cur->next = prev; // 反转当前节点的指针
        prev = cur;       // 更新前一个节点
        cur = next;       // 更新当前节点
    }
    return prev;
}

// 给你单链表的头结点 head,请你找出并返回链表的中间结点
// 如果有两个中间结点,则返回第二个中间结点

// 输入：head = [1,2,3,4,5]
// 输出：[3,4,5]
// 解释：链表只有一个中间结点，值为 3

// 输入：head = [1,2,3,4,5,6]
// 输出：[4,5,6]
// 解释：该链表有两个中间结点，值分别为 3 和 4 ，返回第二个结点。

struct ListNode *middleNode(struct ListNode *head)
{
    if (head == NULL)
        return head;

    int length = 0; // 用来记录节点的长度
    ListNode *dummy = head;
    ListNode *cur = head;
    while (dummy)
    {
        dummy = dummy->next;
        length++;
    }
    for (int i = 0; i < length / 2; i++)
    {
        head = head->next;
    }
    return head;
}

// 使用快慢指针法
struct ListNode *middleNode(struct ListNode *head)
{
    if (head == NULL)
        return head;

    ListNode *slow = head;
    ListNode *fast = head;
    // 满指针每次走一步,快指针每次走两步,快指针是慢指针速度的两倍,当快指针走向尾节点的时候,慢指针走了链表的一半
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 将两个升序链表合并为一个新的升序链表并返回,新链表是通过拼接给定的两个链表的所有节点组成的

// 示例 1:
// 输入：l1 = [1,2,4], l2 = [1,3,4]
// 输出：[1,1,2,3,4,4]

// 示例 2：
// 输入：l1 = [], l2 = []
// 输出：[]

// 示例 3：
// 输入：l1 = [], l2 = [0]
// 输出：[0]

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    ListNode *l1 = list1, *l2 = list2;
    if (l1 && l2 == NULL) // l1不为空,l2为空
    {
        return l1;
    }
    else if (l2 && l1 == NULL) // l2不为空,l1为空
    {
        return l2;
    }
    else if (l1 == NULL && l2 == NULL) // l1和l2都为空
    {
        return NULL;
    }

    ListNode *newHead = NULL, *newTail = NULL;
    while (l1 && l2) // l1和l2两个都不为空则进入循环条件
    {
        if (l1->val < l2->val) // 判断l1中第一个结点的值是否小于l2中第一个结点的值
        {
            if (newHead == NULL) // 如果头节点为空,说明这是要插入的第一个节点
            {
                newHead = newTail = l1;
            }
            else
            {
                newTail->next = l1;
                newTail = newTail->next;
            }
            l1 = l1->next;
        }
        else
        {
            if (newHead == NULL)
            {
                newHead = newTail = l2;
            }
            else
            {
                newTail->next = l2;
                newTail = newTail->next;
            }
            l2 = l2->next;
        }
    }

    // 当l1或l2为空
    if (l1)
    {
        newTail->next = l1;
    }
    if (l2)
    {
        newTail->next = l2;
    }

    return newHead;
}

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    ListNode *l1 = list1, *l2 = list2;
    ListNode dummy;          // 哑节点,简化边界处理
    ListNode *tail = &dummy; // 尾指针
    dummy.next = NULL;

    // 遍历两个链表,每次取较小节点接在tail后面
    while (l1 && l2)
    {
        if (l1->val <= l2->val)
        {
            tail->next = l1;
            l1 = l1->next;
        }
        else
        {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // 连接剩余链表
    if (l1)
    {
        tail->next = l1;
    }
    if (l2)
    {
        tail->next = l2;
    }

    return dummy.next;
}