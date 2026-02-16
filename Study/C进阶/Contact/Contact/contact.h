#pragma once

#include <string.h>
#include <stdio.h>
#include <assert.h>

#define MAX 100
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TEL 12
#define MAX_ADDR 30

// 类型的声明
//
// 人的信息
typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char gender[MAX_SEX];
	char phone[MAX_TEL];
	char address[MAX_ADDR];
} PeoInfo;

// 通讯录

typedef struct Contact
{
	PeoInfo data[MAX]; // 用来存放人的信息
	int count;		   // 记录当前通讯录中实际人的个数
} Contact;

// 初始化通讯录
void InitContact(Contact *pContact);

// 增加联系人通讯录
void AddContact(Contact *pContact);

// 显示联系人通讯录
void DisplayContact(const Contact *pContact);

// 删除联系人通讯录
void DeleteContact(Contact *pContact);

// 查找指定联系人
void SearchContact(Contact *pContact);

//  修改指定联系人
void ModifyContact(Contact *pContact);

// 排序通讯录
// 按照名字排序
void SortContactByName(Contact *pContact);

// 按照年龄排序
void SortContactByAge(Contact *pContact);
