#include<iostream>
using namespace std;
#define VALUES 5
//int main()
//{
//	int* p;//p没有初始化,没有明确的指向,是野指针
//	//一个局部变量没有初始化,默认值是随机值:0xCCCCCCCC
//
//	*p = 10;//野指针指向的位置不可控,可能会引发程序崩溃
//
//	return 0;
//}

//越界访问

//int main()
//{
//	int arr[10] = { 0 };
//	int* p = arr;
//	for (int i = 0; i <= 10; i++)
//	{
//		*p = i;
//		p++;//指针向后移动4个字节,指向下一个整形元素,当i=10时,p指向arr[10]后面的位置,会发生越界访问
//	}
//	return 0;
//}
//
//int* test()
//{
//	int a = 10;
//	return &a; //返回局部变量的地址
//}
//
//int main()
//{
//	int* p = test();
//	cout << *p << endl; //会发生越界访问
//	return 0;
//}

//int main()
//{
//	//int a = 10;
//	//int* p = &a;//指针p指向变量a的地址,,明确给p初始化
//
//
//	//int* p2 = nullptr; //指针变量初始化为空指针,不指向任何有效的内存空间,相当于int b = 10;
//	////nullptr是C++11引入的关键字,表示空指针,NULL是C语言中的空指针,本质上是0
//	///**p2 = 20; *///空指针不可解引用,会引发程序崩溃
//	//if (p2 != nullptr) //使用指针前,检查指针是否为空指针
//	//{
//	//	*p2 = 20;
//	// }
//	return 0;
//}

//int* test()
//{
//	int a = 10;
//	return &a; //返回局部变量的地址	
//}
//
//int main()
//{
//	int* p = test();
//	if (p != nullptr)
//	{
//		cout << *p << endl; //会发生越界访问
//	}
//}

//int main()
//{
//	float values[VALUES];
//	float* vp = values;
//	for (vp = &values[0]; vp < &values[VALUES];)//values[VALUES]是一个越界元素,数组的内容是values[0]到values[VALUES-1]
//	{
//		*vp++ = 0;
//	}
//	return 0;
//
//}

//*vp++和*(vp++)是等价的,先解引用再自增
//*vp++等价于*(vp);vp=vp+1;
//*vp++和*++vp是不等价的
//*++vp等价于vp=vp+1;*vp;
//*vp++是先使用指针指向的值,然后指针自增
//*++vp是先让指针自增,然后使用指针指向的值

//*vp++和(*vp)++是不等价的
//(*vp)++是先解引用指针,然后让解引用的值自增
//*vp++等价于*(vp);vp=vp+1;

//int main()
//{
//	int arr[10] = { 0 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	//指针的方式初始化数组元素
//	//for (int i = 0; i < sz; i++)
//	//{
//	//	*(arr + i) = i;
//	//}
//	////数组下标的方式初始化数组元素
//	//for (int i = 0; i < sz; i++)
//	//{
//	//	arr[i] = i;
//	//}
//	int* pa = arr;
//	for (int i = 0; i < sz; i++)
//	{
//		//*(pa + i) = i;
//		*pa++ = i;
//	}
//	return 0;
//}

//int main()
//{
//	int arr[10] = { 0 };
//	cout << &arr[9] - &arr[0] << endl; //9   &arr[0] - &arr[9] = -9
//	//指针-指针的结果是两个指针之间相隔的元素个数
//	return 0;
//}


#include<string.h>
//
//int my_strlen(const char* str)
////使用const是因为函数不会修改str指向的内容,而接受的实参是一个字符串常量,字符串常量存放在只读区,不能被修改,当使用
////数组存放字符串时,数组里面的字符可以被修改,但是函数内部不会修改字符串内容,所以使用const修饰指针参数
//{
//	int count = 0;
//	while (*str != '\0')
//	{
//		count++;
//		str++;
//	}
//	return count;
//}

int my_strlen(const char* str)
{
	char* str_start = (char*)str;
	while (*str != '\0')
	{
		str++;
	}
	return str - str_start;
}
int main()
{
	int len = my_strlen("hello");//这里传递的是常量字符串"hello",存放在只读区,
	                //如果函数声明是int my_strlen(char* str),则会报错,因为不能将const char*转换为char*
	cout << "len = " << len << endl;
	return 0;
}