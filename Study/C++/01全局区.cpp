#include <iostream>

using namespace std;

int main()
{

    //创建普通局部变量
    int a = 10;
    int b = 10;
    cout << &a << endl; //输出a的地址
    cout << &b << endl; //输出b的地址

    return 0;
}
