#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
//实现strlen函数 --求字符串长度

int my_strlen(char* str)
{
	int length = 0;
	while (*str)
	{
		length++;
	}
	return length;
}

int main()
{
	char arr[] = "Hello bit";
	my_strlen(arr);
	printf("%d\n", my_strlen(arr));
	return 0;
}