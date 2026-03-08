// 用单链表保存 n 个整数,结点的结构为[data][next],且|data|≤n(n 为正整数)
// 现要求设计一个时间复杂度尽可能高效的算法,对于链表中data的绝对值相等的节点
// 仅保留第一次出现的节点而删除其余绝对值相等的结点
// 例如单链表为
// head -> 21 -> -15 -> -15 -> -7 -> 15 -> NULL
// 删除节点后变为
// head -> 21 -> -15 -> -7 -> NULL

// 要求：
// 1）给出算法的基本设计思想.
// 2）使用C或C ++语言,给出单链表节点的数据类型定义.
// 3）根据设计思想,采用C或C ++语言描述算法,关键之处给出注释.
// 4）说明你所设计算法的时间复杂度和空间复杂度.

// 1.算法基本设计思想
// 由于链表中的每个整数∣data∣≤n,𝑛为链表长度
// 所有节点的绝对值均在0∼n 范围内.为了以最高效率删除绝对值重复的节点,可以采用空间换时间的方法：
// 首先遍历链表一次,统计节点个数n
// 动态分配一个大小为n+1的布尔数组flag,初始化为false,用于标记每个绝对值是否已出现过
// 再次遍历链表,对于每个节点,计算其data的绝对值absVal:
// 若flag[absVal]为false,说明该绝对值首次出现,将其置为true,并保留该节点
// 若flag[absVal]为true,说明该绝对值已出现过,则删除当前节点
// 最后释放辅助数组空间

// 该方法需两次线性扫描,时间复杂度为O(n),空间复杂度为O(n)

typedef struct ListNode
{
    int data;
    struct ListNode *next;
} ListNode;

void removeDuplicates(ListNode *head)
{
    if (head == NULL || head->next == NULL || head->next->next == NULL)
    {
        return; // 空链表或只有一个节点,无需处理
    }

    // 统计链表节点个数
    int n = 0;
    ListNode *dum = head->next;
    while (dum)
    {
        n++;
        dum = dum->next;
    }

    // 分配辅助数组
    // |data|<=n,所以取值的数目为n+1个,0~n
    int *flag = (ListNode *)calloc(n + 1, sizeof(int));
    if (falg == NULL) // 判断是否分配成功
    {
        perror("calloc\n");
        return;
    }

    // 遍历并删除重复节点
    ListNode *prev = head;       // 前驱指针(始终指向当前保留节点的前一个)
    ListNode *curr = head->next; // 当前检查的节点

    while (curr)
    {
        int absVal = abs(curr->data); // abs的功能是对数据取绝对值
        if (absVal <= n && flag[absVal] == 1)
        {
            // 绝对值已出现过,删除curr
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
        else
        {
            // 首次出现,标记并保留
            if (absVal <= n)
            {
                flag[absVal] = 1;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    free(flag);
}