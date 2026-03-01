#include <iostream>

using namespace std;

int global_var = 10; //全局变量
int global_vbr = 20;

//const修饰的全局变量
const int const_var = 10;
const int const_vbr = 20;

int main()
{

    //创建普通局部变量
    int a = 10;
    int b = 10;
    cout << &a << endl; //输出a的地址
    cout << &b << endl; //输出b的地址
    cout << &global_var << endl; //输出全局变量的地址
    cout << &global_vbr << endl; //输出全局变量的地址

    //创建静态局部变量
    static int c = 10;//在普通变量的前面加上static关键字
    static int d = 20;
    cout << &c << endl; //输出c的地址
    cout << &d << endl; //输出d的地址

    //常量
    //字符串常量
    //双引号括起来的字符串都是字符串常量
    cout << &"Hello, world!" << endl;

    //const修饰的变量
    //const修饰的全区变量,const修饰的局部变量
    cout << &const_var << endl; //输出const_var的地址
    cout << &const_vbr << endl; //输出const_vbr的地址

    const int e = 10;
    const int f = 20;
    cout << &e << endl; //输出e的地址
    cout << &f << endl; //输出f的地址

    return 0;
}
