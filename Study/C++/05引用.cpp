#include <iostream>

using namespace std;

// int main()
// {
//     // 引用:给变量起别名
//     int a = 10;
//     // 定义一个引用,起别名为b,引用a
//     int &b = a;
//     cout << "a = " << a << endl;
//     cout << "b = " << b << endl;

//     // 通过引用修改a的值
//     b = 100;
//     cout << "a = " << a << endl;
//     cout << "b = " << b << endl;

//     // 引用必须初始化,引用一旦初始化后,就不能改变引用的对象
//     int c = 20;
//     b = c; // 这不是改变引用的对象,而是改变引用对象的值
//     cout << "a = " << a << endl;
//     cout << "b = " << b << endl;

//     int &b = c;
//     // int &c; // 错误,引用必须初始化
//     // int &d = a; // 正确,引用必须初始化
//     // int &e = b; // 正确,引用必须初始化
//     // int &f = 100; // 错误,引用必须初始化,不能引用常量
//     return 0;
// }

// 值传递
void swap01(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

// 地址传递
void swap02(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 引用传递
void swap03(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a = 10;
    int b = 20;
    swap01(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    swap02(&a, &b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    // 引用做函数参数
    swap03(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    // 常量引用
    const int &c = a;
    c = 100; // 错误,常量引用不能修改引用的对象的值,只能读取引用的对象的值,不能修改
    return 0;
}