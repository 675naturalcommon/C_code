#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

//结构体类型的定义

//学生

//struct Stu
//{
//	//学生的相关属性
//	char name[20];
//	int age;
//};
//
//struct Stu
//{
//	//学生的相关属性
//	char name[20];
//	int age;
//}s1, s2;//s1和s2是struct Stu类型的变量,且是全局变量
//
////匿名结构体类型
////只能用1次
//struct
//{
//	int a;
//	float x;
//} s1;
//
//int main()
//{
//	struct Stu s3;  //局部变量
//	return 0;
//}


//结构体内存对齐

//struct  S1
//{
//	char c1;
//	int i;
//	char c2;
//};
//
//struct  S2
//{
//	char c1;
//	char c2;
//	int i;
//};
//
//int main()
//{
//	printf("%d\n", sizeof(struct S1));//12
//	printf("%d\n", sizeof(struct S2));//8
//
//	return 0;
//}




