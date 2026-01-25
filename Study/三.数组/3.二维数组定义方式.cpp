#include<iostream>
using namespace std;

int main()
{
    int arr[3][4] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12} }; // 定义方式1
    int arr2[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12}; // 定义方式2
    int arr3[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12}; // 定义方式3

    // 输出二维数组
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    // 输出二维数组
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<arr2[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    // 输出二维数组
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<arr3[i][j]<<" ";
        }
        cout<<endl;
    }
    
    return 0;
}