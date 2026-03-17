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

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode dummy;
    ListNode* tail = &dummy;

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
