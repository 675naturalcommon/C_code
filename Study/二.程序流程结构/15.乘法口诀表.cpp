#include <iostream>

using namespace std;

int main()
{
    for(int i = 1;i <= 9;i++)//i表示行数
    {
        //cout << i << endl;
        for(int j = 1;j <= i;j++)//列数小于等于行数,j表示列数
        {
            cout << j << "*" << i << "=" << j*i << " ";
        }
        cout << endl;
    }
    return 0;
}