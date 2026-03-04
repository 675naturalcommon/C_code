#include "SList.h"

//void SListTest01()
//{
//	// 链表是由一个个节点组成
//	// 创建几个节点
//	SLTNode *node1 = (SLTNode *)malloc(sizeof(SLTNode));
//	node1->data = 1;
//
//	SLTNode *node2 = (SLTNode *)malloc(sizeof(SLTNode));
//	node2->data = 2;
//
//	SLTNode *node3 = (SLTNode *)malloc(sizeof(SLTNode));
//	node3->data = 3;
//
//	SLTNode *node4 = (SLTNode *)malloc(sizeof(SLTNode));
//	node4->data = 4;
//
//	SLTNode *node5 = (SLTNode *)malloc(sizeof(SLTNode));
//	node5->data = 5;
//
//	// 将四个链表连接起来
//	node1->next = node2;
//	node2->next = node3;
//	node3->next = node4;
//	node4->next = node5;
//	node5->next = NULL;
//
//	// 调用打印函数
//	SLTNode *plist = node1;
//	SLTPrint(plist);
//}

void SListTest02()
{
	SLTNode* plist;
	SLTPushBack(&plist, 1);
	SLTPrint(plist);
}

int main()
{
	// SListTest01();
	SListTest02();
	return 0;
}
