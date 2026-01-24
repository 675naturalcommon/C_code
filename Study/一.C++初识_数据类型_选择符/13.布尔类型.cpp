#include<iostream>
using namespace std;
int main()
{
    //布尔数据类型代表真或假的值
    //true -- 真(本质是1)
    //false - 假(本质是0)
    //bool类型占一个字节的大小

    //1.创建布尔类型
    bool flag = true;
    cout << flag <<endl;  //输出1

    flag = false;
    cout << flag <<endl;  //输出0
    //2.查看布尔类型占据内存空间大小
    cout << "bool类型占据内存空间大小:" << sizeof(flag) <<endl;
    system("pause");
    return 0;

}

