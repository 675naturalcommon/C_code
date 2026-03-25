#include <iostream>

using namespace std;

// 1 new的基本语法
int *func()
{
    // 利用new开辟一个int类型的变量,并且初始化为100

    // new返回的是一个指针,指向开辟的内存空间,指针的类型和开辟的内存空间的类型一致
    int *p = new int(100);
    return p;
}
void test01()
{
    int *p = func();
    cout << *p << endl;

    // 堆区的数据 由程序员管理开辟和释放,如果程序员不释放,程序结束时由操作系统回收
    //  释放内存.利用delete关键字会释放new开辟的内存,并且调用析构函数
    delete p;
}
// 2 在堆区利用new开辟数组
void test02()
{
    // 利用new开辟一个int类型的数组,数组长度为5
    int *arr = new int[5];
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i + 1;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    // 释放内存,利用delete[]关键字会释放new开辟的数组内存,并且调用析构函数
    delete[] arr;
}
int main()
{
    test01();
    test02();
    return 0;
}