#include <iostream>

using namespace std;

//函数的声明,实现两个整形数字进行比较,返回较大的值,声明可以有多次,但函数的定义只能有一次
//定义
int max(int num1,int num2)
{
    return num1 > num2 ? num1:num2;
}
int main()
{
    int a = 10,b = 20;
    cout << "c = " << max(a,b);
    return 0;
}