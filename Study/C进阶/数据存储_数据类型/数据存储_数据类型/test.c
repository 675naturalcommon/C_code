#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <string.h>

// int main()
// {
//     int a[] = {1, 2, 3, 4};

//     printf("%d\n", sizeof(a));
//     // sizeof(数组名),数组名表示整个数组,计算的是整个数组的大小,单位是字节
//     // sizeof(数组名[下标]),数组名[下标]表示数组的某个元素,计算的是单个元素的大小,单位是字节
//     printf("%d\n", sizeof(a + 0)); // 首元素的地址
//     // a不是单独放在sizeof内部,也没有取地址,所以a就是首元素的地址,a+0还是首元素的地址
//     // 是地址,大小就是指针的大小,指针的大小是4字节或8字节,取决于系统的位数
//     //  sizeof(数组名 + 偏移量),数组名 + 偏移量表示数组的某个元素,计算的是单个元素的大小,单位是字节
//     //  数组名 + 偏移量的形式表示数组的某个元素,偏移量是字节数,从数组的开头算起,正数表示向后偏移,负数表示向前偏移
//     printf("%d\n", sizeof(*a));
//     // a == &a[0]  *a == *&a[0] == a[0],所以sizeof(*a) == sizeof(a[0])
//     // sizeof(*数组名),*数组名表示数组的第一个元素,计算的是单个元素的大小,单位是字节
//     printf("%d\n", sizeof(a + 1));
//     // a+1表示数组的第二个元素的地址,地址的大小就是指针的大小,指针的大小是4字节或8字节,取决于系统的位数
//     // sizeof(数组名 + 偏移量),数组名 + 偏移量表示数组的某个元素,计算的是单个元素的大小,单位是字节
//     printf("%d\n", sizeof(a[1]));
//     // a[1]是第二个元素所占内存空间的大小,单位是字节,sizeof(a[1]) == sizeof(int),占4个字节
//     printf("%d\n", sizeof(&a));
//     // &a表示数组的首地址,地址的大小就是指针的大小,指针的大小是4字节或8字节,取决于系统的位数
//     printf("%d\n", sizeof(*&a));
//     // &a --> 取出的是数组的地址,它的类型是int(*)[4],是数组指针,数组指针解引用,找到的是数组
//     printf("%d\n", sizeof(&a + 1));
//     //&a取出的是整个数组的地址,&a --> int(*)[4],&a+1 --> int(*)[4],跳过的是整个数组的大小
//     //&a+1还是地址,是地址就是4/8个字节
//     printf("%d\n", sizeof(&a[0]));
//     // 第一个元素的地址大小
//     printf("%d\n", sizeof(&a[0] + 1));
//     // 第二个元素的地址大小  &a[0] + 1---> &a[1]
//     return 0;
// }

// int main()
// {
//     char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
//     printf("%d\n", sizeof(arr)); // 6
//     // sizeof(数组名),数组名表示的是整个数组,计算的是整个数组的大小,单位是字节
//     printf("%d\n", sizeof(arr + 0)); // 8
//     // arr+0是数组首元素的地址,是地址,就表示4/8个字节,具体取决于系统的位数
//     printf("%d\n", sizeof(*arr)); // 1
//     // 数组名不是单独放在sizeof里,所以数组名表示首元素地址,
//     // 首元素地址解引用,所以*arr == arr[0] == 'a',大小是1个字节
//     printf("%d\n", sizeof(arr[1])); // 1
//     printf("%d\n", sizeof(&arr));   // 8
//     // arr表示数组首元素的地址,&arr还是数组首元素的地址,地址是4/8个字节,具体取决于系统的位数
//     printf("%d\n", sizeof(&arr + 1)); // 8
//     // 第二个元素的地址
//     printf("%d\n", sizeof(&arr[0] + 1)); // 8
//     // 第二个元素的地址
//     return 0;
// }

// int main()
//{
//     char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
//	  char arr1[] = "abcdef";
//	  printf("%d\n", strlen(arr));         //随机值,直到遇到'\0'才停止,所以结果不确定
//     printf("%d\n", strlen(arr + 0));     //随机值
//
//     printf("%d\n", strlen(*arr));        //strlen('a')-->strlen(97) //野指针
//	  printf("%d\n", strlen(arr[1]));      //strlen('b')-->strlen(98) //野指针
//
//     printf("%d\n", strlen(&arr));        //随机值
//     printf("%d\n", strlen(&arr + 1));    //随机值-6
//     printf("%d\n", strlen(&arr[0] + 1)); //随机值-1
//     return 0;
// }

// int main()
// {
// 	char arr[] = "abcdef";

// 	printf("%d\n", sizeof(arr));        //7
// 	printf("%d\n", sizeof(arr + 0));    //4/8
// 	printf("%d\n", sizeof(*arr));       //1
// 	printf("%d\n", sizeof(arr[1]));     //1
// 	printf("%d\n", sizeof(&arr));       //4/8
// 	printf("%d\n", sizeof(&arr + 1));   //4/8
// 	printf("%d\n", sizeof(&arr[0] + 1));//4/8

// 	//strlen是求字符串长度的,关注的是字符串中的\0,计算的是\0之前出现的字符的个数
// 	//strlen是库函数,只针对字符串
// 	//
// 	//sizeof只关注占用内存空间大小,不在乎放的什么
// 	//sizeof是操作符
// 	printf("%d\n", strlen(arr));         //6
//     printf("%d\n", strlen(arr + 0));     //6

//     //printf("%d\n", strlen(*arr));        //野指针
// 	//printf("%d\n", strlen(arr[1]));      //野指针

//     printf("%d\n", strlen(&arr));        //6
//     printf("%d\n", strlen(&arr + 1));    //12 随机值

//     printf("%d\n", strlen(&arr[0] + 1)); //5

// 	return 0;
// }

int main()
{
    char *p = "abcdef";

    printf("%d\n", sizeof(p));      //4/8
    printf("%d\n", sizeof(p + 1));  //4/8
    printf("%d\n", sizeof(*p));     //1
    printf("%d\n", sizeof(p[0]));   //1
    printf("%d\n", sizeof(&p));     //4/8
    printf("%d\n", sizeof(&p + 1)); //4/8
    printf("%d\n", sizeof(&p[0] + 1)); //4/8

    printf("%d\n", strlen(p));       //6
    printf("%d\n", strlen(p + 1));   //5
    //printf("%d\n", strlen(*p));      //err
    //printf("%d\n", strlen(p[0]));    //err
    printf("%d\n", strlen(&p));      //随机值
    printf("%d\n", strlen(&p + 1));  //随机值,比上面的随机值
    printf("%d\n", strlen(&p[0] + 1)); //随机值

    return 0;
}