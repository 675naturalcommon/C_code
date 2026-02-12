#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <assert.h>

// int main()
//{
//     char arr1[] = "Hello World";
//     char arr2[20] = { 0 };
//     char* ret = strcpy(arr2, arr1);  //将arr1中的字符串复制到arr2中
//	printf("%s\n", arr2);
//     printf("%s\n", ret);
//
//     return 0;
// }

// int main()
//{
//     char arr1[] = "Hello World";
//     char* p = "***********************";   //常量字符串,不能被修改,目的地址一定要能被修改
//     char* ret = strcpy(p, arr1);  //将arr1中的字符串复制到arr2中
//	printf("%s\n", p);
//     printf("%s\n", ret);
//
//     return 0;
// }

// 模拟实现strcpy函数
// char *my_strcpy(char* dest, const char* src)
//{
//	char* ret = dest;
//	while (*src)//拷贝'\0'之前的字符
//	{
//		*dest = *src;
//		src++;
//		dest++;
//	}
//	*dest = *src;   //拷贝'\0'
//	return ret;
// }

// char* my_strcpy(char* dest, const char* src)
//{
//	char* ret = dest;
//	while (*src)//拷贝'\0'之前的字符
//	{
//		*dest++ = *src++;
//	}
//	*dest = *src;   //拷贝'\0'
//	return ret;
// }

// char* my_strcpy(char* dest, const char* src)
//{
//	char* ret = dest;
//	while (*dest++ = *src++)
//	{
//		;
//	}
//	return ret;
// }

// char *my_strcpy(char *dest, const char *src)
// {
//     assert(dest && src);
//     char *ret = dest;
//     while (*dest++ = *src++)
//     {
//         ;
//     }
//     return ret;
// }

// int main()
// {
//     char arr1[] = "Hello World";
//     char arr2[] = "***************";
//     char *ret = my_strcpy(arr2, arr1);
//     printf("%s\n", arr2);
//     printf("%s\n", ret);
//     return 0;
// }

// char *my_strcat(char *dest, const char *src)
//{
//     assert(dest && src);
//     char *ret = dest;
//     while (*dest)
//         dest++;
//     while (*dest++ = *src++)
//     {
//         ;
//     }
//     return ret;
// }
//
// int main()
//{
//     char arr1[20] = "Hello";
//     char arr2[] = "World";
//
//     char *ret = my_strcat(arr1, arr2);
//     printf("%s\n", ret);
//     return 0;
// }

// strcmp  -- string compare 字符串比较
//
//int my_strcmp(const char* str1, const char* str2)
//{
//    assert(str1 && str2);
//    while (*str1 == *str2)
//    {
//        if (*str1 == '\0')
//            return 0;
//        str1++;
//        str2++;
//    }
//    if (*str1 > *str2)
//        return 1;
//    else
//        return -1;
//}
//
//int main()
//{
//    char arr1[] = "abcdef";
//    char arr2[] = "abc";
//
//    int r = my_strcmp(arr1, arr2);
//    if (r > 0)
//        printf("arr1[] > arr2[]\n");
//    else if (r < 0)
//        printf("arr1[] < arr2[]\n");
//    else
//        printf("arr1[] == arr2[]\n");
//
//    return 0;
//}

//strncpy的模拟实现

//char* my_strncpy(char* dest, const char* src, size_t n)
//{
//	if (n == 0)
//		return dest;
//
//	size_t i;
//	for (i = 0; i < n && src[i] != '\0'; i++)
//	{
//		dest[i] = src[i];
//	}
//	//剩余位置填充'\0'
//	for (; i < n; i++)
//	{
//		dest[i] = '\0';
//	}
//
//	return dest;
//}


//int main()
//{
//	char arr1[10] = "abcdefghi";
//	char arr2[20] = { 0 };
//
//	my_strncpy(arr2, arr1, 5);
//
//	printf("%s\n", arr2);
//	
//	return 0;
//}

//char* my_strncat(char* dest, const char* src, size_t n)
//{
//	if (n == 0)
//		return dest;
//
//	char* ret = dest;
//
//	//找到dest的末尾
//	while (*dest)
//		dest++;
//	//拷贝最多n个字符
//	size_t i = 0;
//	for (i = 0; i < n && src[i] != '\0'; i++)
//	{
//		dest[i] = src[i];
//	}
//
//	//始终添加终止空字符
//	dest[i] = '\0';
//
//
//	return ret;
//}
//
//int main()
//{
//	char arr1[10] = "abcdefghi";
//	char arr2[20] = "xxx";
//
//	my_strncat(arr2, arr1, 5);
//
//	printf("%s\n", arr2);
//
//	return 0;
//}

//char* my_strstr(const char* str1, const char* str2)
//{
//	assert(str1 && str2);
//
//	if (*str2 == '\0')
//	{
//		return (char*)str1;
//	}
//
//	while (*str1)
//	{
//		const char* h = str1;
//		const char* n = str2;
//
//		//逐个字符比较
//		while (*h && *n && *h == *n)
//		{
//			h++;
//			n++;
//		}
//
//		//如果字符完全匹配(n走到了结尾)
//		if (*n == '\0')
//		{
//			return (char*)str1;
//		}
//
//		//否则移动str1继续尝试
//		str1++;
//	}
//
//	//没有找到
//	return NULL;
//}
//
////KMP算法实现
//
////构建部分匹配表(next 数组)
//static void* build_next(const char* pattern, int* next, int m)
//{
//	next[0] = -1;
//	int i = 0;
//	int j = -1;
//	while (i < m - 1)
//	{
//		if (j == -1 || pattern[i] == pattern[j])
//		{
//			i++;
//			j++;
//			next[i] = j;
//		}
//		else
//		{
//			j = next[j];
//		}
//	}
//}
//
//char* my_strstr_kmp(const char* haystack, const char* needle)
//{
//	if (*needle == '\0')
//		return (char*)haystack;
//
//	int n = strlen(haystack);
//	int m = strlen(needle);
//	if (n < m)
//		return NULL;
//
//	int* next = (int*)malloc(m * sizeof(int));
//	build_next(needle, next, m);
//
//	int i = 0, j = 0;
//	while (i < n && j < m)
//	{
//		if (j == -1 || haystack[i] == needle[j])
//		{
//			i++; j++;
//		}
//		else
//		{
//			j = next[j];
//		}
//	}
//	free(next);
//	return (j == m) ? (char*)(haystack + i - m) : NULL;
//}
//
//int main()
//{
//	char arr1[] = "abcdefghijklmn";
//	char arr2[] = "ghi";
//
//	char* p = my_strstr(arr1, arr2);
//	
//	if (p != NULL)
//	{
//		printf("找到了,%s\n", p);
//	}
//	else
//	{
//		printf("未找到\n");
//	}
//	return 0;
//}



//strtok函数的使用 
//分割字符串

//int main()
//{
//	char arr1[] = "ahu.edu.cn@com";
//	char arr2[100] = { 0 };
//	char sep[] = "@.";
//
//	strcpy(arr2, arr1);
//	char* p = NULL;
//	for (p = strtok(arr2, sep); p; p = strtok(NULL, sep))
//	{
//		printf("%s\n", p);
//	}
//	return 0;
//}

//strerror函数的使用
//int main()
//{
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d :%s\n", i, strerror(i));
//	}
//	return 0;
//}



//perror  print error

