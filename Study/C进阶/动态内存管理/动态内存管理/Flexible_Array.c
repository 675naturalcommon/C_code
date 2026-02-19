#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//柔性数组允许你在一个结构体的末尾定义一个没有指定大小的数组.这个数组的大小可以在运行时动态确定
//1.柔性数组必须是结构体的最后一个成员
//2.结构体中必须至少有一个其他命名的成员
//3.使用sizeof计算包含柔性数组的结构体大小时,不会包含柔性数组的内存,他只计算柔性数组之前的成员
//4.需要使用malloc动态内存分配函数,为整个结构体额外分配你所需要的柔性数组的空间
//struct S
//{
//	int i;
//	char c;
//	int a[];//柔性数组成员
//};



//struct packet 
//{
//    int length;
//    char data[];
//    // 柔性数组成员
//};
//int main() 
//{
//    char my_data[] = "Hello, Flexible Array Member!";
//    int data_length = strlen(my_data) + 1;
//    // 包含字符串结束符 '\0'
//    // 1. 一次性分配内存：结构体基础大小 + 数组所需大小
//    struct packet* p = (struct packet*)malloc(sizeof(struct packet) + data_length * sizeof(char));
//    if (p == NULL) 
//    {
//        perror("malloc failed");
//        return 1;
//    }
//    // 2. 初始化结构体
//    p->length = data_length;
//    // 直接将数据拷贝到柔性数组所在的内存区域
//    strcpy(p->data, my_data);
//    // 3. 使用
//    printf("Length: %d\n", p->length);
//    printf("Data: %s\n", p->data);
//    // 直接访问柔性数组
//    // 4. 一次性释放所有内存
//    free(p);
//    return 0;
//}

struct S
{
	int n;
	int* arr;//结构体中包含指针
};

int main()
{
	struct S* ps = (struct S*)malloc(sizeof(struct S));
	//printf("%zu\n", sizeof(struct S));
	if (ps == NULL)
	{
		perror("malloc");
		return 1;
	}
	ps->n = 100;
	int* ptr = (int*)malloc(10 * sizeof(int));
	if (ptr == NULL)
	{
		perror("malloc");
		return 1;
	}
	ps->arr = ptr;
	//存放1-10
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		ps->arr[i] = i + 1;
	}
	//空间不够,扩容
	ptr = realloc(ps->arr, 20 * sizeof(int));
	if (ptr == NULL)
	{
		perror("realloc");
		return 1;
	}
	ps->arr = ptr;
	//释放
	free(ps->arr);
	free(ps);
	ps = NULL;

	return 0;
}