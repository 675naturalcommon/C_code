#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 已知带有一个表头结点的单链表,节点结构为data  link
// 假设该链表只给出了头指针list.在不改变链表的前提下,请设计一个尽可能高效的算法
// 查找链表中倒数第k个位置的节点(k为正整数).若查找成功,算法输出该节点的data域的值,并返回1;
// 否则,只返回0
// 要求:
// 描述算法的基本思想
// 描述算法的详细实现步骤
// 根据设计思想和实现步骤,采用程序设计语言描述算法,关键之处请给出简要注释

// 1.算法基本思想
// 采用双指针法,只需遍历链表一次.设置两个指针p个q,初始时都指向链表的第一个数据节点
// 即头节点的下一个节点.首先让指针p向前移动k步,如果在这个过程中p变为空,说明链表长度小于k
// 查找失败;否则,p和q之间相距k个节点.然后让p和q同时向后移动,直到p到达链表末尾(p为空)
// 此时q所指的节点恰好就是倒数第k个节点.输出该节点的data值并返回1;若链表长度小于k,则返回0
// 该方法只扫描链表一次,时间复杂度为o(n),时间复杂度为o(1),满足高效要求

// 2.算法的详细实现步骤
// 1.初始化
// 定义两个指针p和q,初试都指向第一个数据节点,即p=q = list->link
// 定义计数器i = 0,用于移动p移动的步数
// 2.让p先走k步
// 循环执行:当p!=NULL且i<k时,p=p->link,i++
// 循环结束后,检查i是否等于k
// 如果i<k,说明链表节点总数不足k,查找失败,返回0
// 3.同时移动p和q
// 此时p已经领先q共k步
// 继续循环:当p!=NULL时,指向p=p->link和q=q->link
// 循环结束时,p指向NULL,q指向倒数第k个节点
// 4.输出结果并返回
// 输出q->data的值
// 返回1表示查找成功

typedef struct Node
{
    int data;          // 数据域
    struct Node *link; // 指针域
} Node;

int findKthFromEnd(Node *list, int k)
{
    if (list == NULL || k <= 0) // 防御性检查
        return 0;

    Node *p = list->link; // p指向第一个数据节点
    Node *q = list->link; // q也指向第一个数据节点
    int i = 0;

    // 让p先走k步
    while (p != NULL && i < k)
    {
        p = p->link;
        i++;
    }
    // 从while循环里出来,如果i<k,说明链表长度小于k
    if (i < k)
        return 0;

    // p和q同步移动,直到p为空
    while (p != NULL)
    {
        p = p->link;
        q = q->link;
    }
    // 此时q指向倒数第k个节点
    printf("%d\n", q->data);
    return 1;
}

// 时间复杂度o(n),空间复杂度为o(1)