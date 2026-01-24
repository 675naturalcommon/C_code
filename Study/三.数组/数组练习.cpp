#include <iostream>
using namespace std;

int main() {
//练习1:五只小猪称体重
//在一个数组中记录了五只小猪的体重,如:int weight[5] = {100, 120, 110, 130, 125};
//找出并打印最重的小猪体重
    int weight[5] = {100, 120, 110, 130, 125};
    int max_weight = weight[0];
    for(int i=0; i<5; i++)
    {
        if(weight[i] > max_weight)
        {
            max_weight = weight[i];
        }
    }
    cout << "The heaviest pig has a weight of " << max_weight << " kg." << endl;


//练习2:数组元素逆置
//在一个数组中记录了10个整数,如:int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//将数组中的元素逆置,如:arr[0]变为arr[9], arr[1]变为arr[8], arr[2]变为arr[7], 以此类推...
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "原数组元素为: ";
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        cout << arr[i] << " ";
    }
    for(int i=0; i<5; i++)
    {
        int temp = arr[i];
        arr[i] = arr[9-i];
        arr[9-i] = temp;
    }
    cout << endl;
    cout << "逆置后数组元素为: ";
    for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}