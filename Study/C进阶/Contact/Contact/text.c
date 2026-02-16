#define _CRT_SECURE_NO_WARNINGS

#include "contact.h"

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	DISPLAY,
	SORT
};
void menu()
{
	printf("**********************************\n");
	printf("*****1.Add Contact 2.Delete ******\n");
	printf("*****3.Search Contact 4.Modify****\n");
	printf("*****5.Display Contacts 6.Sort****\n");
	printf("*****0.Exit                   ****\n");
	printf("**********************************\n");
}

int main()
{
	int choice = 0;

	Contact con; // 通讯录

	// 初始化通讯录
	InitContact(&con);

	do
	{
		menu();
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case ADD:
			AddContact(&con);
			break;
		case DEL:
			DeleteContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case DISPLAY:
			DisplayContact(&con);
			break;
		case SORT:
			SortContactByName(&con);
			break;
		case EXIT:
			printf("退出通讯录\n");
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	} while (choice);
	return 0;
}