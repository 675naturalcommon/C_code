#include <iostream>

using namespace std;

// 堆区
// 由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收
// 在c++中主要利用new来开辟内存,利用delete来释放内存

int *func()
{
    // 利用new关键字 将数据开辟到堆区
    int *p = new int(100);
    return p;
}

int main()
{
    int *p = func();
    cout << *p << endl;

    return 0;
}