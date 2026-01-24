#include <iostream>

using namespace std;

int main()
{
    int count = 1;
    int count1 = 1;
    cout << "  ";
    while(count <= 10)
    {
        cout << count << " ";
        count ++;
    }
    cout << endl;
    //利用嵌套循环实现星图
    for (int j = 0; j < 10; j++)
    {
        if(count1 == 10)
        {
            cout << count1;
        }
        else
        {
            cout << count1 << " " ;
        }
        for (int i = 0; i < 10; i++)
        {
        /* code */
        cout << "* ";
        }
        cout << endl;
        count1 ++;

    }

    //打印一行星图
    return 0;
}