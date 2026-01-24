#include <iostream>

using namespace std;

int main()
{
    //switch语句
    //给电影进行打分
    //10~9 经典
    //8~7 精品
    //6~5 一般
    //0~4 垃圾

    //1.提示用户给电影评分
    cout << "请输入电影的评分：";
    //2.用户开始进行打分
    int score;
    cin >> score;
    cout << "您的评分是：" << score << endl;
    //3.根据评分进行判断
    switch (score)
    {
    case 10:
    case 9:
        cout << "您认为是经典电影" << endl;
        break;
    case 8:
    case 7:
        cout << "您认为是精品电影" << endl;
        break;
    case 6:
    case 5:
        cout << "您认为是一般电影" << endl;
        break;
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        cout << "垃圾" << endl;
        break;
    default:
        cout << "输入错误" << endl;
        break;

    }

    //if和switch的区别
    //switch缺点:
    //1.只能判断整数或者是字符型的变量，不能判断浮点数,不可以是一个区间
    //switch优点:
    //代码清晰,执行效率高

    return 0;
}