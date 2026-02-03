#include<iostream>
using namespace std;

//常量的作用:用于记录程序中不可更改的数据
	//两种方式
	//#define 宏常量: define 常量名 常量值  (通常在文件上方定义,表示一个常量)
	//const 修饰的变量  const 数据类型 常量名 = 常量值
	//                  在变量定义前加关键字const,修饰该变量为常量,不可修改

#define Day 7
int main4()
{
	//Day = 14;  //错误,表达式必须是可以修改的左值
	cout << "一周有" << Day << "天" << endl;

	const int month = 12;
	//month = 24; //错误,定义常量第二种方式,通过使用关键字const
	cout << "一年有" << month << "月" << endl;
	system("pause");
	return 0;
}

