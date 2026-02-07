#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

//int main()
//{
//	//数组指针
//	int arr1[10] = { 0 };
//	int (*p)[10] = &arr1;
//
//	//指针数组
//	int* arr[10];
//
//	return 0;
//}

//int test(const char* str)
//{
//	//printf("%s\n", str);
//	printf("test()\n");
//	return 0;
//}
//int main()
//{
//	//函数指针 --也是指针,是一种指向函数的指针
//	int (*pf)(const char* str) = test;
//	pf("abc");
//	(*pf)("abc");
//	return 0;
//}
//
//typedef void(* pf_t)(int);
//int main()
//{
//	(*(void(*)())0)();
//	//void(*)()是一个类型
//	//void表示没有返回值
//	//(*)表示是指针
//	//()表示函数没有参数,或参数列表为空
//	//所以void(*)()表示"指向无参数无返回值函数的指针"类型
//
//	//所以(void(*)())0表示将整数0强制转换为这种类型,相当于:我有一个指向地址0的函数指针
//	//*(void(*)())0获取地址0处的"函数"
//	//(*(void(*)())0)()最后一步就是函数调用
//	
//
//	void (*signal(int, void(*)(int)))(int);
//	pf_t(signal(int, pf_t));//和上面的声明是等价的
//	//void (  *signal( int,  void(*) (int)  )  )  (int);
//	//这是一个函数声明,首先是一个signal函数,有两个参数,第一个是int,第二个是函数指针类型void(*)(int)
//	//函数指针类型void(*)(int)是一个指向int参数,返回void的函数指针
//	//signal返回一个指向int参数,返回void的函数指针
//	//最外层的void(*)(int)--表示signal的返回值类型是void(*)(int),即返回一个指向void f(int)的函数指针
//
//	// * + 函数调用表达式表明这个函数返回一个指针
//	//最后外面部分void(*)(int)表明这个指针指向一个函数,这个函数返回的是void类型,参数是int
//	return 0;
//}


//函数指针的用途

//写一个计算器,实现加法,减法,乘法,除法
//
//void menu()
//{
//	printf("********************\n");
//	printf("****1.Add  2.Sub****\n");
//	printf("****3.Mul  4.Div****\n");
//	printf("****0.Exit     ****\n");
//	printf("********************\n");
//}
//
//int Add(int x, int y)
//{
//	return x + y;
//}
//
//int Sub(int x, int y)
//{
//	return x - y;
//}
//
//int Mul(int x, int y)
//{
//	return x * y;
//}
//
//int Div(int x, int y)
//{
//	return x / y;
//}
//
//void calc(int (*pf)(int x, int y))//此处的x,y可以给也可以不给
//{
//	int x = 0;
//	int y = 0;
//	printf("请输入计算数:");
//	scanf("%d %d", &x, &y);
//	int ret = 0;
//	ret = pf(x, y);
//	printf("%d\n", ret);
//}
//int main()
//{
//	int input = 0;
//	
//	do 
//	{
//		menu();
//		printf("请选择:->");
//		scanf("%d", &input);
//		switch (input)
//		{
//			case 1:
//				calc(Add);
//				break;
//			case 2:
//				calc(Sub);
//				break;
//			case 3:
//				calc(Mul);
//				break;
//			case 4:
//				calc(Div);
//				break;
//			case 0:
//				printf("已退出计算.\n");
//				break;
//			default:
//				printf("输入错误\n");
//				break;
//		}
//	} while (input);
//	return 0;
//}

//
//int Add(int x, int y)
//{
//	return x + y;
//}
//
//int Sub(int x, int y)
//{
//	return x - y;
//}
//
//int Mul(int x, int y)
//{
//	return x * y;
//}
//
//int Div(int x, int y)
//{
//	return x / y;
//}
//
//int main()
//{
//	int (*pf) (int, int) = Add;  //pf是函数指针
//	int (*arr[4])(int ,int) = {Add, Sub, Mul, Div};//函数指针数组
//	//数组每个元素都是一个函数指针,指向一个有两个int参数,返回int的函数,去掉arr[4]就是函数指针类型
//	//int (*)(int, int)就是函数指针类型
//
//	int i = 0;
//	for (i = 0; i < 4; i++)
//	{
//		int ret = arr[i](20, 10);//通过函数指针数组调用函数
//		printf("%d\n", ret);
//	}
//	return 0;
//}


void menu()
{
	printf("********************\n");
	printf("****1.Add  2.Sub****\n");
	printf("****3.Mul  4.Div****\n");
	printf("****0.Exit     ****\n");
	printf("********************\n");
}

int Add(int x, int y)
{
	return x + y;
}

int Sub(int x, int y)
{
	return x - y;
}

int Mul(int x, int y)
{
	return x * y;
}

int Div(int x, int y)
{
	return x / y;
}



int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int ret = 0;

	int (*pfArr[5])(int, int) = { NULL, Add, Sub, Mul, Div };//函数指针数组,0位置不使用

	

	do 
	{
		menu();
		printf("请选择:->");
		scanf("%d", &input);

		if (input == 0)
		{
			printf("退出计算器\n");
		}
		else if (input >= 1 && input <= 4)
		{
			printf("请输入两个操作数:");
			scanf("%d %d", &x, &y);
			ret = pfArr[input](x, y);
			printf("%d\n", ret);
		}
		else
		{
			printf("输入错误\n");
		}
	} while (input);
	return 0;
}

