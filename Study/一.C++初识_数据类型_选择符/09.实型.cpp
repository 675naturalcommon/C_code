#include<iostream>
using namespace std;
int main()
{
    //1.单精度 float
    //2.双精度 double
    float f1 = 3.14f;  //加f:默认情况下编译器会把小数认为是双精度,如果前面是float类型的话,则会有一步双精度到单精度的转换,会增加工作量

    cout << "f1 = " << f1 <<endl;

    double f2 = 3.14;
    cout << "f2 = " << f2 <<endl;

    //默认情况下输出一位小数,会输出六位有效数字,比如3.1415926会输出3.14159

    //统计float和double占用内存空间大小

    cout << "float占用内存空间大小:" << sizeof(float) <<endl;   //4字节
    cout << "double占用内存空间大小:" << sizeof(double) <<endl; //8字节

    //科学计数法
    float f3 = 3e2;
    cout << "f3 = " << f3 <<endl;

    float f4 = 3e-2;
    cout << "f4 = " << f4 <<endl;

    system("pause");
    return 0;
}