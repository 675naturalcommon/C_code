// 设线性表L = (a₁, a₂, a₃, …, aₙ₋₂, aₙ₋₁, aₙ)采用带头节点的单链表保存,链表中的节点定义如下:
typedef struct node
{
    int data;
    struct node *next;
} ListNode;
// 请设计一个空间复杂度为O(1)且时间上尽可能高效的算法,重新排列L中的各节点
// 得到线性表 L’ = (a₁, aₙ, a₂, aₙ₋₁, a₃, aₙ₋₂, …)
// 要求：
// 1）给出算法的基本设计思想。
// 2）根据设计思想，采用 C 或 C++ 语言描述算法，关键之处给出注释。
// 3）说明你所设计算法的时间复杂度。

void recoderList(ListNode *head)
{
    if (head == NULL || head->next == NULL || head->next->next == NULL)
    {
        return; // 带头节点的单链表,head指向的是头节点,head->next指向的是第一个有效节点
                // head->next->next指向的是第二个有效节点
    }

    // 使用快慢指针找到链表的中间节点(前半部分的最后一个)
    ListNode *slow = head->next;
    ListNode *fast = head->next;
    // while (fast && fast->next)会让slow指向后半部分的第一个结点(对于偶数个结点)
    // 或中间节点(对于奇数个结点),而不是前半部分的最后一个结点,会导致后续反转的链表段错误
    // 还有可能形成环
    while (fast && fast->next->next)
    {
        slow = slow->next;       // 慢指针每次走一步
        fast = fast->next->next; // 快指针每次走两步
    }
    // 此时slow指向前半部分的最后一个节点
    // 将后半部分链表反转
    ListNode *prev = NULL;
    ListNode *pcur = slow->next;
    ListNode *pnext = pcur->next;
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

    // 交替合并前半部分和反转后的后半部分
    ListNode *p = head->next; // 前半部分当前节点
    ListNode *q = prev;       // 后半部分当前节点
    ListNode *cur = head;     // 新链表的尾指针(从头节点开始)

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