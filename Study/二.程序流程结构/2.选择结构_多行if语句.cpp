#include <iostream>

using namespace std;

int main()
{
    //1.用户输入分数
    int score = 0;
    cout << "请输入一个分数:";
    cin >> score;
    //2.打印用户输入的分数
    cout << "您输入的分数是:" << score << endl;
    //3.判断分数是否大于600,如果大于,那么输出
    if (score > 600)
    {
        cout << "恭喜您考上了一本大学" << endl;
    }
    else
    {
        cout << "您未考上一本大学" << endl;
    }
    return 0;
}