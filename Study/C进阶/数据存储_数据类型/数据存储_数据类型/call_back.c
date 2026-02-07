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



int cmp_int(const void* e1, const void* e2)
{
	return (*(int*)e1 - *(int*)e2);
}

void bubble_sort(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		int j = 0;
		int flag = 1;
		for (j = 0; j < sz - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;
			}
		}
		if (flag == 1)
		{
			break;
		}
	}
}

void text1()
{
	int arr[] = { 9,8,7,6,5,4,3,2,1,0 };
	int sz = sizeof(arr) / sizeof(arr[0]);

	//bubble_sort(arr, sz);

	qsort(arr, sz, sizeof(arr[0]), cmp_int);


	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

struct Stu
{
	char name[15];
	int age;
};

int cmp_stu_by_name(const void* e1, const void* e2)
{
	return strcmp(((struct Stu*)e1)->name, ((struct Stu*)e2)->name);
}

int cmp_stu_by_age(const void* e1, const void* e2)
{
	return ((struct Stu*)e1)->age - ((struct Stu*)e2)->age;
}


void text2()
{
	//测试使用qsort来排序结构数据
	struct Stu s[] = { {"zhangsan",15},{"lisi",16},{"wangwu",17} };
	int sz = sizeof(s) / sizeof(s[0]);
	qsort(s, sz, sizeof(s[0]), cmp_stu_by_name);
	qsort(s, sz, sizeof(s[0]), cmp_stu_by_age);
}

int main()
{
	//text1();
	text2();
	return 0;
}

//int main()
//{
//	int a = 10;
//	//char* p = &a; //会有警告,指针类型不匹配
//	void* p = &a;  //void*是无具体类型的指针,可以接受任意类型的地址
//	//void型指针不能解引用,也不能+-整数,因为void*是无具体类型的指针
//	//+-整数不知道+或-几个字节
//	return 0;
//}