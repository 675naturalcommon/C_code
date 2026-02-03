#include<iostream>
using namespace std;
int main()
{
    //字符型变量只能用来显示单个字符  char
    //在显示字符型变量时,用单引号将其括起来,不能用双引号
    //char ch = 'a'
    //单引号里只能有一个字符,不能有多个字符,也就是不能有字符串

    //1.字符型变量创建方式
    char ch = 'a';
    cout << ch << endl;
    //2.字符型变量所占内存大小
    cout << "字符型变量所占内存空间:" << sizeof(char) <<endl;
    //3.字符型变量常见错误
    //char ch2 = "a";  //创建字符型变量时,要用单引号
    //char ch2 = 'abcdef';  //创建字符型变量时,单引号内只能有一个字符,有溢出
    //cout << "ch2 = " << ch2 <<endl;

    //4.字符型变量所占的ASCII码
    cout << int(ch) <<endl;
    system ("pause");
    return 0;
}