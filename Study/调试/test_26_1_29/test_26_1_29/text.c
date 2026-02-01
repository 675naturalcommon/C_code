#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


//int main()
//{
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", i);
//	}
//	printf("\n");
//	return 0;
//}

//
//int Add(int x, int y)
//{
//	return x + y;
//}
//
//int main()
//{
//	int a = 10;
//	int b = 20;
//	int sum = Add(a, b);
//	printf("sum = %d\n", sum);
//	return 0;
//}

//1! + 2! + 3! + ... + n!

//
//int main()
//{
//	int n = 0;
//	scanf("%d", &n);
//	int i = 0;
//	int j = 0;
//	int ret = 1;
//	int sum = 0;
//	for (j = 1; j <= n; j++)
//	{
//		ret = 1;
//		for (i = 1; i <= j; i++)
//		{
//			ret *= i;
//		}
//		sum += ret;
//	}
//
//	printf("%d\n", sum);
//	return 0;
//}


// int main()
// {
// 	int i = 0;
// 	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
// 	//int i = 0;

// 	for (i = 0; i <= 12; i++)
// 	{
// 		arr[i] = 0;
// 		printf("hehe\n");
// 	}

// 	return 0;
// }

//栈区的使用习惯是先使用高地址的空间,在使用低地址的空间
//数组随着下标的增加,地址是从低到高增长的
//如果i和arr数组之间空间过短,利用数组越界,就可能把i覆盖掉,从而出现死循环

//模拟实现库函数,strcpy

//#include<string.h>
//int main()
//{
//	char arr1[20] = {0};
//	char arr2[] = "Hello bit";
//	strcpy(arr1,arr2);
//	//strcpy在拷贝字符串的时候,会把源字符串中的'\0'也拷贝过去
//	printf("%s\n",arr1);
//	return 0;
//}


//void my_strcpy(char* dest, char* src)
//{
//	while (*src != '\0')
//	{
//		*dest = *src;
//		dest++;
//		src++;
//	}
//	//*dest = '\0';
//	*dest = *src;
//}

//void my_strcpy(char* dest, char* src)
//{
//	while (*dest++ = *src++)
//	{
//		;
//	}
//}

//#include <assert.h>
//
//void my_strcpy(char* dest,const char* src)//加上const保证src里面的源数据不能被改变
//{
//	//断言
//	assert(src != NULL);
//	assert(dest != NULL);
//	while (*dest++ = *src++)
//	{
//		;
//	}
//}
//int main()
//{
//	char arr1[20] = "xxxxxxxxxxxxxx";
//	char arr2[] = "Hello bit";
//	my_strcpy(arr1, arr2);
//
//	printf("%s\n", arr1);
//
//	return 0;
//}

//为什么返回char*
// 是为了实现链式访问
// strcpy函数返回的是目标空间的起始地址
// 
char* my_strcpy1(char* dest, const char* src)
{
	if (dest == NULL || src == NULL)
	{
		return NULL;
	}
	char* ret = dest;
	while (*dest++ = *src++)
	{
		;
	}
	return ret;
}

//使用索引实现
//char* my_strcpy1(char* dest, const char* src)
//{
//	int i = 0;
//	while ((dest[i] = src[i]) != '\0')
//	{
//		i++;
//	}
//	return dest;
//}

//安全的strcpy(带长度限制) - 类似strcpy但不完全一样
//char* my_strcpy_safe(char* dest, const char* src, size_t dest_size)
//{
//	if (dest == NULL || src == NULL || dest_size == 0)
//		return NULL;
//
//	size_t i;
//	for (i = 0; i < dest_size - 1 && src[i] != '\0'; i++) 
//	//i<dest_size-1的作用是假设dest_size有n个空间可以存取字符,
//	// 那么可以保证前n-1个空间都可以复制传过来的字符串
//	//如果源字符串超过n个空间,那么后面的字符会丢弃不再进行复制,而src最后一个位置存放的是'\0'
//	{
//		dest[i] = src[i];
//	}
//	dest[i] = '\0';
//
//	return dest;
//}
//
//int main()
//{
//	char src[] = "Hello,World!";
//	char dest[10];
//
//	my_strcpy_safe(dest, src, sizeof(dest));
//	printf("%s\n", dest);
//	return 0;
//}
// 
// 
int main()
{
	char arr1[20] = "xxxxxxxxxxxxxx";
	char arr2[] = "Hello bit";
	char* ret = my_strcpy1(arr1, arr2);
	//printf("%s\n", ret);
	printf("%s\n", my_strcpy1(arr1, arr2));
	return 0;
}


//int main()
//{
//	/*int num = 10;
//	num = 20;
//	printf("%d\n", num);*/
//
//	const int num = 20;
//	//num = 100;
//
//	//const修饰指针变量
//
//	//1.const放在*左边
//	//意思是p指向的对象不能通过p来改变,但是p变量本身的值(也就是p指向的地址)是可以进行改变的
//	//*p = 100;    //这种写法就是错误的
//	//const int* p = &num;
//	//int n = 100;
//	////int const* p     //这种写法和上面写法是一样的
//	////*p = 100;       //err
//
//	//p = &n; //ok,但不会改变num的值
//
//	//2.const放在*的右边
//	//意思是p指向的对象可以通过p来改变,但p本身的值(也就是p存的地址不能被改变)
//	int* const p = &num;
//	*p = 0;   //ok
//	int n = 100;
//	//p = &n; //err
//	printf("%d\n", num);
//	return 0;
//}