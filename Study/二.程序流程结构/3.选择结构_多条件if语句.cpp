#include <iostream>

using namespace std;

int main()
{
    //选择结构 多条件 if语句
    //输入一个考试分数,如果大于600分,考上一本大学,屏幕输出
    //大于500分,考上二本大学,屏幕输出
    //大于400分,考上三本大学,屏幕输出
    //小于等于400分,未考上本科大学,屏幕输出

    //1.用户输入分数
    int score = 0;
    cout << "请输入您考的分数:";
    //2.提示用户输入的分数
    cin >> score;
    //3.判断
    if(score > 600)
    {
        cout << "恭喜您考上了一本" << endl;
    }
    else if (score > 500)
    {
        cout << "恭喜您考上了二本" << endl;
    }
    else if(score > 400)
    {
        cout << "恭喜您考上了三本" << endl;
    }
    else
    {
        cout << "很遗憾您没有考上本科大学" << endl;
    }


    return 0;
}