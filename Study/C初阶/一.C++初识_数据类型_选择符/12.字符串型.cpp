#include<iostream>
using namespace std;
int main()
{
    //1.c风格字符串   char 变量名[] = "字符串值";
    //注意事项,变量名后要加中括号[]
    //注意事项2,等号后面要加双引号
    char str1[] = "Hello World";
    cout << str1 <<endl;
    //2.c++风格字符串 string 变量名 = "字符串值";
    string str2 = "Hello World";
    cout << str2 <<endl;
    system("pause");
    return 0;
}