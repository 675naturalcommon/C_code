#include <iostream>

using namespace std;

int main()
{
    //三目运算符
    //创建三个变量a,b,c
    //将a和b作比较,将变量大的值赋给c
    int a,b,c;
    a = 10;
    b = 20;
    c = (a > b ? a : b);
    cout << c << endl;
    //在c++中三目运算符返回的是变量,可以继续赋值
    (a > b ? a : b) = 100;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}