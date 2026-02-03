#include <iostream>

using namespace std;

int add(int num1,int num2)//加法函数,实现两个整形相加,并且返回相加值
{//num1和num2为形式参数,没有实际的值,简称形参
    return num1 + num2;
}
int main()
{
    int a = 10,b = 20;
    cout<<"两数相加和为:"<<add(10,20)<<endl;
    cout<<"两数相加和为:"<<add(a,b)<<endl;//a和b为实际参数,简称实参,当调用函数add的时候,a,b的值会传给num1和num2

    return 0;
}