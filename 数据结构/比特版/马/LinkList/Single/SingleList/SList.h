#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 定义节点的结构
// 数据+指向下一个节点的指针

typedef int SLTDataType;

struct SListNode
{
	SLTDataType data;
	struct SListNode *next;
};

typedef struct SListNode SLTNode;

void SLTPrint(SLTNode *phead);

void SLTPushBack(SLTNode **phead, SLTDataType x);
void SLTPushFront(SLTNode **phead, SLTDataType x);