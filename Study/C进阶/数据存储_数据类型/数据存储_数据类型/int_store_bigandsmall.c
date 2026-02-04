#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

//int main()
//{
//	int i = 0;
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	                       // Debug       Release
//	printf("%p\n", arr);  //005DF73C     00B3F954
//	printf("%p\n", &i);   //005DF76C     00B3F950
//	
//	
//	/*for (i = 0; i < 12; i++)
//	{
//		arr[i] = 0;
//		printf("hehe\n");
//	}*/
//	return 0;
//}


//int is_little_endian()
//{
//	int num = 1;
//	// 1在内存中存储的形式：01 00 00 00（小端） 00 00 00 01（大端）
//	//如果最低地址存放的是1,则是小端序
//	//如果最低地址存放的是0,则是大端序
//	return *(char*)&num == 1;
//}
//
//int main()
//{
//	if (is_little_endian())
//	{
//		printf("小端序\n");
//	}
//	else
//	{
//		printf("大端序\n");
//	}
//	return 0;
//}


//int main()
//{
//	char a = -1;
//	signed char b = -1;
//	unsigned char c = -1;
//	printf("%d %d %d\n", a, b, c);
//	return 0;
//}

//int main()
//{
//	//10000000
//	//10000000000000000000000010000000
//	//11111111111111111111111101111111
//	//11111111111111111111111110000000
//	//10000000    -- a
//	//11111111111111111111111110000000
//	char a = -128;
//	printf("%u\n", a);
//
//	//在大多数系统中,char默认是有符号的(signed char),范围是-128~127
//	//-128在内存中以补码形式存储:对于8位有符号char,-128的二进制补码是10000000
//	//%u期望一个unsigned int类型的参数,但传入的是char类型,在可变参数函数中,printf就是,char会进行整型提升int
//	//a是有符号的char,值为-128,提升为int时进行符号扩展:-128(int)补码时)0xFFFFFF80
//	//%u将0xFFFFFF80解释为无符号整数
//
//	printf("%d\n", a);
//
//	//11111111111111111111111110000000
//	//10000000000000000000000001111111
//	//10000000000000000000000010000000
//	return 0;
//}

//int main()
//{
//	char a = 128;
//	//a的二进制原码形式是10000000
//	//11111111111111111111111110000000
//	printf("%u\n", a);
//
//	printf("%d\n", a);
//	//11111111111111111111111110000000
//	//10000000000000000000000001111111
//	//10000000000000000000000010000000
//	return 0;
//}


//int main()
//{
//	int i = -20;          //100000000000000000000000 00010100
//	                      //111111111111111111111111 11101011
//	                      //111111111111111111111111 11101100
//	unsigned int j = 10;  //000000000000000000000000 00001010
//	
//	printf("%d", i + j);  //111111111111111111111111 11110110
//	                      //100000000000000000000000 00001001
//	                      //100000000000000000000000 00001010
//	return 0;
//}

//int main()
//{
//	unsigned int i;
//	for (i = 9; i >= 0; i--)
//	{
//		printf("%u\n", i);
//	}
//
//	//会陷入死循环中,原因是打印 9 8 7 6 5 4 3 2 1 0之后,i--  i变为-1
//	//-1的原码是10000000 00000000 00000000 00000001
//	//    反码  11111111 11111111 11111111 11111110
//	//    补码  11111111 11111111 11111111 11111111   --  4294967295 十进制
//	//但由于我们的i是无符号整形unsigned int,所以它会把-1的补码理解为全1的整数
//	return 0;
//}

#include<string.h>


//int main()
//{
//	//char a[1000]; //char类型-128~127
//	//int i;
//
//	//for (i = 0; i < 1000; i++)
//	//{
//	//	a[i] = -1 - i;
//	//}
//	////a[i]中的存放的值是-1~-128,127~0,循环放
//	////strlen求的长度与是'\0'之前的值,0的ASCII码值是'\0'
//	//printf("%d\n", strlen(a));
//
//	char a[100] = "Hello";
//	printf("%d\n", strlen(a));//5
//	return 0;
//}

//unsigned char i = 0;
////unsigned char 数据类型范围是0~255,恒满足以下条件,所以会发生死循环
//int main()
//{
//	for (i = 0; i <= 255; i++)
//	{
//		printf("hehe\n");
//	}
//	return 0;
//}

//int main()
//{
//	/*int len = strlen("abcdef");
//	printf("%d\n", len);*/
//
//	//strlen返回的值是size_t -> unsigned int
//	
//	if (strlen("abc") - strlen("abcdef") >= 0)
//		printf(">\n");
//	else
//		printf("<\n");
//	return 0;
//}


//
//int main()
//{
//	int n = 9;
//	float* pFloat = (float*)&n;
//
//	printf("n的值为:%d\n", n);
//	printf("*pFloat的值为:%f\n", *pFloat);
//	*pFloat = 9.0;
//	printf("n的值为:%d\n", n);
//	printf("*pFloat的值为:%f\n", *pFloat);
//
//	return 0;
//}


