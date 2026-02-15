#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// 结构体类型的定义

// 学生

// struct Stu
//{
//	//学生的相关属性
//	char name[20];
//	int age;
// };
//
// struct Stu
//{
//	//学生的相关属性
//	char name[20];
//	int age;
// }s1, s2;//s1和s2是struct Stu类型的变量,且是全局变量
//
////匿名结构体类型
////只能用1次
// struct
//{
//	int a;
//	float x;
// } s1;
//
// int main()
//{
//	struct Stu s3;  //局部变量
//	return 0;
// }

// 结构体内存对齐

// struct  S1
//{
//	char c1;
//	int i;
//	char c2;
// };
//
// struct  S2
//{
//	char c1;
//	char c2;
//	int i;
// };
//
// int main()
//{
//	printf("%d\n", sizeof(struct S1));//12
//	printf("%d\n", sizeof(struct S2));//8
//
//	return 0;
// }

// struct S
//{
//	int data[100];
//	int num;
// };
//
//
// void print1(struct S ss)
//{
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		printf("%d ", ss.data[i]);
//	}
//	printf("%d\n", ss.num);
// }
//
// void print2(const struct S* ss)
//{
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		printf("%d ", ss->data[i]);
//	}
//	printf("%d\n", ss->num);
// }
//
//
// int main()
//{
//	struct S s = { {1,2,3},100 };
//	print1(s);    //传值调用
//	print2(&s);   //传址调用
//	return 0;
// }

// struct A
// {
// 	int _a : 2;
// 	int _b : 5;
// 	int _c : 10;
// 	int _d : 20;
// };

// int main()
// {
// 	printf("%d", sizeof(struct A));
// 	return 0;
// }