#include<iostream>
using namespace std;
int main8()
{
    //sizeof关键字可以算出数据类型所占内存空间的大小
    short num1 = 10;
    cout << "short占用内存空间为:" << sizeof(short) <<endl;
    cout << "short占用内存空间为:" << sizeof(num1) <<endl;
    //整形结论
    //short < int <= long <= long long
    system("pause");
    return 0;
}