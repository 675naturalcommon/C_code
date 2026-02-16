#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>  //用来提供strcmp(),strchr()函数的原型
#include <stdbool.h>
char* s_gets(char* st, int n);


enum spectrum
{
	red,orange,yellow,green,blue,violet
};

const char* colors[] = { "red","orange","yellow","green","blue","violet" };

#define LEN 30

int main(void)
{
	char choice[LEN];
	enum spectrum color;
	bool color_is_found = false;

	puts("Enter a color (empty line to quit):");
	while (s_gets(choice, LEN) != NULL && choice[0] != '\0')
	{
		for (color = red; color <= violet; color++)
		{
			if (strcmp(choice, colors[color]) == 0)
			{
				color_is_found = true;
				break;
			}
		}
		if (color_is_found)
			switch (color)
			{
			case red:puts("Roses are red.");
				break;
			case orange:puts("Poppies are orange.");
				break;
			case yellow:puts("Sunflowers are yellow.");
				break;
			case green:puts("Grass is green.");
				break;
			case blue:puts("Bluebells are blue.");
				break;
			case violet:puts("Violets are violet.");
				break;
			}
		else
			printf("I don't know about the color %s.\n", choice);
		color_is_found = false;
		puts("Next color,please (empty line to quit):");
	}
	puts("Goolbye!");

	return 0;
}

char* s_gets(char* st, int n)
{
	char* ret_val;
	char* find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n'); //查找换行符
		if (find)				//如果地址不是NULL
			*find = '\0';       //在此处放置一个空字符
		else
			while (getchar() != '\n')
				continue;       //清理输入行
	}
	return ret_val;
}

//枚举 enum
//enum Day
//{
//	Mon,   //0
//	Tues,  //1
//	Wed,   //2
//	Thur,  //3
//	Fri,   //4
//	Sat,   //5
//	Sun    //6
//};


//enum Day
//{
//	//枚举常量
//	Mon = 1,    //1
//	Tues,		//2
//	Wed,		//3
//	Thur,		//4
//	Fri,		//5
//	Sat,		//6
//	Sun			//7
//};
//
//int main()
//{
//	printf("%d\n", Mon);
//	printf("%d\n", Tues);
//	printf("%d\n", Wed);
//	printf("%d\n", Thur);
//	printf("%d\n", Fri);
//	printf("%d\n", Sat);
//	printf("%d\n", Sun);
//
//	return 0;
//}