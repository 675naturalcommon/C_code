#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<assert.h>
//实现strlen函数 --求字符串长度

//int my_strlen(const char* str)//const修饰,*str不能被改变
//{
//	int length = 0;
//	assert(str != NULL);
//	while (*str)
//	{
//		length++;
//		str++;
//	}
//	return length;
//}
//
//int main()
//{
//	char arr[] = "Hello bit";
//	/*int len = my_strlen(arr);
//	printf("%d\n", len);*/
//	printf("%d\n", my_strlen(arr));
//	return 0;
//}

//判断三角形
//int main()
//{
//	int a = 0;
//	int b = 0;
//	int c = 0;
//	while ((scanf("%d %d %d", &a, &b, &c)) == 3)
//	{
//		if (a <= 0 || b <= 0 || c <= 0)
//		{
//			printf("Not a triangle!\n");
//		}
//		else if ((a + b > c) && (a + c > b) && (b + c > a))
//			{
//				if (a == b && b == c)
//				{
//					printf("Equilateral triangle!\n");
//				}
//				else if ((a == b && b != c) || (a == c && c != b) || (b == c && c != a))
//				{
//					printf("Isosceles triangle!\n");
//				}
//				else
//				{
//					printf("Oridinary triangle!\n");
//				}
//			}
//		else
//		{
//			printf("Not a triangle!\n");
//		}
//	}
//	return 0;
//}

//ctrl + f 查找

//
//int main()
//{
//	int arr[] = { 1,2,3,4,5 };
//	short* p = (short*)arr;
//	for (int i = 0; i < 4; i++)
//	{
//		*(p + i) = 0;
//	}
//	for (int i = 0; i < 5; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}

//写一个函数打印arr数组的内容,使用指针,不使用数组下标

//void print_arr(int* ptr, int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *(ptr + i));
//	}
//	printf("\n");
//}
//int main()
//{
//	int arr[] = { 1,2,3,4,5 };
//	print_arr(arr, sizeof(arr) / sizeof(arr[0]));
//	return 0;
//}


//写一个函数,可以逆序字符串的内容
//void string_turn(char* ptr)
//{
//	char* left = ptr;
//	char* right = ptr;
//	while (*ptr != '\0')
//	{
//		right++;
//		ptr++;
//	}
//	right--;
//	while (left <= right)
//	{
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//}
//
//
//int main()
//{
//	//char string[] = "abcdef";
//	char string[] = "I am a student!";
//	string_turn(string);
//	printf("%s\n", string);
//	return 0;
//}

//int main()
//{
//	char arr[10001] = "0";
//	gets(arr);   //输入arr的内容,不用scanf的原因是scanf遇到空格就结束输入
//
//	int left = 0;
//	int right = strlen(arr) - 1;
//
//	while (left < right)
//	{
//		char temp = arr[left];
//		arr[left] = arr[right];
//		arr[right] = temp;
//		left++;
//		right--;
//	}
//	printf("%s\n", arr);
//	return 0;
//}

//求Sn = a + aa + aaa + aaaa + aaaaa的前五项之和,其中a是一个数字
//例如: 2+22+222+2222+22222
//22 = 2*10+2
//222 = 22*10+2
//2222 = 222*10+2

//int main()
//{
//	int a = 0;
//	int n = 0;
//	scanf("%d %d", &a, &n);
//	int i = 0;
//	int sum = 0;
//	int k = 0;
//	for (i = 0; i < n; i++)
//	{
//		k = k * 10 + a;
//		sum += k;
//	}
//
//	printf("%d\n", sum);
//	return 0;
//}

//求出0-100000之间的所有"水仙花数"并输出
//"水仙花数"是指一个n位数,其各数数字的n次方之和确好等于该数本身,如:153 = 1^3 + 5^3 + 3^3,153是一个水仙花数
//#include<math.h>
//
//int is_narcissistic_number(int i)
//{
//
//	int n = 1; //计算i是几位数
//	int tmp = i; //创建一个变量,防止i被改变
//	int sum = 0;   //计算和
//	while (tmp / 10)
//	{
//		n++;
//		tmp = tmp / 10;
//	}
//	tmp = i;
//	while (tmp)
//	{
//		sum += pow(tmp % 10, n);
//		tmp /= 10;
//	}
//	return sum == i;
//	/*if (sum == i)
//	{
//		return 1;
//	}
//	else
//	{
//		return 0;
//	}*/
//
//}
//
//int main()
//{
//	int i = 0;
//	for (i = 0; i <= 100000; i++)
//	{
//		if (is_narcissistic_number(i))
//		{
//			printf("%d ", i);
//		}
//	}
//	
//	return 0;
//}
// 
// 
//int main()
//{
//	int i = 0;
//	for (i = 0; i <= 100000; i++)
//	{
//		int n = 1; //计算i是几位数
//		int tmp = i; //创建一个变量,防止i被改变
//		int sum = 0;   //计算和
//		while (tmp /10)
//		{
//			n++;
//			tmp = tmp / 10;
//		}
//		tmp = i;
//		while (tmp)
//		{
//			sum += pow(tmp % 10, n);
//			tmp /= 10;
//		}
//		if (sum == i)
//		{
//			printf("%d ", i);
//		}
//	}
//	return 0;
//}


//int main()
//{
//	int line = 0;
//	scanf("%d", &line);
//	//上
//	int i = 0;
//	for (i = 0; i < line; i++)
//	{
//		//打印一行
//		//空格
//		int j = 0;
//		for (j = 0; j < line - 1 - i; j++)
//		{
//			printf(" ");
//		}
//		//*
//		for (j = 0; j < 2 * i + 1; j++)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//
//	//下
//	for (i = 0; i < line - 1; i++)
//	{
//		//打印一行
//		//空格
//		int j = 0;
//		for (j = 0; j <= i; j++)
//		{
//			printf(" ");
//		}
//		//*
//		for (j = 0; j < 2 * (line - 1 - i) - 1; j++)
//		{
//			printf("*");
//		}
//		printf("\n");
//	}
//	return 0;
//}


//喝汽水,一瓶汽水一元,两个空瓶可以换一瓶汽水,给20元,可以喝多少汽水(编程实现)

//int max_soda(int money)
//{
//	int total = money;
//	int empty = total;
//	while (empty >= 2)
//	{
//		int new_bottles = empty / 2;
//		total += new_bottles;
//		empty = empty % 2 + new_bottles;
//	}
//	return total;
//}
//
//int main()
//{
//	int money = 0;
//	scanf("%d", &money);
//	int count = max_soda(money);
//	printf("%d\n", count);
//	return 0;
//}

int max_soda(int money)
{
	if (money <= 0)
	{
		return 0;
	}
	else
	{
		return 2 * money - 1;
	}
}

int main()
{
	int money = 0;
	scanf("%d", &money);
	int total = max_soda(money);
	printf("%d", total);
	return 0;
}