#include<iostream>
using namespace std;
int main()
{
    //加减乘除
    int a1 = 10;
    int b1= 10;
    cout << "a1 + b1 = " << a1 + b1 << endl;
    cout << "a1 - b1 = " << a1 - b1 << endl;
    cout << "a1 * b1 = " << a1 * b1 << endl;
    cout << "a1 / b1 = " << a1 / b1 << endl;//两个整数相除结果依然是整数,即使真正的结果是小数,也会只保留小数点前数字

    int a2 = 10, b2 = 20;
    cout << "a2 / b2 = " << (float)a2/b2 << endl;  //强制类型转换

    int a3 = 10 , b3 = 0;
   // cout << "a3 / b3 = " << a3 / b3 << endl;  两个整数相除,结果一定不能为0

   //两个小数相除

   float f1 = 0.5f;
   float f2 = 0.22f;
   cout << f1 / f2 <<endl;//两个小数可以相除,运算的结果依然是小数
    system("pause");
    return 0;
}