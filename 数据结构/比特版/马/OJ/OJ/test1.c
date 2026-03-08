#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
} ListNode;

// 原函数
void recoderList(ListNode* head)
{
    if (head == NULL || head->next == NULL || head->next->next == NULL)
    {
        return; // 带头节点的单链表,head指向的是头节点,head->next指向的是第一个有效节点
        // head->next->next指向的是第二个有效节点
    }

    // 使用快慢指针找到链表的中间节点(前半部分的最后一个)
    ListNode* slow = head->next;
    ListNode* fast = head->next;
    // while (fast && fast->next)会让slow指向后半部分的第一个结点(对于偶数个结点)
    // 或中间节点(对于奇数个结点),而不是前半部分的最后一个结点,会导致后续反转的链表段错误
    // 还有可能形成环
    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;       // 慢指针每次走一步
        fast = fast->next->next; // 快指针每次走两步
    }
    // 此时slow指向前半部分的最后一个节点
    // 将后半部分链表反转
    ListNode* prev = NULL;
    ListNode* pcur = slow->next;
    ListNode* pnext = pcur->next;
    while (pcur)
    {
        pcur->next = prev;
        prev = pcur;
        pcur = pnext;
        if (pnext)
        {
            pnext = pnext->next;
        }
    }
    // 反转后,prev指向后半部分的新头节点(原最后一个节点)
    slow->next = NULL;
    // 交替合并前半部分和反转后的后半部分
    ListNode* p = head->next; // 前半部分当前节点
    ListNode* q = prev;       // 后半部分当前节点
    ListNode* cur = head;     // 新链表的尾指针(从头节点开始)

    while (p != NULL && q != NULL)
    {
        // 先取一个前半部分节点
        cur->next = p;
        p = p->next;
        cur = cur->next;

        // 再取一个后半部分结点
        cur->next = q;
        q = q->next;
        cur = cur->next;
    }

    // 若前半部分还有剩余(即n为奇数时),直接接上
    if (p)
    {
        cur->next = p;
    }
    // 后半部分不可能有剩余,因为前半部分长度>=后半部分
}

// 辅助函数：创建链表
ListNode* createList(int arr[], int n)
{
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head->next = NULL;
    ListNode* tail = head;

    for (int i = 0; i < n; i++)
    {
        ListNode* node = (ListNode*)malloc(sizeof(ListNode));
        node->data = arr[i];
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return head;
}

// 辅助函数：打印链表
void printList(ListNode* head)
{
    ListNode* p = head->next;
    printf("[");
    while (p)
    {
        printf("%d", p->data);
        if (p->next)
            printf(", ");
        p = p->next;
    }
    printf("]\n");
}

// 辅助函数：释放链表
void freeList(ListNode* head)
{
    ListNode* p = head->next;
    while (p)
    {
        ListNode* temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
}

// 测试函数
void testCase(int arr[], int n, const char* desc)
{
    printf("\n测试: %s (n=%d)\n", desc, n);
    if (arr != NULL && n > 0)
    {
        printf("原始数组: [");
        for (int i = 0; i < n; i++)
        {
            printf("%d", arr[i]);
            if (i < n - 1)
                printf(", ");
        }
        printf("]\n");
    }
    else
    {
        printf("原始数组: []\n");
    }

    ListNode* head = createList(arr, n);
    printf("原始链表: ");
    printList(head);

    recoderList(head);
    printf("重排后: ");
    printList(head);

    freeList(head);
}

int main()
{
    // 测试用例
    int arr1[] = { 1, 2, 3, 4, 5, 6 };
    testCase(arr1, 6, "偶数个节点");

    int arr2[] = { 1, 2, 3, 4, 5 };
    testCase(arr2, 5, "奇数个节点");

    int arr3[] = { 1, 2 };
    testCase(arr3, 2, "2个节点");

    int arr4[] = { 1 };
    testCase(arr4, 1, "1个节点");

    // 零长度数组在C中不允许，使用NULL指针
    testCase(NULL, 0, "0个节点（只有头节点）");

    int arr6[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    testCase(arr6, 8, "8个节点");

    return 0;
}