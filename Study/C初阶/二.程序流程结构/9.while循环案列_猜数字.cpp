#include <iostream>
#include<ctime>
using namespace std;

int main()
{
    //系统随机生成一个1~100之间的整数,玩家进行猜测,如果猜错,提示玩家数字过大或过小
    //如果猜对恭喜玩家胜利,并且退出游戏


    srand(( unsigned int)time(NULL));
    //系统随机生成一个1~100之间的整数
    int num = rand() % 100 + 1; //rand()函数返回一个随机整数,范围是0~RAND_MAX,这里除以100后加1,得到1~100之间的随机整数,rand() % n + 1的意思是生成一个1~n之间的随机整数
    //cout << "系统随机生成的数字是: " << num << endl;

    //此处生成的随机数是伪随机数,程序每次运行时生成的随机数都一样,如果想让程序每次运行都生成不同的随机数,需要添加随机数种子

    //添加随机数种子  作用:利用系统时间作为随机数种子,使得每次运行程序生成的随机数都不一样
    srand(( unsigned int)time(NULL));

    //玩家进行猜测
    int guess;
    cout << "请输入你猜的数字: ";
    cin >> guess;

    while(num != guess)
    {
        if(guess > num)
        {
            cout << "你猜的数字太大了,请重新输入: ";
            cin >> guess;
        }
        else if(guess < num)
        {
            cout << "你猜的数字太小了,请重新输入: ";
            cin >> guess;
        }

    }
    //如果猜对,提示玩家恭喜你猜对了,并且退出游戏
    cout << "恭喜你猜对了,游戏结束!" << endl;
    //游戏结束
    return 0;
}

