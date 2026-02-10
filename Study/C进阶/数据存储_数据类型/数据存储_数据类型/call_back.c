#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//
//qsort -- 这个函数可以排序任意类型的数据
//

//
//void qsort(void* base,   //你要排序的数据的起始位置
//	size_t num,          //待排序的数据元素的个数
//	size_t width,        //待排序的数据元素的大小(单位是字节)
//	int(*cmp)(const void* e1, const void* e2)//函数指针-比较函数
//);




//
//void bubble_sort(int arr[], int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		int j = 0;
//		int flag = 1;
//		for (j = 0; j < sz - 1 - i; j++)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				int tmp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = tmp;
//				flag = 0;
//			}
//		}
//		if (flag == 1)
//		{
//			break;
//		}
//	}
//}

//
//int cmp_int(const void* e1, const void* e2)
//{
//	return (*(int*)e1 - *(int*)e2);
//}
//
//
//void Swap(char*buf1,char *buf2,int width)
//{
//	int i = 0;
//	for (i = 0; i < width; i++)
//	{
//		char tmp = *buf1;
//		*buf1 = *buf2;
//		*buf2 = tmp;
//		buf1++;
//		buf2++;
//	}
//}
//
//
//
//void bubble_sort(void* base, int sz, int width, int (*cmp)(const void* e1, const void* e2))
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		int j = 0;
//		int flag = 1;
//		for (j = 0; j < sz - 1 - i; j++)
//		{
//			if (cmp((char*)base + j * width, (char*)base + (j + 1) * width) > 0)
//			{
//				//交换
//				Swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
//				flag = 0;
//			}
//		}
//		if (flag == 1)
//		{
//			break;
//		}
//	}
//}
//
//void text1()
//{
//	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	//bubble_sort(arr, sz);
//
//	qsort(arr, sz, sizeof(arr[0]), cmp_int);
//
//
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//}
//
//struct Stu
//{
//	char name[15];
//	int age;
//};
//
//int cmp_stu_by_name(const void* e1, const void* e2)
//{
//	return strcmp(((struct Stu*)e1)->name, ((struct Stu*)e2)->name);
//}
//
//int cmp_stu_by_age(const void* e1, const void* e2)
//{
//	return ((struct Stu*)e1)->age - ((struct Stu*)e2)->age;
//}
//
//
//void text2()
//{
//	//测试使用qsort来排序结构数据
//	struct Stu s[] = { {"zhangsan",15},{"lisi",16},{"wangwu",17} };
//	int sz = sizeof(s) / sizeof(s[0]);
//	qsort(s, sz, sizeof(s[0]), cmp_stu_by_name);
//	qsort(s, sz, sizeof(s[0]), cmp_stu_by_age);
//}
//
//void text3()
//{
//	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	//bubble_sort(arr, sz);
//
//	bubble_sort(arr, sz, sizeof(arr[0]), cmp_int);
//
//
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//}
//
//void text4()
//{
//	//测试使用qsort来排序结构数据
//	struct Stu s[] = { {"zhangsan",15},{"lisi",16},{"wangwu",17} };
//	int sz = sizeof(s) / sizeof(s[0]);
//	//qsort(s, sz, sizeof(s[0]), cmp_stu_by_name);
//	bubble_sort(s, sz, sizeof(s[0]), cmp_stu_by_age);
//}
//
//int main()
//{
//	//text1();
//	//text2();
//	//text3();
//	text4();
//	return 0;
//}

//int main()
//{
//	int a = 10;
//	//char* p = &a; //会有警告,指针类型不匹配
//	void* p = &a;  //void*是无具体类型的指针,可以接受任意类型的地址
//	//void型指针不能解引用,也不能+-整数,因为void*是无具体类型的指针
//	//+-整数不知道+或-几个字节
//	return 0;
//}


//下面的代码是通过deepseek生成,我重复一遍

//回调函数--通过函数指针调用的函数

//
////回调函数的类型定义
//typedef void (*CallbackFunc)(int);
//
////接受回调函数作为参数的函数
//void process_data(int value, CallbackFunc callback) //callback是参数(形参),类型是CallbackFunc
//{
//	printf("正在处理数据: %d\n", value);
//
//	//调用回调函数
//	if (callback != NULL)
//	{
//		callback(value * 2);//处理完后调用回调
//	}
//}
//
////实际的回调函数实现
//void my_callback(int result)
//{
//	printf("回调函数被调用,结果: %d\n", result);
//}
//
//int main()
//{
//	//将函数指针作为参数传递
//	process_data(10, my_callback);
//	return 0;
//}


//回调函数类型:比较两个整数
//typedef int(*CompareFunc)(int, int);
//
////使用回调函数进行排序
//void bubble_sort(int arr[], int n, CompareFunc compare)
//{
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n - 1 - i; j++)
//		{
//			//使用回调函数比较元素
//			if (compare(arr[j], arr[j + 1]) > 0)
//			{
//				int temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}
//}
//
//
////不同的比较函数实现
//
////升序排序
//int ascending(int a, int b)
//{
//	return a - b;  //>0 表示 a > b
//}
//
////降序排序
//int descending(int a, int b)
//{
//	return b - a; //>0 表示 a < b
//}
//
////按绝对值升序
//int absolute_ascending(int a, int b)
//{
//	int abs_a = a < 0 ? -a : a;
//	int abs_b = b < 0 ? -b : b;
//	return abs_a - abs_b;
//}
//
//int main()
//{
//	int numbers[] = { 5,-2,8,-1,3 };
//	int n = sizeof(numbers) / sizeof(numbers[0]);
//
//	printf("原始数组: ");
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d ", numbers[i]);
//	}
//
//	//使用不同的回调函数进行排序
//	bubble_sort(numbers, n, ascending);
//	printf("\n升序排序:");
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d ", numbers[i]);
//	}
//
//
//	bubble_sort(numbers, n, descending);
//	printf("\n降序排序:");
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d ", numbers[i]);
//	}
//
//	bubble_sort(numbers, n, absolute_ascending);
//	printf("\n绝对值排序:");
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d ", numbers[i]);
//	}
//	return 0;
//}