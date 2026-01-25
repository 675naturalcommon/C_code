#include "swap.h"
#include <iostream>
using namespace std;

//函数的定义
void swap(int num1, int num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
    cout << "交换后的值为:num1 = " << num1 << "   " << "num2 = " << num2 << endl;
}
