// 编号从1-n的n个人围成一圈,从编号为1的人开始报数,报到m的人离开.下一个人继续从n开始报数.
// n-1轮结束以后,只剩下一个人,问最后留下的人编号是多少?

// 输入: 5  2
// 返回值: 3
// 说明:开始5个人 1,2,3,4,5,从1开始报数,1->1,2->2编号为2的人离开
// 1,3,4,5 从3开始报数3->1,4->2,编号为4的人离开
// 1,3,5 从5开始报数 5->1,1->2,编号为1的人离开
// 3,5 从3开始报数,3->1,5->2,编号为5的人离开
// 剩下3

// 进阶:空间复杂度O(1),时间复杂度O(n)

// #include <stdio.h>

// int main(void)
// {
//     long long n = 0;
//     long long m = 0;
//     if (scanf("%lld %lld", &n, &m) != 2) {
//         return 0;
//     }

//     if (n <= 0 || m <= 0) {
//         return 0;
//     }

//     long long last = 0; // 0-based index
//     for (long long i = 2; i <= n; ++i) {
//         last = (last + m) % i;
//     }

//     printf("%lld", last + 1);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

// 定义链表结点结构
struct ListNode
{
    int val;
    struct ListNode *next;
};
typedef struct ListNode ListNode;

// 创建一个包含n个结点的环形链表
ListNode *createCircle(int n)
{
    ListNode *head = NULL, *prev = NULL; // 创建两个节点,开始都将其初始化为空节点
    for (int i = 1; i <= n; i++)
    {
        // 申请动态内存空间
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->val = i; // 将申请的新节点中的数据值赋值为i
        if (i == 1)       // 如果是申请的第一个节点,那么要使head指向新节点
        {
            head = newNode;
        }
        else
        {
            prev->next = newNode; // 上一个结点指向当前新节点
        }
        prev = newNode; // 初始时,i==1,prev指向的也是第一个节点
    }
    prev->next = head;
    return head;
}

int solveJosephus(int n, int m)
{
    if (n == 1)
        return 1; // 只有一个结点,也是剩下的唯一一个节点
    if (m == 1)
        return n; // 特殊情况:报1就走,最后剩下的是原序列第n个人

    ListNode *curr = createCircle(n); // 创建环形链表
    ListNode *prev = NULL;

    // 找到头节点的前驱结点,方便删除操作
    prev = curr;
    while (prev->next != curr)
    {
        prev = prev->next;
    }
    // 循环结束后,prev指向的是第n个结点

    // 开始游戏,直到只剩一个结点
    while (curr->next != curr) // 链表中的结点只要大于1个,循环就继续
    {
        // 报数:移动m-1次到达报数m的人
        for (int i = 1; i < m; i++)
        {
            prev = curr; // 使prev指向的永远是当前节点的前一个结点
            curr = curr->next;
        }

        // 剔除当前结点curr
        prev->next = curr->next;
        printf("编号 %d 出局\n", curr->val);

        ListNode *temp = curr;
        curr = curr->next; // 下一个人从1开始重新报数
        free(temp);        // 释放内存
    }

    int result = curr->val;
    free(curr); // 释放最后一个节点
    return result;
}

int main()
{
    int n, m;
    printf("请输入人数 n 和报数 m:");
    if (scanf("%d %d", &n, &m) == 2)
    {
        int winner = solveJosephus(n, m);
        printf("最后剩下的人的编号是:%d\n", winner);
    }
    return 0;
}