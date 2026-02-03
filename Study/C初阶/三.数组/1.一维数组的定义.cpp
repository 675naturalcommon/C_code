#include <iostream>

using namespace std;

int main()
{
    //数组
    /*
        数组的三种定义方式
        1.数据类型 数组名[数组长度]
        2.数据类型 数组名[数组长度] = {值1, 值2, 值3,..., 值n};
        3.数据类型 数组名[] = {值1, 值2, 值3,..., 值n};
    */
    //方式1
    int arr1[5]; //定义一个长度为5的整型数组
    //方式2
    int arr2[3] = {1, 2, 3}; //定义一个长度为3的整型数组，并初始化为{1, 2, 3}
    //方式3
    int arr3[] = {4, 5, 6}; //定义一个长度为3的整型数组，并初始化为{4, 5, 6}
    //输出数组元素
    cout << "arr1: ";
    for (int i = 0; i < 5; i++)
    {
        cout << arr1[i] << " ";
    }
    cout << endl;
    cout << "arr2: ";
    for (int i = 0; i < 3; i++)
    {
        cout << arr2[i] << " ";
    }
    cout << endl;
    cout << "arr3: ";
    for (int i = 0; i < 3; i++)
    {
        cout << arr3[i] << " ";
    }
    cout << endl;
    return 0;
}