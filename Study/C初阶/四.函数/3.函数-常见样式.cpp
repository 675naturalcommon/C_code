#include <iostream>

using namespace std;
//函数的四种样式
//1.无参无返
void test01()
{
    cout << "this is test01!" << endl;
}
//2.有参无返
void test02(int a)
{
    cout << "this is test02 a = " << a << endl;
}
//3.无参有返
int test03()
{
    cout << "This is test03!" << endl;
    return 1000;
}
//4.有参有返
int main()
{
    //无参无返的函数调用
    test01();
    //有参无返的函数调用
    test02(100);
    //无参有返的函数调用
    int num1 = test03();
    cout << "num1 = " << num1 << endl;
    //有参有返的函数调用
    //两个整数相加的值传递
    return 0;
}