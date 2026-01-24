#include <iostream>

using namespace std;

int main()
{
    //do while语句
    //在屏幕上输出0~9
    int num = 0;
    do
    {
        cout << num << endl;
        num ++;
    } while (num < 10);

    //do..while循环和while循环的区别在于,do..while可以先执行一次循环语句
    return 0;
}