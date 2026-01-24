#include <iostream>

using namespace std;

int main()
{
    //continue语句的作用是跳过当前循环的未执行语句，直接开始下一轮循环。
    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0)
        {
            continue;//跳出当前循环，直接开始下一轮循环。
        }
        cout << i << " ";
    }
    cout << endl;
    return 0;
}