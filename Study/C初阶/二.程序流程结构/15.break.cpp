#include <iostream>

using namespace std;

int main()
{
    //break使用场景

    //1.switch语句中使用break
    // cout << "请选择副本难度" << endl;
    // cout << "1.简单" << endl;
    // cout << "2.中等" << endl;
    // cout << "3.困难" << endl;
    // int level;  //创建选择结果的变量
    // cin >> level;//等待用户输入
    // switch (level)
    // {
    // case 1:
    //     cout << "你选择了简单副本" << endl;
    //     break;
    // case 2:
    //     cout << "你选择了中等副本" << endl;
    //     break;
    // case 3:
    //     cout << "你选择了困难副本" << endl;
    //     break;
    // default:
    //     cout << "你没有选择任何副本难度" << endl;
    //     break;
    //}

    //2.循环语句中使用break
    // for(int i=0;i<10;i++)
    // {
    //     cout << i << " ";
    //     if(i == 5)
    //     {
    //         break;
    //     }
    // }

    //3.嵌套循环语句中使用break
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if (j == 5)
            {
                /* code */
                break;
            }

            cout << "*" << " ";
        }
        cout << endl;
    }
    return 0;
}