#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define NAME_MAX 20
#define GENDER_MAX 10
#define TEL_MAX 20
#define ADDR_MAX 100

// 定义联系人数据的结构
typedef struct personInfo
{
    char name[NAME_MAX];
    char gender[GENDER_MAX];
    int age;
    char tel[TEL_MAX];
    char addr[ADDR_MAX];
} peoInfo;

// 通讯录结构（基于顺序表）
typedef struct Contact
{
    peoInfo *data; // 指向存放联系人数据的数组
    int size;      // 当前通讯录中有效联系人的个数
    int capacity;  // 当前通讯录的最大容量
} Contact;

// 函数声明
// 初始化通讯录
void ContactInit(Contact *pc);

// 销毁通讯录
void ContactDestroy(Contact *pc);

// 检查容量并扩容
void ContactCheckCapacity(Contact *pc);

// 添加联系人（尾插）
void ContactAdd(Contact *pc);

// 显示所有联系人
void ContactShow(const Contact *pc);

// 按姓名查找联系人（返回位置，未找到返回-1）
int ContactFindByName(const Contact *pc, const char *name);

// 删除联系人（按姓名）
void ContactDelete(Contact *pc);

// 查找联系人（按姓名）
void ContactSearch(const Contact *pc);

// 修改联系人信息（按姓名）
void ContactModify(Contact *pc);

// 清空通讯录
void ContactClear(Contact *pc);

// 按姓名排序
void ContactSort(Contact *pc);
