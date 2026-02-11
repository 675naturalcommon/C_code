#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>


//
//int main()
//{
//	int r = isdigit('a');
//	//printf("%d\n", r);
//
//	if (r)
//	{
//		printf("是10进制的数字字符\n");
//	}
//	else
//	{
//		printf("不是10进制的数字字符\n");
//	}
//	return 0;
//}

//
//int main()
//{
//
//	if (islower('A'))
//	{
//		printf("是小写\n");
//	}
//	else
//	{
//		printf("不是小写\n");
//	}
//	return 0;
//}

//将字符串中的小写字母转大写,其他字符不变

//int main()
//{
//	char arr[] = "I am a Chinese!";
//	//将字符串中的字符逐个进行处理
//	//遇到小写,转换成大写,在输出
//	//如果不是小写,正常输出
//
//	/*char* str = arr;
//	while (*str)
//	{
//		if (islower(*str))
//		{
//			printf("%c", toupper(*str));
//		}
//		else
//		{
//			printf("%c", *str);
//		}
//		str++;
//	}*/
//
//	int i = 0;
//	while (arr[i])
//	{
//		if (islower(arr[i]))
//			arr[i] -= 32;
//		printf("%c", arr[i]);
//		i++;
//	}
//	return 0;
//}

//int main()
//{
//	//int r = toupper('a');  //将小写字母转换为大写
//	int r = tolower('A');  //将大写字母转换为小写
//	printf("%c\n", r);
//	return 0;
//}


//
//int main()
//{
//	char arr[] = "I am a Chinese!";
//	int i = 0;
//
//	while (arr[i])
//	{
//		if (islower(arr[i]))
//			arr[i] = toupper(arr[i]);
//		printf("%c", arr[i]);
//
//		i++;
//	}
//	return 0;
//}


//int main()
//{
//	char ch = 'w';
//	if (ch >= 'A' && ch <= 'Z')  //isupper
//	{
//		//...
//	}
//}

#include<string.h>


//int main()
//{
//	char arr[3] = { 'a','b','c' };
//	printf("%zu\n", strlen(arr));
//	size_t  len = strlen("abcdef");
//	printf("%zu\n", len);
//	return 0;
//}


//int main()
//{
//	/*if (strlen("abc") - strlen("abcdef") > 0)
//	{
//		printf(">\n");
//	}*/
//	//if (strlen("abc") > strlen("abcdef"))
//	if ((int)strlen("abc") - (int)strlen("abcdef") > 0)
//	{
//		printf(">\n");
//	}
//	else
//	{
//		printf("<=\n");
//	}
//	return 0;
//}



#include <assert.h>

//strlen函数的模拟实现
// 1.计数器方式
//int my_strlen(const char* str)
//{
//	int count = 0;
//	while (*str)
//	{
//		count++;
//		str++;
//	}
//	return count;
//}

// 2.指针-指针
//int my_strlen(const char* str)
//{
//	char* p = str;
//	while (*p)
//		p++;
//	return p - str;
//}

// 3.不能在函数内部创建临时变量,怎么求字符串长度?
// 使用递归

//size_t my_strlen(const char* str)
//{
//	assert(str);
//	if (*str != '\0')
//		return 1 + my_strlen(str + 1);
//	else
//		return 0;
//}
//
//
//int main()
//{
//	char str[] = "abcdef";
//
//	size_t len = my_strlen(str);
//	printf("%d\n", len);
//	return 0;
//}