//输入一个整数数组,实现一个函数来调整该数组中数字的顺序
//使得数组中所有的奇数位于数组的前半部分,所有偶数位于数组的后半部分

#include<assert.h>
//void sort_array(int* arr, int size)
//{
//    assert(arr != NULL);
//
//    int left = 0;
//    int right = size - 1;
//
//    //使用双指针法
//    while (left < right)
//    {
//        //从左向右找第一个偶数
//        while (left < right && (arr[left] % 2 == 1))
//        {
//            //arr[left] %2 == 1 判断当前元素是否为奇数,如果是奇数,说明他在正确位置--前半部分
//            //继续向后移动,直到找到偶数  %2==0 他应该在后半部分,不满足循环条件,跳出循环
//            left++;
//        }
//
//        //从右向左找第一个奇数
//        while (left < right && (arr[right] % 2 == 0))
//        {
//            //arr[right] % 2 == 0判断元素是否是偶数,如果是偶数,满足循环条件,进入循环
//            //如果是奇数,跳出循环
//            right--;
//        }
//
//        //交换奇数和偶数
//        if (left < right)
//        {
//            int temp = arr[left];
//            arr[left] = arr[right];
//            arr[right] = temp;
//            left++;
//            right--;
//        }
//    }
//}
//
//int main()
//{
//    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//    int size = sizeof(arr) / sizeof(arr[0]);
//
//    sort_array(arr, size);
//
//    // 直接打印数组，不使用指针遍历直到0
//    for (int i = 0; i < size; i++)
//    {
//        printf("%d ", arr[i]);
//    }
//
//    return 0;
//}


//输入两个升序排列的序列,将两个序列合并为一个有序序列并输出
//输入包含三行,第一行包含两个正整数n和m,用空格分隔.
//n表示第二行第一个升序序列中数字的个数,m表示第三行第二个升序序列中数字的个数
//第二行包含n个整数, 用空格分隔.第三行包含m个整数, 用空格分隔
//输出为一行, 输出长度为n + m的升序序列, 
//即长度为n的升序序列和长度为m的升序序列中的元素重新进行升序序列排列合并

//int main()
//{
//	int n = 0;
//	int m = 0;
//	scanf("%d %d", &n, &m);
//	/*int arr1[n];   C99支持变长数组
//	int arr2[m];*/
//	int arr1[10000];
//	int arr2[10000];
//	int i = 0;
//	//输入n个整数
//	for (i = 0; i < n; i++)
//	{
//		scanf("%d", arr1 + i);
//	}
//	//输入m个整数
//	for (i = 0; i < m; i++)
//	{
//		scanf("%d", arr2 + i);
//	}
//
//	//合并打印
//	int j = 0;
//	int k = 0;
//	while (j < n && k < m)
//	{
//		if (arr1[j] < arr2[k])
//		{
//			printf("%d ", arr1[j]);
//			j++;
//		}
//		else
//		{
//			printf("%d ", arr2[k]);
//			k++;
//		}
//	}
//	//两个数组不等长,将更长数组的剩余元素进行打印
//	if (j < n)
//	{
//		for (; j < n; j++)
//		{
//			printf("%d ", arr1[j]);
//		}
//	}
//	else
//	{
//		for (; k < m; k++)
//		{
//			printf("%d ", arr2[k]);
//		}
//	}
//	return 0;
//}



//int main()
//{
//	int n = 0;
//	int m = 0;
//	scanf("%d %d", &n, &m);
//	/*int arr1[n];   C99支持变长数组
//	int arr2[m];*/
//	int arr1[10000];
//	int arr2[10000];
//	int arr3[10000];
//	int i = 0;
//	//输入n个整数
//	for (i = 0; i < n; i++)
//	{
//		scanf("%d", arr1 + i);
//	}
//	//输入m个整数
//	for (i = 0; i < m; i++)
//	{
//		scanf("%d", arr2 + i);
//	}
//
//	//合并打印
//	int j = 0;
//	int k = 0;
//	int r = 0;
//	while (j < n && k < m)
//	{
//		if (arr1[j] < arr2[k])
//		{
//			arr3[r++] = arr1[j];
//			j++;
//		}
//		else
//		{
//			arr3[r++] = arr2[k];
//			k++;
//		}
//	}
//	//两个数组不等长,将更长数组的剩余元素进行打印
//	if (j < n)
//	{
//		for (; j < n; j++)
//		{
//			arr3[r++] = arr1[j];
//		}
//	}
//	else
//	{
//		for (; k < m; k++)
//		{
//			arr3[r++] = arr2[k];
//		}
//	}
//
//	for (i = 0; i < n + m; i++)
//	{
//		printf("%d ", arr3[i]);
//	}
//	return 0;
//}










