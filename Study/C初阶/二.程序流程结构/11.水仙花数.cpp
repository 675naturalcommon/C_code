#include <iostream>

using namespace std;

int main()
{
    //水仙花数是一个三位数,它的每位数字的三次幂之和等于它本身
    int num = 100;
    do
    {
        /* code */
        int a = num % 10;         //取个位
        int b = (num / 10) % 10;  //取十位
        int c = num / 100;        //取百位
        if(a*a*a+b*b*b+c*c*c == num)
        {
            cout << num << "是水仙花数" << endl;
        }
        num ++;
    } while (num >= 100 && num <= 999);

    return 0;
}