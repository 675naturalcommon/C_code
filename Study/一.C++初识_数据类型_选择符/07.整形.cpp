#include<iostream>
using namespace std;
int main7()
{
    //区别在于所占内存空间不同

    //整形
    //1.短整型     short 2字节     表示范围(-2^15~2^15-1)  -32768-32767
    //short num1 = 10;
    short num1 = 32768;

    //2.整形       int   4字节     表示范围(-2^31~2^31-1)
    int num2 = 10;

    //3.长整型     long  Windows下4字节,Linux下32位为4字节,64位为8字节  表示范围(-2^31~2^31-1)
    long num3 = 10;

    //4.长长整形   long long 8字节  表示范围(-2^63~2^63-1)
    long long num4 = 10;

    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
    cout << "num3 = " << num3 << endl;
    cout << "num4 = " << num4 << endl;

    system("pause");
    return 0;
}