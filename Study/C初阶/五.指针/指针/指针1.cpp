
#include<iostream>
using namespace std;
//int main()
//{
//	int a = 10;//a是整形变量,占用四个字节的内存空间
//	int* pa = &a;
//	//pa是一个指针变量,用来存放地址的
//
//	//本质上指针就是地址
//	//口语中说的指针其实是指针变量,指针变量是用来存放地址的变量
//	char* pc = nullptr;
//	short* pi = NULL;
//	int* ps = nullptr;
//	double* pd = nullptr;
//	cout << "sizeof(pc) = " << sizeof(pc) << endl;
//	cout << "sizeof(pi) = " << sizeof(pi) << endl;
//	cout << "sizeof(ps) = " << sizeof(ps) << endl;
//	cout << "sizeof(pd) = " << sizeof(pd) << endl;
//
//	return 0;
//}

//x86 - 32位操作系统
//指针变量占用4个字节
//x64 - 64位操作系统
//指针变量占用8个字节


//指针类型的意义
//int main()
//{
//	int a = 0x11223344;
//	/*int* pa = &a;
//	*pa = 0;*/
//
//	char* pc = (char*) &a;
//	*pc = 0;
//
//	//结论:指针类型决定了指针在被解引用时访问几个字节
//	//如果是int*的指针,解引用访问四个字节
//	//如果是char*的指针,解引用访问一个字节
//	return 0;
//}

//int main()
//{
//	int a = 0x11223344;
//	int* pa = &a;
//	char* pc = (char*)&a;
//
//	cout << "pa = " << pa << endl;         //0019F720
//	cout << "pa + 1 = " << pa + 1 << endl; //0019F724
//
//	cout << "pc = " << (void*)pc << endl;  //0019F720
//	cout << "pc + 1 = " << (void*)(pc + 1) << endl;//0019F721
//
//	//结论
//	//指针的类型决定了指针+1,-1操作跳过几个字节
//	return 0;
//}