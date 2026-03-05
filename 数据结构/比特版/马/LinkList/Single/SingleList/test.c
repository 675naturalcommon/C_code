#include "SList.h"

// void SListTest01()
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
// }

void SListTest02()
{
	// plist为指针,指向SLTNode类型的指针,指针要对其初始化,防止为野指针
	SLTNode *plist = NULL;

	// 尾插
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);
	SLTPushBack(&plist, 5);
	SLTPrint(plist);

	// 查找
	SLTNode *ret = SLTFind(plist, 1);
	SLTInsert(&plist, ret, 6);
	SLTPrint(plist);

	/*if (ret == NULL)
	{
		printf("没有找到\n");
	}
	else
	{
		printf("找到了\n");
	}*/

	// 头插
	/*SLTPushFront(&plist, 6);
	SLTPrint(plist);
	SLTPushFront(&plist, 7);
	SLTPrint(plist);
	SLTPushFront(&plist, 8);
	SLTPrint(plist);*/

	// 尾删
	/*SLTPopBack(&plist);
	SLTPrint(plist);

	SLTPopBack(&plist);
	SLTPrint(plist);

	SLTPopBack(&plist);
	SLTPrint(plist);

	SLTPopBack(&plist);
	SLTPrint(plist);

	SLTPopBack(&plist);
	SLTPrint(plist);

	SLTPopBack(&plist);
	SLTPrint(plist);*/

	// 头删
	/*SLTPopFront(&plist);
	SLTPrint(plist);

	SLTPopFront(&plist);
	SLTPrint(plist);

	SLTPopFront(&plist);
	SLTPrint(plist);

	SLTPopFront(&plist);
	SLTPrint(plist);

	SLTPopFront(&plist);
	SLTPrint(plist);*/
}

void SListTest03()
{
	// 测试SLTInsertAfter函数
	SLTNode *plist = NULL;

	// printf("测试SLTInsertAfter函数:\n");

	// 创建链表: 1->2->3->4->5
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);
	SLTPushBack(&plist, 5);
	printf("原始链表: ");
	SLTPrint(plist);

	SListDesTroy(&plist);
	SLTPrint(plist);

	// SLTNode* ret = SLTFind(plist, 1);

	// //删除pos节点
	// SLTErase(&plist, ret);
	// SLTPrint(plist);

	// //删除pos之后的节点
	// SLTEraseAfter(ret);
	// SLTPrint(plist);

	//// 在节点2之后插入6
	// SLTNode *pos2 = SLTFind(plist, 2);
	// if (pos2 != NULL)
	//{
	//	SLTInsertAfter(pos2, 6);
	//	printf("在节点2之后插入6: ");
	//	SLTPrint(plist);
	// }

	//// 在节点5之后插入7（尾节点之后插入）
	// SLTNode *pos5 = SLTFind(plist, 5);
	// if (pos5 != NULL)
	//{
	//	SLTInsertAfter(pos5, 7);
	//	printf("在节点5之后插入7: ");
	//	SLTPrint(plist);
	// }

	//// 在节点1之后插入8（头节点之后插入）
	// SLTNode *pos1 = SLTFind(plist, 1);
	// if (pos1 != NULL)
	//{
	//	SLTInsertAfter(pos1, 8);
	//	printf("在节点1之后插入8: ");
	//	SLTPrint(plist);
	// }
}

int main()
{
	// SListTest01();
	// SListTest02();
	SListTest03();
	return 0;
}
