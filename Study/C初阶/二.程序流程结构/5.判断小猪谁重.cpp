#include <iostream>

using namespace std;

int main()
{
    //三只小猪称体重,判断谁最重
    float pig1 , pig2 , pig3;
    cout << "请输入三只小猪的体重" << endl;
    cout << "小猪1的体重是:" ;
    cin >> pig1;
    cout << "小猪2的体重是:" ;
    cin >> pig2;
    cout << "小猪3的体重是:" ;
    cin >> pig3;
    if(pig1>pig2)
    {
        if(pig1 > pig3)
        {
            cout << "小猪1的体重最重" << endl;
        }
        else
        {
            cout << "小猪3的体重最重" << endl;
        }

    }
    else
    {
        if(pig2 > pig3)
        {
            cout << "小猪2的体重最重" << endl;
        }
        else
        {
            cout << "小猪3的体重最重" << endl;
        }

    }
    return 0;
}