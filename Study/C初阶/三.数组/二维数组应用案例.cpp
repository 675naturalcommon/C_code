#include <iostream>
#include<string>
using namespace std;

int main()
{
    //二维数组应用案例--考试成绩
    //1.创建二维数组
    int scores[3][3] =
    {
        {100,100,100},
        {98,97,95},
        {94,92,99}
    };
    string names[3] = {"张三","李四","王五"};
    //2.统计每个人的总和分数
    for(int i = 0; i < 3; i++)
    {
        int sum = 0; //统计分数总和变量
        for(int j = 0; j < 3; j++)
        {
            sum += scores[i][j];
            //cout << scores[i][j] << " ";
        }
        cout << names[i] << "的考试分数是" << sum << endl;
        //cout << "第一个人的总分为:" << sum << endl;
        //cout << endl;
    }
    cout << endl;
    return 0;
}