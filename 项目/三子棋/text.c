#define _CRT_SECURE_NO_WARNINGS 1

#include"game.h"
#include <stdlib.h>
#include <time.h>

void menu()
{
	printf("********************\n");
	printf("********************\n");
	printf("***** 1. play  *****\n");
	printf("***** 0. exit  *****\n");
	printf("********************\n");
	printf("********************\n");
}
void game()
{
	//游戏代码
	char board[ROW][COL] = { 0 };
	char ret = ' ';
	//初始化棋盘
	InitBoard(board, ROW, COL);
	//打印棋盘
	PrintBoard(board, ROW, COL);
	//下棋
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		PrintBoard(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != ' ')
			break;

		//电脑下棋
		ComputerMove(board, ROW, COL);
		PrintBoard(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != ' ')
			break;
	}

	if (ret == 'X')
		printf("玩家获胜!\n");
	else if (ret == 'O')
		printf("电脑获胜!\n");
	else if (ret == 'Q')
		printf("平局!\n");
}
int main()
{
	int input = 0;
	srand((unsigned int)time(NULL)); // 初始化随机数种子
	do
	{
		menu();//菜单
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
			case 1:
				printf("游戏开始!\n");
				game();
				break;
			case 0:
				printf("退出游戏!\n");
				break;
		default:
			printf("选择错误，请重新选择!\n");
			break;
		}
	} while (input);
}
