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

struct ListNode
{
    int data;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
{
    ListNode dummy;
    ListNode *tail = &dummy;

    dummy.next = 0;
    while (l1 && l2)
    {
        if (l1->data <= l2->data)
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

    if (l1)
    {
        tail->next = l1;
    }
    else
    {
        tail->next = l2;
    }

    return dummy.next;
}

ListNode *MergetwoLists(ListNode *l1, ListNode *l2)
{
    ListNode dummy;          // 创建一个哑结点
    ListNode *tail = &dummy; // 创建一个指针tail,tail指向的是ListNode类型,存储的是dummy的地址
    dummy.next = 0;          // 0是空指针常量,会被编译器转换为空指针值,这里相当于dummy.next = NULL

    while (l1 && l2) // l1指针和l2指针都不为空的时候进入循环
    {
        if (l1->data < l2->data) // 链表l1第一个结点中的数据值小于l2第一个结点中的数据值,先插l1
        {
            tail.next = l1; // 哑结点指向第一个结点
            l1 = l1->next;  // l1指向下一个结点
        }
        else
        {
            tail.next = l2;
            l2 = l2->next;
        }
        tail = tail.next;
    }

    if (l1)
    {
        tail.next = l1;
    }
    else
    {
        tail.next = l2;
    }

    return dummy.next;
}

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    ListNode *l1 = list1;
    ListNode *l2 = list2;
    // 判断l1和l2是否为空
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;
    ListNode *newHead, *newTail;
    newHead = newTail = NULL;
    // 确定头节点
    if (l1->data <= l2->data)
    {
        newHead = newTail = l1;
        l1 = l1->next;
    }
    else
    {
        newHead = newTail = l2;
        l2 = l2->next;
    }
    while (l1 && l2)
    {
        if (l1->data <= l2->data)
        {
            newTail->next = l1;
            l1 = l1->next;
        }
        else
        {
            newTail->next = l2;
            l2 = l2->next;
        }
        newTail = newTail->next;
    }
    // 接入剩余的部分
    if (l1)
        newTail->next = l1;
    if (l2)
        newTail->next = l2;

    return newHead;
    // while (l1 && l2)
    // {
    //     if (l1->data <= l2->data)
    //     {
    //         if (newHead == NULL && newTail == NULL)
    //         {
    //             newHead = newTail = l1;
    //         }
    //         else
    //         {
    //             newTail->next = l1;
    //             l1 = l1->next;
    //         }
    //     }
    //     else
    //     {
    //         if (newHead == NULL && newTail == NULL)
    //         {
    //             newHead = newTail = l2;
    //         }
    //         else
    //         {
    //             newTail->next = l2;
    //             l2 = l2->next;
    //         }
    //     }
    //     newTail = newTail->next;
    // }
    return newHead;
}