#include <iostream>

using namespace std;

int main()
{
    int score = 0;
    cout << "请输入你的高考分数:";
    cin >> score;
    cout << "你的高考分数是:" << score << endl;
    if (score > 600)
    {
        cout << "你考上了一本大学" << endl;
        if (score > 650)
        {
            cout << "你考上了清华大学" <<endl;
        }
        else if (score > 700)
        {
            cout << "你考上了北京大学" << endl;
        }
        else
        {
            cout << "你考上了中国人民大学" << endl;
        }

    }
    else if(score > 500)
    {
        cout << "你考上了二本大学" << endl;
    }
    else if(score > 400)
    {
        cout << "你考上了三本大学" << endl;
    }
    else
    {
        cout << "您未考上本科大学" <<endl;
    }
    return 0;
}