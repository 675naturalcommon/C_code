#include <iostream>

using namespace std;

// 栈区数据注意事项
// 栈区数据由编译器开辟,管理和释放
// 栈区不能返回局部变量的地址

int *func()
{
    int a = 10; // 局部变量存放在栈区,栈区的数据在函数执行完后自动释放
    return &a;  // 错误,栈区不能返回局部变量的地址
}

int main()
{
    int *p = func(); // 接受func的返回值
    cout << *p << endl;

    return 0;
}