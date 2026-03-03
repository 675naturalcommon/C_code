#include "Contact.h"
#include <stdio.h>
#include <string.h>

// 手动测试函数
void test_contact_system()
{
    printf("=== 开始测试通讯录系统（顺序表实现） ===\n\n");

    Contact con;

    // 测试1: 初始化通讯录
    printf("测试1: 初始化通讯录\n");
    ContactInit(&con);
    printf("初始化成功！size=%d, capacity=%d\n\n", con.size, con.capacity);

    // 测试2: 添加联系人
    printf("测试2: 添加联系人\n");
    printf("添加联系人1: 张三\n");
    // 手动添加联系人（模拟ContactAdd函数）
    ContactCheckCapacity(&con);
    strcpy(con.data[con.size].name, "张三");
    strcpy(con.data[con.size].gender, "男");
    con.data[con.size].age = 25;
    strcpy(con.data[con.size].tel, "13800138000");
    strcpy(con.data[con.size].addr, "北京市朝阳区");
    con.size++;

    printf("添加联系人2: 李四\n");
    ContactCheckCapacity(&con);
    strcpy(con.data[con.size].name, "李四");
    strcpy(con.data[con.size].gender, "女");
    con.data[con.size].age = 30;
    strcpy(con.data[con.size].tel, "13900139000");
    strcpy(con.data[con.size].addr, "上海市浦东新区");
    con.size++;

    printf("当前联系人数量: %d\n\n", con.size);

    // 测试3: 显示所有联系人
    printf("测试3: 显示所有联系人\n");
    ContactShow(&con);
    printf("\n");

    // 测试4: 查找联系人
    printf("测试4: 查找联系人\n");
    printf("查找'张三':\n");
    int pos = ContactFindByName(&con, "张三");
    if (pos != -1)
    {
        printf("找到联系人: %s, 电话: %s\n", con.data[pos].name, con.data[pos].tel);
    }
    else
    {
        printf("未找到联系人\n");
    }
    printf("\n");

    // 测试5: 修改联系人
    printf("测试5: 修改联系人\n");
    printf("修改'李四'的电话为'13999999999'\n");
    pos = ContactFindByName(&con, "李四");
    if (pos != -1)
    {
        strcpy(con.data[pos].tel, "13999999999");
        printf("修改成功！\n");
    }
    printf("\n");

    // 测试6: 显示修改后的联系人
    printf("测试6: 显示修改后的联系人\n");
    ContactShow(&con);
    printf("\n");

    // 测试7: 排序联系人
    printf("测试7: 排序联系人\n");
    // 添加第三个联系人用于测试排序
    ContactCheckCapacity(&con);
    strcpy(con.data[con.size].name, "王五");
    strcpy(con.data[con.size].gender, "男");
    con.data[con.size].age = 28;
    strcpy(con.data[con.size].tel, "13700137000");
    strcpy(con.data[con.size].addr, "广州市天河区");
    con.size++;

    printf("排序前:\n");
    ContactShow(&con);
    printf("\n");

    // 调用排序函数
    ContactSort(&con);

    printf("排序后:\n");
    ContactShow(&con);
    printf("\n");

    // 测试8: 删除联系人
    printf("测试8: 删除联系人\n");
    printf("删除'张三'\n");
    // 模拟删除操作
    pos = ContactFindByName(&con, "张三");
    if (pos != -1)
    {
        for (int i = pos; i < con.size - 1; i++)
        {
            con.data[i] = con.data[i + 1];
        }
        con.size--;
        printf("删除成功！\n");
    }

    printf("删除后联系人数量: %d\n", con.size);
    ContactShow(&con);
    printf("\n");

    // 测试9: 清空通讯录
    printf("测试9: 清空通讯录\n");
    ContactClear(&con);
    printf("清空后联系人数量: %d\n", con.size);

    // 测试10: 销毁通讯录
    printf("测试10: 销毁通讯录\n");
    ContactDestroy(&con);

    printf("\n=== 所有测试完成 ===\n");
}

int main()
{
    test_contact_system();
    return 0;
}