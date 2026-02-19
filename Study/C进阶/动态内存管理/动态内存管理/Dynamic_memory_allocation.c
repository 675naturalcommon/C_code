#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// malloc
// void* malloc(size_t size)

// free
// void free(void* ptr)

// int main()
//{
//	int n = 0;
//	//输入要存放几个整型值
//	scanf("%d", &n);
//	int* p = (int*)malloc(n * sizeof(int));
//
//	//假设申请20个字节的空间,存放5个整数
//	int* p = (int*)malloc(5 * sizeof(int));
//	//判断返回值
//	if (p == NULL)//开辟失败了
//	{
//		perror("malloc");
//		return 1;
//	}
//	//开辟成功了
//	//使用这块空间了
//	int i = 0;
//	for (i = 0; i < 5; i++)
//	{
//		*(p + i) = i + 1;
//	}
//	for (i = 0; i < 5; i++)
//	{
//		printf("%d ", p[i]);
//	}
//
//	//当不在使用这块空间的时候,主动还回去
//	free(p);
//	p = NULL;
//	return 0;
// }
//

// calloc
// void* calloc(size_t num, size_t size)
// 函数功能:分配内存,并将内存初始化为0
// 参数:num:要分配的内存块的个数
// size:每个内存块的大小
// 返回值:返回指向新分配内存的指针
// 注意:calloc分配的内存空间,必须全部初始化为0,否则会出现未定义行为

// int main()
// {
//     // 申请10个int型的内存空间
//     // int *p = (int *)malloc(10 * sizeof(int));
//     int *p = (int *)calloc(10, sizeof(int));
//     if (p == NULL)
//     {
//         perror("calloc");
//         return 1;
//     }
//     // 使用这块内存空间
//     int i = 0;
//     for (i = 0; i < 10; i++)
//     {
//         printf("%d ", p[i]);
//     }
//     // 释放空间
//     free(p);
//     p = NULL;
//     return 0;
// }

// realloc
// void* realloc(void* ptr, size_t size)
// 函数功能:重新分配内存
// 参数:ptr:原先分配的内存块的地址
// size:新的内存块的大小
// 返回值:返回指向新分配内存的指针
// 注意:realloc重新分配的内存空间,原先分配的内存块的内容会被保留,新的内存块的内容会被初始化为0

// int main()
// {
//     // 申请5个int型的内存空间
//     int *p = (int *)malloc(5 * sizeof(int));
//     if (p == NULL) // 申请失败
//     {
//         perror("malloc");
//         return 1;
//     }
//     // 申请成功,使用这块内存空间
//     int i = 0;
//     for (i = 0; i < 5; i++)
//     {
//         p[i] = i + 1;
//     }
//     // 进行扩容,扩充为10个int型的内存空间
//     int *q = (int *)realloc(p, 10 * sizeof(int));
//     if (q == NULL)
//     {
//         perror("realloc");
//         free(p);
//         p = NULL;
//         return 1;
//     }
//     p = q; // 指向扩充后的内存空间;
//     for (i = 5; i < 10; i++)
//     {
//         p[i] = i + 1;
//     }
//     // 释放原先的内存空间
//     free(p);
//     p = NULL;

//     return 0;
// }

// realloc也可以直接用来申请内存空间
//
// int main()
// {
//     realloc(NULL,100);  //申请100字节的内存空间  -- 等价于malloc(100)
//     return 0;
// }

// 常见的动态内存错误

// 1.对NULL指针的解引用操作
// 没有对malloc,calloc,realloc函数的返回值做判断
//  int main()
//  {
//      int *p = (int *)malloc(INT_MAX);
//      if (p == NULL)
//      {
//          perror("malloc");
//          return 1;
//      }
//      int i = 0;
//      for (i = 0; i < 10; i++)
//      {
//          p[i] = i + 1;
//      }
//      free(p);
//      p = NULL;

//     return 0;
// }

// 2.对动态开辟空间的越界访问
// int main()
// {
//     int *p = (int *)malloc(5 * sizeof(int));
//     if (p == NULL)
//     {
//         perror("malloc");
//         return 1;
//     }
//     int i = 0;
//     for (i = 0; i < 10; i++) // 数组越界,当i == 5时,就已经越界了
//     {
//         p[i] = i + 1;
//     }
//     free(p);
//     p = NULL;

//     return 0;
// }

// 3.对非动态开辟内存使用free释放
// int main()
// {
//     int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int *p = arr;

//     free(p); // 错误:释放非动态开辟的内存空间
//     p = NULL;

//     return 0;
// }

