#include "SList.h"

void SLTPrint(SLTNode *phead)
{
	SLTNode *pcur = phead;
	while (pcur) // pcur!=NULL
	{
		printf("%d ", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}

SLTNode *SLTBuyNode(SLTDataType x)
{
	SLTNode *newnode = (SLTNode *)malloc(sizeof(SLTNode));
	if (newnode) // 判断节点是否申请成功
	{
		perror("malloc");
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

void SLTPushBack(SLTNode **phead, SLTDataType x)
{
	SLTNode *newnode = SLTBuyNode(x);
	// 空链表和非空链表两种情况
	// 空链表
	if (phead == NULL)
	{
		phead = newnode;
	}
	else
	{
		// 找现有链表节点的尾巴
		SLTNode *ptail = phead;
		while (ptail->next)
		{
			ptail = ptail->next;
		}
		// 此时ptail指向的是尾节点
		ptail->next = newnode;
	}
}

void SLTPushFront(SLTNode **phead, SLTDataType x)
{
}