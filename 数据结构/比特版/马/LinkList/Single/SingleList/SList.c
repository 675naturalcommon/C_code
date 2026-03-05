#include "SList.h"

void SLTPrint(SLTNode *phead)
{
	SLTNode *pcur = phead;
	while (pcur) // pcur!=NULL
	{
		printf("%d ", pcur->data);
		pcur = pcur->next;
	}
	printf("NULL\n");
}

SLTNode *SLTBuyNode(SLTDataType x)
{
	SLTNode *newnode = (SLTNode *)malloc(sizeof(SLTNode));
	if (newnode == NULL) // 判断节点是否申请成功
	{
		perror("malloc");
		exit(1);
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

// 尾插
void SLTPushBack(SLTNode **pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode *newnode = SLTBuyNode(x);
	// 空链表和非空链表两种情况
	// 空链表
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		// 找现有链表节点的尾巴
		SLTNode *ptail = *pphead;
		while (ptail->next)
		{
			ptail = ptail->next;
		}
		// 此时ptail指向的是尾节点
		ptail->next = newnode;
	}
}

// 头插
void SLTPushFront(SLTNode **pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode *newnode = SLTBuyNode(x);
	//*pphead指向的是结构体类型
	newnode->next = *pphead;
	*pphead = newnode;
}

// 尾删
void SLTPopBack(SLTNode **pphead)
{
	// 传过来的指针不能为空,结构体也不能为空
	assert(pphead && *pphead);
	// 只有一个节点的情况
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLTNode *prev = *pphead;
		SLTNode *ptail = *pphead;
		while (ptail->next)
		{
			prev = ptail;
			ptail = ptail->next;
		}
		free(ptail);
		ptail = NULL;
		prev->next = NULL;
	}
}

// 头删
void SLTPopFront(SLTNode **pphead)
{
	assert(pphead && *pphead);

	// 当只有一个节点的时候情况也成立,只有一个节点(*pphead)->next = NULL,即next为NULL
	// 那么此时*pphead = next;即为*pphead = NULL
	SLTNode *next = (*pphead)->next;
	free(*pphead);
	*pphead = next;
}

// 查找
SLTNode *SLTFind(SLTNode *list, SLTDataType x)
{
	assert(list);
	SLTNode *pcur = list;
	while (pcur)
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	// 没找到
	return NULL;
}

// 检查指定位置是否在链表中
void SLTCheck(SLTNode *phead, SLTNode *pos)
{
	assert(phead); // 添加头节点检查
	assert(pos);   // 添加位置检查

	SLTNode *cur = phead;
	while (cur != NULL && cur != pos)
	{
		cur = cur->next;
	}

	// 如果没找到，使用断言终止程序
	assert(cur != NULL && "Error: pos is not in the list");
}

// 在指定位置之前插入数据
// SLTNode *pos指向要插入位置的目标节点,新节点将插入在pos节点之前
// pos必须是一个有效的链表结点指针
void SLTInsert(SLTNode **pphead, SLTNode *pos, SLTDataType x)
{
	// 传入指针不能为空对pphead做判断,链表头指针也不能为空对*pphead做判断
	// *pphead为空的话:链表为空,无法在指定位置插入
	assert(pphead && *pphead);
	// pos为空,没有指定有效的插入位置
	// assert(pos);

	// 验证pos是否在链表中
	SLTCheck(*pphead, pos);
	// SLTNode *check = *pphead;
	// while (check != NULL && check != pos)
	// {
	// 	check = check->next;
	// }
	// if (check == NULL)
	// {
	// 	// pos不在链表中
	// 	fprintf(stderr, "Error: pos is not in the list\n");
	// 	return; // assert(0)也可以用来终止程序
	// }

	// 申请一个新节点用来存储x
	SLTNode *newnode = SLTBuyNode(x);
	// 如果pos == *pphead,说明是头插
	if (pos == *pphead)
	{
		SLTPushFront(pphead, x);
	}
	else
	{
		SLTNode *prev = *pphead;
		// 添加边界检查,确保pos一定在链表中
		// while(prev != NULL && prev->next != pos)
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		newnode->next = pos;
		prev->next = newnode;
	}
}

// 在指定位置之后插入数据
void SLTInsertAfter(SLTNode *pos, SLTDataType x)
{

	// 传入位置不能为空,否则没有有效的插入位置
	assert(pos);

	// 申请一个新节点用来存储x
	SLTNode *newnode = SLTBuyNode(x);

	// 在pos之后插入新节点
	newnode->next = pos->next;
	pos->next = newnode;
}

// 删除pos节点
void SLTErase(SLTNode **pphead, SLTNode *pos)
{
	// 传入指针不能为空,传入链表不能为空
	assert(pphead && *pphead);
	// 传入位置不能为空
	assert(pos);
	// 检查pos是否在链表中
	// SLTCheck(*pphead, pos);

	// 删除pos节点
	if (pos == *pphead) // pos是头节点
	{
		SLTPopFront(pphead);
	}
	else
	{
		SLTNode *prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}

		prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

// 删除pos之后的节点
void SLTEraseAfter(SLTNode *pos)
{
	assert(pos && pos->next);
	SLTNode *del = pos->next;
	pos->next = del->next;
	free(del);
	del = NULL;
}

// 销毁链表 -- 一个个销毁
void SListDesTroy(SLTNode **pphead)
{
	assert(pphead && *pphead);
	SLTNode *pcur = *pphead;
	while (pcur)
	{
		SLTNode *next = pcur->next;
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}