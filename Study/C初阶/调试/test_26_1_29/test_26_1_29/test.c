#define _CRT_SECURE_NO_WARNINGS

//#include<stdio.h>

//计算两个数的最小公倍数
//int main()
//{
//	int a = 0;
//	int b = 0;
//	scanf("%d %d", &a, &b);
//	//int m = (a > b) ? a : b;
//	//while (1)
//	//{
//	//	if (m % a == 0 && m % b == 0)
//	//	{
//	//		break;
//	//	}
//	//	m++;
//	//}
//	int i = 1;
//	while (1)
//	{
//		if (a * i % b == 0)
//		{
//			printf("%d", a * i);
//			break;
//		}
//		i++;
//	}
//	
//	return 0;
//}

//将一句话的单词进行倒置，标点不倒置。比如 I like beijing.经过函数后变为：beijing.like I

//#include<assert.h>
//#include<string.h>
//
//void reverse(char* left, char* right)
//{
//	assert(left);
//	assert(right);
//	while (left < right)
//	{
//		char tmp;
//		tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//}
//
//int main()
//{
//	char string[101] = "0";
//	gets(string);
//	int len = strlen(string);
//	//逆置整个字符串
//	reverse(string, string + len - 1);
//
//	//逆序每个单词
//	char* start = string;
//	while (*start)
//	{
//		char* end = start;
//		while (*end != ' ' && *end != '\0')
//		{
//			end++;
//		}
//		reverse(start, end - 1);
//		if (*end != '\0')
//			end++;
//		start = end;
//	}
//	printf("%s\n", string);
//
//	return 0;
//}

#include <stdio.h>
#include <string.h>

//int main()
//{
//    char a[1000];
//    int len, i, j;
//    gets(a);  //输入字符串
//    len = strlen(a);  //求取字符串长度
//    for (i = len - 1; i >= 0; i--)  //使a[i]指向的位置是输入的字符串的最后一位
//    {
//        if (a[i] == ' ')
//        {
//            for (j = i + 1; a[j] != '\0' && a[j] != ' '; j++)//逆置单词
//                printf("%c", a[j]);
//            printf(" ");
//        }
//    }
//    //以下代码的作用是输出字符串的第一个单词
//    i = 0;
//    while (a[i] != ' ')
//        i++;
//    for (j = 0; j < i; j++)
//        printf("%c", a[j]);
//}

//编写一个函数,实现字符串的左旋操作,例如:输入"abcdef"和2,输出"cdefab"
//void left_ronate_string(char* str, int n)
//{
//	//计算字符串长度
//	int len = 0;
//	char* p = str;
//	while (*p)
//	{
//		len++;
//		p++;
//	}
//	n = n % len;//防止n大于字符串长度
//	//反转前n个字符
//	char* left = str;
//	char* right = str + n - 1;
//	while (left < right)
//	{
//		char tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//	//反转剩余字符
//	left = str + n;
//	right = str + n - 1;
//	while (left < right)
//	{
//		char tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//	//反转整个字符串
//	left = str;
//	right = str + len - 1;
//	while (left < right)
//	{
//		char tmp = *left;
//		*left = *right;
//		*right = tmp;
//		left++;
//		right--;
//	}
//}
//
//int main()
//{
//	char arr[] = "abcdef";
//	int n = 2;
//	left_ronate_string(arr, n);
//	printf("%s\n", arr);
//	return 0;
//}

