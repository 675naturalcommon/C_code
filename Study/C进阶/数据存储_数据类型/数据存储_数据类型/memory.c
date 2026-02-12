#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <assert.h>
#include <string.h>

//void* my_memcpy(void* dest, const void* src, size_t num)
//{
//	assert(src);
//
//	void* ret = dest;
//	while (num--)
//	{
//		*(char*)dest = *(char*)src;
//		src = (char*)src + 1;
//		dest = (char*)dest + 1;
//	}
//	return ret;
//}
//int main()
//{
//	//int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
//	//int arr2[20] = { 0 };
//	//my_memcpy(arr2, arr1, sizeof(arr1));//将arr1中的内容复制到arr2
//
//	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
//	my_memcpy(arr + 2, arr, 20);//将arr中的内容复制到arr+2的位置上
//	//源字符串和目的字符串重叠,结果和自己想得到的结果不一样,因为在复制过程中,源字符串的内容被覆盖了
//	//这种情况就要用memmove函数,它会先把源字符串的内容复制到一个临时的空间中,
//	//然后再从这个临时空间复制到目的字符串中,这样就不会出现覆盖的问题了
//	return 0;
//}



//int main()
//{
//	//内存中没有重叠的情况
//	int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int arr2[20] = { 0 };
//
//	memmove(arr2, arr1, sizeof(arr1));//将arr1中的内容复制到arr2
//	return 0;
//}

//void* my_memmove(void* dest, const void* src, size_t num)
//{
//	assert(src);
//	void* ret = dest;
//	if (dest < src)
//	{
//		while (num--)
//		{
//			*(char*)dest = *(char*)src;
//			src = (char*)src + 1;
//			dest = (char*)dest + 1;
//		}
//	}
//	else
//	{
//		while (num--)
//		{
//			*((char*)dest + num) = *((char*)src + num);
//		}
//	}
//	return ret;
//}
//
//
//int main()
//{
//	//内存中有重叠的情况
//	int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
//	int arr2[20] = { 0 };
//
//	my_memmove(arr1 + 2, arr1, 20);//将arr1中的内容复制到arr2
//	return 0;
//}


//memset

//int main()
//{
//	//char arr[20] = "hello world";
//	//memset(arr + 2, '*', 5);//将arr中的3-8个字符设置为'*'
//	//printf("%s\n", arr);//***** world
//
//	int arr[10] = { 0 };
//	memset(arr, 1, 40);//这种方法不能将arr中的所有元素都设置为1
//	//因为memset是按照字节来设置的,而int类型占4个字节,所以每个元素被设置为0x01010101,也就是16843009
//	//memset(arr, -1, sizeof(arr));//将arr中的所有元素都设置为-1
//	//我们应避免使用memset来设置非字符类型的数组为非零值,因为它是按照字节来设置的,可能会导致意想不到的结果
//	//0和-1是特殊的值,因为它们在内存中都是全0和全1,所以可以正确地设置非字符类型的数组
//	//-1在补码下内存全1
//	return 0;
//}


//memcmp  --内存比较

int main()
{
	int arr1[] = { 1,2,3,4,5,6,7,8,9,10 };
	int arr2[] = { 1,2,3,4,5 };

	int r = memcmp(arr1, arr2, 20);//比较arr1和arr2的前20个字节

	if (r > 0)
		printf(">\n");
	else if (r < 0)
		printf("<\n");
	else
		printf("==\n");
	return 0;
}