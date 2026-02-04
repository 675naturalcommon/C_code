#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

//int main()
//{
//	/*char* ch = 'a';
//	char* p = &ch;
//	printf("%c\n", *p);
//	printf("%p\n", p);
//	printf("%c\n", ch);
//	*p = 'b';
//	printf("%c\n", *p);*/
//
//	const char* p = "abcdef";//把字符串首字符a的地址赋给了p
//	//加上const,限制*p的更改
//	//*p = 'w';  //常量字符串不允许被更改
//
//	printf("%s\n", p);//printf的功能,给%s告诉printf我要打印的是字符串,给字符串的起始地址就可以打印出来
//	//char arr[] = "abcdef";
//	//printf("%s\n", arr);
//
//	return 0;
//}

int main()
{
	const char* p1 = "abcdef";
	const char* p2 = "abcde";

	char arr1[] = "abcdef";
	char arr2[] = "abcdef";

	if (p1 == p2)
		printf("p1==p2\n");
	else
		printf("p1!=p2\n");

	if (arr1 == arr2)
		printf("arr1==arr2\n");
	else
		printf("arr1!=arr2\n");


	return 0;
}