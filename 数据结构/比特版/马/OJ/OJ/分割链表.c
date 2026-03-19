// 给你一个链表的头节点head和一个特定值x,请你对链表进行分割
// 使得所有小于x的结点都出现在大于或等于x的结点之前

#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

ListNode *createList(int x)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

// 分割链表
ListNode *cutlist(ListNode *head, int e)
{
    // 处理边界问题
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    // 两个哑节点,分别代表小于x和大于等于x的链表
    ListNode small_dummy = {0, NULL};
    ListNode large_dummy = {0, NULL};

    ListNode *small = &small_dummy;
    ListNode *large = &large_dummy;
    ListNode *curr = head;

    while (curr != NULL)
    {
        if (curr->val < e)
        {
            small->next = curr;
            small = small->next;
        }
        else
        {
            large->next = curr;
            large = large->next;
        }
        curr = curr->next;
    }

    // 连接两个链表
    small->next = large_dummy.next;

    // 断开large链表的尾部,防止成环
    large->next = NULL;
    return small_dummy.next;
}

// 打印链表
void printList(ListNode *head)
{
    ListNode *p = head;
    while (p)
    {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

// 释放链表内存
void freeList(ListNode *head)
{
    ListNode *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main()
{
    // 构造测试链表:1 4 3 2 5 2 (x = 3)
    ListNode *head = createList(1);
    head->next = createList(4);
    head->next->next = createList(3);
    head->next->next->next = createList(2);
    head->next->next->next->next = createList(5);
    head->next->next->next->next->next = createList(2);

    printf("原始链表: ");
    printList(head);

    int x = 3;
    ListNode *result = cutlist(head, 3);
    printf("分割后的链表:");
    printList(result);

    // 释放内存
    freeList(result);

    return 0;
}