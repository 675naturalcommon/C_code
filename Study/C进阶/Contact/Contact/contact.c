#define _CRT_SECURE_NO_WARNINGS

#include "contact.h"

void InitContact(Contact *pContact)
{
    assert(pContact != NULL);
    pContact->count = 0;
    memset(pContact->data, 0, sizeof(pContact->data));
}

void AddContact(Contact *pContact)
{
    assert(pContact != NULL);
    if (pContact->count >= MAX)
    {
        printf("通讯录已满！\n");
        return;
    }
    //
    // 输入姓名、年龄、性别、电话、地址
    //
    printf("请输入姓名：");
    scanf("%s", pContact->data[pContact->count].name); // 这里不取地址是因为name是数组
    printf("请输入年龄：");
    scanf("%d", &pContact->data[pContact->count].age); // age是整型变量,要取地址
    printf("请输入性别：");
    scanf("%s", &pContact->data[pContact->count].gender);
    printf("请输入电话：");
    scanf("%s", pContact->data[pContact->count].phone);
    printf("请输入地址：");
    scanf("%s", pContact->data[pContact->count].address);

    pContact->count++;
    printf("添加成功！\n");
}

void DisplayContact(const Contact *pContact)
{
    assert(pContact != NULL);
    int i = 0;
    for (i = 0; i < pContact->count; i++)
    {
        printf("姓名：%s, 年龄：%d, 性别：%s, 电话：%s, 地址：%s\n",
               pContact->data[i].name,
               pContact->data[i].age,
               pContact->data[i].gender,
               pContact->data[i].phone,
               pContact->data[i].address);
    }
}

static int SearchByName(const Contact *pContact, const char *name)
{
    assert(pContact);
    assert(name);
    int i = 0;
    for (i = 0; i < pContact->count; i++)
    {
        if (strcmp(pContact->data[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void DeleteContact(Contact *pContact)
{
    assert(pContact != NULL);
    int i = 0;
    if (pContact->count == 0)
    {
        printf("通讯录为空！\n");
        return;
    }
    printf("请输入要删除的联系人姓名：");
    scanf("%s", pContact->data[i].name); // 这里不取地址是因为name是数组

    // 删除

    // 1.查找
    int index = SearchByName(pContact, pContact->data[i].name);
    if (index == -1)
    {
        printf("联系人不存在！\n");
        return;
    }
    // 2.删除
    for (i = index; i < pContact->count - 1; i++)
    {
        pContact->data[i] = pContact->data[i + 1];
    }
    pContact->count--;
    printf("删除成功！\n");
}

void SearchContact(Contact *pContact)
{
    assert(pContact);
    char name[20] = {0};
    if (pContact->count == 0)
    {
        printf("通讯录为空！\n");
        return;
    }
    printf("请输入要查找的联系人姓名：");
    scanf("%s", name);
    int index = SearchByName(pContact, name);
    if (index == -1)
    {
        printf("联系人不存在！\n");
        return;
    }
    else
    {
        printf("姓名：%s, 年龄：%d, 性别：%s, 电话：%s, 地址：%s\n",
               pContact->data[index].name,
               pContact->data[index].age,
               pContact->data[index].gender,
               pContact->data[index].phone,
               pContact->data[index].address);
    }
}

void ModifyContact(Contact *pContact)
{
    assert(pContact);
    char name[20] = {0};
    if (pContact->count == 0)
    {
        printf("通讯录为空！\n");
        return;
    }
    printf("请输入要修改的联系人姓名：");
    scanf("%s", name);
    int index = SearchByName(pContact, name);
    if (index == -1)
    {
        printf("联系人不存在！\n");
        return;
    }
    printf("请输入姓名：");
    scanf("%s", pContact->data[index].name); // 这里不取地址是因为name是数组
    printf("请输入年龄：");
    scanf("%d", &pContact->data[index].age); // age是整型变量,要取地址
    printf("请输入性别：");
    scanf("%s", &pContact->data[index].gender);
    printf("请输入电话：");
    scanf("%s", pContact->data[index].phone);
    printf("请输入地址：");
    scanf("%s", pContact->data[index].address);
}

static int cmp_age(const void *a, const void *b)
{
    return strcmp(((PeoInfo *)a)->name, ((PeoInfo *)b)->name);
}

void SortContactByName(Contact *pContact)
{
    assert(pContact);
    qsort(pContact->data, pContact->count, sizeof(PeoInfo), cmp_name);
    printf("通讯录按姓名排序成功！\n");
}
