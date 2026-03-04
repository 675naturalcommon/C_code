#include "Contact.h"

// 菜单显示函数
void menu()
{
    printf("=================================\n");
    printf("===== 通讯录管理系统 =====\n");
    printf("=================================\n");
    printf("===== 1. 添加联系人 =====\n");
    printf("===== 2. 显示所有联系人 =====\n");
    printf("===== 3. 删除联系人 =====\n");
    printf("===== 4. 查找联系人 =====\n");
    printf("===== 5. 修改联系人 =====\n");
    printf("===== 6. 清空通讯录 =====\n");
    printf("===== 7. 按姓名排序 =====\n");
    printf("===== 0. 退出系统 =====\n");
    printf("=================================\n");
    printf("请选择操作：");
}

int main()
{
    Contact con; // 创建通讯录
    int input = 0;

    // 初始化通讯录
    ContactInit(&con);

    do
    {
        menu();
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            ContactAdd(&con); // 添加联系人
            break;
        case 2:
            ContactShow(&con); // 显示所有联系人
            break;
        case 3:
            ContactDelete(&con); // 删除联系人
            break;
        case 4:
            ContactSearch(&con); // 查找联系人
            break;
        case 5:
            ContactModify(&con); // 修改联系人
            break;
        case 6:
            ContactClear(&con); // 清空通讯录
            break;
        case 7:
            ContactSort(&con); // 按姓名排序
            break;
        case 0:
            printf("正在退出系统...\n");
            break;
        default:
            printf("输入错误，请重新输入！\n");
            break;
        }

        printf("\n");

    } while (input != 0);

    // 销毁通讯录，释放内存
    ContactDestroy(&con);

    printf("感谢使用通讯录管理系统！\n");
    return 0;
}
