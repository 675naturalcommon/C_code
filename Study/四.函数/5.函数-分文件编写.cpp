#include <iostream>
#include"swap.h"
using namespace std;

//函数分文件编写有四个步骤
//1.创建后缀名为.h的头文件
//2.创建后缀名为.cpp的源文件
//3.在头文件中写函数的声明
//4.在源文件中写函数的定义

//实现两个数字交换的函数

//函数定义
/* void swap(int num1,int num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
    cout << "交换后的值为:num1 = " << num1 << "   " << "num2 = " << num2 << endl;
} */
int main()
{
    int a = 10;
    int b = 20;
    swap(a,b);
    return 0;
}