// 假定采用带头节点的单链表保存单词，当两个单词有相同的后缀时，则可共享相同的后缀存储空间，
// 例如，“loading”和“being”的存储映像中ing享有共同的存储空间
// 设str1和str2分别指向两个单词所在单链表的头节点，链表结点结构为
// 请设计一个时间上尽可能高效的算法，找出由str1和str2所指向两个链表共同后缀的起始位置
// 要求：
// 1)描述算法的基本设计思想
// 2)根据设计思想,关键之处给出注释
// 3)说明你所设计算法的时间复杂度

// 算法基本设计思想
// 分别遍历两个带头节点的单链表,求出它们的长度--数据结点个数
// 计算长度差,让较长的链表先移动长度差步,使得两个链表剩余部分长度相等
// 然后同时遍历两个链表,比较当前结点是否相同,即地址相同,第一个相同的结点即为共同后缀的起始位置
// 若遍历完仍未找到相同结点,则说明没有共同后缀,返回NULL

typedef struct ListNode
{
    int data;
    struct ListNode *next;
} ListNode;

// 计算链表长度(不包括头节点)
int getlength(ListNode *L)
{
    int length = 0;
    ListNode *phead = L->next;
    while (phead)
    {
        length++;
        phead = phead->next;
    }
    return length;
}

// 寻找两个链表的共同后缀起始节点
ListNode *findCommonSuffix(ListNode *str1, ListNode *str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return NULL;
    }
    int len1 = getlength(str1);
    int len2 = getlength(str2);

    ListNode *p = str1->next; // 指向第一个数据节点
    ListNode *q = str2->next;

    int diff = len1 - len2;
    if (diff > 0) // 说明str1链表的长度大于str2链表的长度
    {
        while (diff--)
        {
            p = p->next;
        }
    }
    else // 说明str2链表的长度大于str1的链表长度
    {
        diff = -diff;
        while (diff--)
        {
            q = q->next;
        }
    }
    // 同步向后遍历,直到找到相同节点或到达末尾
    while (p && q && p != q)
    {
        p = p->next;
        q = q->next;
    }

    return p; // 若找到则返回该节点,否则返回NULL
}

// 时间复杂度
// 计算长度需遍历两个链表,时间复杂度为O(len1+len2)
// 对齐和同步遍历最多再走较长链表的剩余部分,总体仍为 O(len1 + len2).
// 算法只需常数个辅助变量,空间复杂度为 O(1).