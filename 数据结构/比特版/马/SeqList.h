#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// 定义顺序表的结构

#define N 100

// 静态顺序表
// struct Seqlist
// {
//     int arr[N];
//     int length; // 顺序表长度,其中存储的是有效数据
// };

typedef int ElemType;
// 动态顺序表
typedef struct Seqlist
{
    ElemType *arr; // 动态数组
    int length;    // 有效数据个数
    int capacity;  // 空间大小
} SL;

// typedef struct Seqlist Seqlist;

// 顺序表初始化
void InitList(SL *L);

// 顺序表销毁
void DestroyList(SL *L);

// 尾插
void InsertTail(SL *L, ElemType e);

// 头插
void InsertHead(SL *L, ElemType e);

// 打印数据
void SLprint(SL L);

// 删除尾部数据
void DeleteTail(SL *L);

// 删除头部数据
void DeleteHead(SL *L);

// 在指定位置插入数据
void InsertPos(SL *L, int pos, ElemType e);

// 在指定位置删除数据
void DeletePos(SL *L, int pos);

// 顺序表的查找
// int SLFind(SL *L, ElemType e);
void SLFind(SL L, ElemType e);
