#include <iostream>

using namespace std;

int main()
{
    for (int i = 1; i <= 100; i++)
    {
        /* code */
        if(i % 10 == 7 || i / 10 % 10 == 7 || i % 7 == 0)
        {
            cout << i << " 敲桌子" << endl;
        }
        else
        {
            cout << i << endl;
        }
    }
    return 0;
}