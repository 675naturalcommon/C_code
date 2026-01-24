#include <iostream>

using namespace std;

int main()
{
    //逻辑运算符 非!真变假,假变真
    int a = 10;
    cout << !a << endl;
    cout << !!a << endl;
    //逻辑运算符 与 && 都为真时才为真
    int b = 10;
    cout << (a && b) << endl;
    cout << (!a && b) << endl;
    //逻辑运算符 或 || 有真即为真
    cout << (!a || b) << endl;

    return 0;
}