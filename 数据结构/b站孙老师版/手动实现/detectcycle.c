#include <stdio.h>
#include <stdlib.h>

// 链表节点定义
typedef struct ListNode
{
    int val;
    struct ListNode *next;
} ListNode;

// 判断是否有环，返回1表示有环，0表示无环
int hasCycle(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return 0;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return 1; // 相遇，有环
        }
    }
    return 0; // 无环
}

// 找出环的入口节点，若无环返回NULL
ListNode *detectCycle(ListNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return NULL;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    // 第一步：判断是否有环并找到相遇点
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            break; // 相遇
        }
    }
    // 若无环，返回NULL
    if (fast == NULL || fast->next == NULL)
    {
        return NULL;
    }
    // 第二步：找入口
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow; // 环入口节点
}

// 创建节点
ListNode *createNode(int val)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

int main()
{
    // 构造一个有环链表：1->2->3->4->5->3（环入口为3）
    ListNode *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = head->next->next; // 5->3

    if (hasCycle(head))
    {
        printf("链表有环\n");
        ListNode *entry = detectCycle(head);
        if (entry != NULL)
        {
            printf("环的入口节点值为: %d\n", entry->val);
        }
    }
    else
    {
        printf("链表无环\n");
    }
    return 0;
}