// 4.使用free释放动态开辟内存的一部分
// int main()
// {
//     int *p = (int *)malloc(10 * sizeof(int));
//     if (p == NULL)
//     {
//         perror("malloc");
//         return 1;
//     }
//     int i = 0;
//     for (i = 0; i < 10; i++)
//     {
//         *p = i + 1;
//         p++;
//     }
//     free(p); // 错误:释放动态开辟内存的一部分,使用free一定要释放动态开辟内存空间的起始位置
//     p = NULL;
//     return 0;
// }

// 5.对申请的动态内存空间进行多次释放
// int main()
// {
//     int *p = (int *)malloc(10 * sizeof(int));
//     if (p == NULL)
//     {
//         perror("malloc");
//         return 1;
//     }
//     int i = 0;
//     for (i = 0; i < 10; i++)
//     {
//         p[i] = i + 1;
//     }
//     free(p); // 释放一次
//     p = NULL;
//     free(p); // 给free传的空指针,即使再次释放,也不会出错
//     return 0;
// }

// 6.对动态开辟内存忘记释放
// void test()
// {
//     int *p = (int *)malloc(10 * sizeof(int));
//     if (p == NULL)
//     {
//         perror("malloc");
//         return;
//     }
// }

// int main()
// {
//     test();

//     return 0;
// }

// void GetMemory(char *p)
// {
//     p = (char *)malloc(100);
// }

// void Test(void)
// {
//     char *str = NULL;
//     GetMemory(str);
//     strcpy(str, "Hello, world!");
//     printf(str);
// }

// int main()
// {
//     Test();//程序会崩溃,因为GetMemory函数中采用的是值传递,形参变量p其实是str的一份拷贝
//     //当我们把malloc申请的空间的起始地址存放在p中时,不会修改str,str依然为NULL
//     //所以当GetMemory函数返回后,再去调用strcpy函数需要将"hello world"拷贝到str指向的空间,
//     //程序会崩溃
//     //另外malloc申请的空间并没有被释放,导致内存泄露
//     return 0;
// }

// void GetMemory(char **p)
// {
//     *p = (char *)malloc(100);
// }

// void Test(void)
// {
//     char *str = NULL;
//     GetMemory(&str);
//     strcpy(str, "Hello, world!");
//     printf(str);
//     free(str); // 释放动态开辟的内存空间
//     str = NULL;
// }

// int main()
// {
//     Test();
//     return 0;
// }

// char *GetMemory()
// {
//     char *p = (char *)malloc(100);
//     return p;
// }

// void Test(void)
// {
//     char *str = NULL;
//     str = GetMemory();
//     strcpy(str, "Hello, world!");
//     printf(str);
//     free(str); // 释放动态开辟的内存空间
//     str = NULL;
// }

// int main()
// {
//     Test();
//     return 0;
// }

// char *GetMemory(void)
// {
//     char p[] = "Hello, world!";
//     return p;
// }

// //p是局部变量,在函数返回后,p指向的空间就被释放了,所以会打印出来随机值
// void Test(void)
// {
//     char *str = NULL;
//     str = GetMemory();
//     printf(str);
// }

// int main()
// {
//     Test();
//     return 0;
// }

// char *GetMemory(void)
// {
//     static char p[] = "Hello, world!";
//     return p;
// }
// //static修饰的数组是存放在内存的静态区的
// void Test(void)
// {
//     char *str = NULL;
//     str = GetMemory();
//     printf(str);
// }

// int main()
// {
//     Test();
//     return 0;
// }

// void GetMemory(char **p, int num)
// {
//     *p = (char *)malloc(num);
// }
// //没有释放动态开辟的内存空间,导致内存泄露
// void Test(void)
// {
//     char *str = NULL;
//     GetMemory(&str, 100);
//     strcpy(str, "hello");
//     printf(str);
//     free(str); // 释放动态开辟的内存空间
//     str = NULL;
// }

// int main()
// {
//     Test();
//     return 0;
// }

// void Test(void)
// {
//     char *str = (char *)malloc(100);
//     strcpy(str, "hello");
//     free(str);
//     //str = NULL;  //手动将str置为空,防止str变为野指针
//     //free(str)之后,str原本用malloc申请的空间就被释放了,这块空间可能被计算机分配给其他进程使用
//     //但此时str还是指向的原地址
//     //所以str此时是野指针,再次访问该地址可能会导致程序崩溃
//     //所以在free之后,应该将str置为NULL,避免再次使用野指针
//     if (str != NULL)//这本身就是个无效判断,free之后,str的值不为空
//     {
//         strcpy(str, "world");
//         printf(str);
//     }
// }

// int main()
// {
//     Test();
//     return 0;
// }