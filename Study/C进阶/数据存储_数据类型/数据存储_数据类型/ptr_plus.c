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

//int main()
//{
//	const char* p1 = "abcdef";
//	const char* p2 = "abcdef";
//
//	char arr1[] = "abcdef";
//	char arr2[] = "abcdef";
//
//	if (p1 == p2)
//		printf("p1==p2\n");
//	//如果const char* p1 = "abcdef";
//	    //const char* p2 = "abcde";   那么p1!=p2
//	else
//		printf("p1!=p2\n");
//
//	if (arr1 == arr2)
//		printf("arr1==arr2\n");
//	else
//		printf("arr1!=arr2\n");
//
//
//	return 0;
//}

//指针数组是数组,是用来存放指针的数组
//int arr[10]  //整型数组
//char ch[5] //字符数组

//int* parr[10] //指针数组,用来存放10个整形指针的数组
//char* pch[5] //指针数组,用来存放5个字符指针的数组

//int main()
//{
//	int arr1[] = { 1,2,3,4,5 };
//	int arr2[] = { 6,7,8,9,10 };
//	int arr3[] = { 11,12,13,14,15 };
//
//	//*(p+i) -> p[i]
//	int* parr[3] = { arr1,arr2,arr3 };//指针数组
//	int i = 0;
//	for (i = 0; i < 3; i++)
//	{
//		int j = 0;
//		for (j = 0; j < 5; j++)
//		{
//			//printf("%d ", *(parr[i] + j));
//			printf("%d ", parr[i][j]);
//
//		}
//		printf("\n");
//	}
//	return 0;
//}


//int main()
//{
//	int arr[10] = { 0 };
//	int* p = arr;
//	int (*p2)[10] = &arr;
//
//	//整形指针是用来存放整形的地址
//	//字符指针是用来存放字符的地址
//	//数组指针是用来存放数组的地址
//	// 
//	//printf("%p\n", arr);
//	//printf("%p\n", arr + 1);
//	//printf("\n");
//
//	//printf("%p\n", &arr[0]);
//	//printf("%p\n", &arr[0] + 1);
//	//printf("\n");
//
//	//printf("%p\n", &arr);
//	//printf("%p\n", &arr + 1);//跳过40个字节
//	//printf("\n");
//
//	//int sz = sizeof(arr);
//	//printf("%d\n", sz);
//	return 0;
//}

//数组名通常表示的都是数组首元素的地址,但是有两个例外
//1.sizeof(数组名),这里的数组名表示的是整个数组,计算的是整个数组的大小
//2.&数组名,这里的数组名表示的依然是整个数组,所以&数组名取出的是整个数组的地址

