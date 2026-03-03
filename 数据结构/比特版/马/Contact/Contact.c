#include "Contact.h"

// 初始化通讯录
void ContactInit(Contact *pc)
{
    assert(pc);
    pc->data = NULL;
    pc->size = 0;
    pc->capacity = 0;
    printf("通讯录初始化成功！\n");
}

// 销毁通讯录
void ContactDestroy(Contact *pc)
{
    assert(pc);
    if (pc->data)
    {
        free(pc->data);
        pc->data = NULL;
    }
    pc->size = 0;
    pc->capacity = 0;
    printf("通讯录已销毁！\n");
}

// 检查容量并扩容
void ContactCheckCapacity(Contact *pc)
{
    assert(pc);
    if (pc->size == pc->capacity)
    {
        int newCapacity = pc->capacity == 0 ? 4 : pc->capacity * 2;
        peoInfo *newData = (peoInfo *)realloc(pc->data, newCapacity * sizeof(peoInfo));
        if (!newData)
        {
            perror("ContactCheckCapacity::realloc");
            return;
        }
        pc->data = newData;
        pc->capacity = newCapacity;
        printf("通讯录扩容成功，当前容量：%d\n", pc->capacity);
    }
}

// 添加联系人（尾插）
void ContactAdd(Contact *pc)
{
    assert(pc);

    // 检查容量
    ContactCheckCapacity(pc);

    printf("请输入姓名：");
    scanf("%s", pc->data[pc->size].name);
    printf("请输入性别：");
    scanf("%s", pc->data[pc->size].gender);
    printf("请输入年龄：");
    scanf("%d", &(pc->data[pc->size].age));
    printf("请输入电话：");
    scanf("%s", pc->data[pc->size].tel);
    printf("请输入地址：");
    scanf("%s", pc->data[pc->size].addr);

    pc->size++;
    printf("联系人添加成功！\n");
}

// 显示所有联系人
void ContactShow(const Contact *pc)
{
    assert(pc);

    if (pc->size == 0)
    {
        printf("通讯录为空！\n");
        return;
    }

    printf("%-10s\t%-8s\t%-4s\t%-12s\t%-20s\n", "姓名", "性别", "年龄", "电话", "地址");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < pc->size; i++)
    {
        printf("%-10s\t%-8s\t%-4d\t%-12s\t%-20s\n",
               pc->data[i].name,
               pc->data[i].gender,
               pc->data[i].age,
               pc->data[i].tel,
               pc->data[i].addr);
    }
}

// 按姓名查找联系人（返回位置，未找到返回-1）
int ContactFindByName(const Contact *pc, const char *name)
{
    assert(pc);
    assert(name);

    for (int i = 0; i < pc->size; i++)
    {
        if (strcmp(pc->data[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 删除联系人（按姓名）
void ContactDelete(Contact *pc)
{
    assert(pc);

    if (pc->size == 0)
    {
        printf("通讯录为空，无法删除！\n");
        return;
    }

    char name[NAME_MAX];
    printf("请输入要删除的联系人姓名：");
    scanf("%s", name);

    int pos = ContactFindByName(pc, name);
    if (pos == -1)
    {
        printf("未找到该联系人！\n");
        return;
    }

    // 将后面的数据前移（顺序表删除操作）
    for (int i = pos; i < pc->size - 1; i++)
    {
        pc->data[i] = pc->data[i + 1];
    }

    pc->size--;
    printf("联系人删除成功！\n");
}

// 查找联系人（按姓名）
void ContactSearch(const Contact *pc)
{
    assert(pc);

    if (pc->size == 0)
    {
        printf("通讯录为空，无法查找！\n");
        return;
    }

    char name[NAME_MAX];
    printf("请输入要查找的联系人姓名：");
    scanf("%s", name);

    int pos = ContactFindByName(pc, name);
    if (pos == -1)
    {
        printf("未找到该联系人！\n");
        return;
    }

    printf("找到联系人：\n");
    printf("%-10s\t%-8s\t%-4s\t%-12s\t%-20s\n", "姓名", "性别", "年龄", "电话", "地址");
    printf("----------------------------------------------------------------\n");
    printf("%-10s\t%-8s\t%-4d\t%-12s\t%-20s\n",
           pc->data[pos].name,
           pc->data[pos].gender,
           pc->data[pos].age,
           pc->data[pos].tel,
           pc->data[pos].addr);
}

// 修改联系人信息（按姓名）
void ContactModify(Contact *pc)
{
    assert(pc);

    if (pc->size == 0)
    {
        printf("通讯录为空，无法修改！\n");
        return;
    }

    char name[NAME_MAX];
    printf("请输入要修改的联系人姓名：");
    scanf("%s", name);

    int pos = ContactFindByName(pc, name);
    if (pos == -1)
    {
        printf("未找到该联系人！\n");
        return;
    }

    printf("找到联系人，请输入新信息：\n");
    printf("请输入姓名：");
    scanf("%s", pc->data[pos].name);
    printf("请输入性别：");
    scanf("%s", pc->data[pos].gender);
    printf("请输入年龄：");
    scanf("%d", &(pc->data[pos].age));
    printf("请输入电话：");
    scanf("%s", pc->data[pos].tel);
    printf("请输入地址：");
    scanf("%s", pc->data[pos].addr);

    printf("联系人信息修改成功！\n");
}

// 清空通讯录
void ContactClear(Contact *pc)
{
    assert(pc);
    pc->size = 0;
    printf("通讯录已清空！\n");
}

// 按姓名排序
void ContactSort(Contact *pc)
{
    assert(pc);

    if (pc->size <= 1)
    {
        printf("通讯录中联系人数量不足，无需排序！\n");
        return;
    }

    // 使用冒泡排序按姓名排序
    for (int i = 0; i < pc->size - 1; i++)
    {
        for (int j = 0; j < pc->size - 1 - i; j++)
        {
            if (strcmp(pc->data[j].name, pc->data[j + 1].name) > 0)
            {
                // 交换两个联系人
                peoInfo temp = pc->data[j];
                pc->data[j] = pc->data[j + 1];
                pc->data[j + 1] = temp;
            }
        }
    }

    printf("通讯录已按姓名排序！\n");
}