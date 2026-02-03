#include<iostream>
using namespace std;

//结构是一些值的集合,这些值称为成员变量.结构的每个成员可以是不同类型的变量.
//结构的定义使用关键字struct,后面跟着结构的名称和大括号括起来的成员变量列表.结构定义的结尾有一个分号.

//struct peo
//{
//	char name[20];
//	char tele[12];
//	char sex[5];
//	int height;
//};
//
////struct peo
////{
////	char name[20];
////	char tele[12];
////	char sex[5];
////	int height;
////}p1, p2;//创建了两个结构体变量p1和p2,p1和p2都是peo类型的变量.而且是全局变量.
//
//struct st
//{
//	struct peo p;//结构体嵌套,结构体里面可以包含另一个结构体变量.
//   //但peo结构体必须在st结构体之前定义.
//	int num;
//	float score;
//};
//
//void print(peo* sp)
//{
//	//结构体指针 -> 访问成员变量使用箭头->
//	cout << "name: " << sp->name << endl;
//	cout << "tele: " << sp->tele << endl;
//	cout << "sex: " << sp->sex << endl;
//	cout << "height: " << sp->height << endl;
//
//	//此处用箭头的原因是传参得到的是地址
//}
//
//void print1(peo sp)//形参是对实参的一次临时拷贝
//{
//	//结构体变量 . 访问成员变量使用点.
//	cout << "name: " << sp.name << endl;
//	cout << "tele: " << sp.tele << endl;
//	cout << "sex: " << sp.sex << endl;
//	cout << "height:" << sp.height << endl;
//}
//int main()
//{
//	peo p1, p2;//创建了两个结构体变量p1和p2,p1和p2都是peo类型的变量.而且是局部变量.
//	struct peo p3;//也可以使用struct关键字来定义结构体变量.
//	struct peo p4 = { "Alice", "12345678901", "F", 165 };//定义结构体变量的同时进行初始化.
//
//	struct st s1 = { {"张三","1564237869","M",188},66,77.0f };//定义结构体变量s1,类型是st.
//
//	cout << "s1.p.name: " << s1.p.name << endl;
//
//	print(&p4);
//	return 0;
//}


//结构体传参


//写一个函数返回参数中二进制1的个数
//int count_of_1(unsigned int num)
//{
//    int count = 0;
//    while(num > 0)
//    {
//        if(num % 2 == 1)
//        {
//            count ++;
//        }
//        num = num / 2;
//    }
//    return count;
//}

// int count_of_1(unsigned int num)
// {
//     int count = 0;
//     // while(num > 0)
//     // {
//     //     if(num & 1 == 1)//与运算,判断最后一位是否为1
//     //     {
//     //         count ++;
//     //     }
//     //     num = num >> 1;//右移一位
//     // }
//     for(int i = 0; i < 32; i++)
//     {
//         if(((num >> i) & 1) == 1 )
//         count ++;
//     }
//     return count;
// }

//int count_of_1(unsigned int num)
//{
//    int count = 0;
//    while (num)
//    {
//        num = num & (num - 1);//将最右边的1变成0
//        count++;
//    }
//    return count;
//}
//
//
// 判断一个数是否是2的n次方
// 2^0=1  1
// 2^1=2  10
// 2^2=4  100
// 2^3=8  1000
//
// if((num & (num - 1)) == 0)
// {
//    .....
// }
//
//
//int main()
//{
//    int num = 0;
//    cin >> num;
//    int count = count_of_1(num);
//    cout << count;
//    return 0;
//}

//编写一个函数,将一个字符串中的大写字母转换为小写字母,小写字母转换为大写字母,其他字符不变.
//void str_convert(char* str)
//{
//	while(*str != '\0')
//	{
//		if(*str >= 'a' && *str <= 'z')
//		{
//			*str = *str - ('a' - 'A');
//		}
//		else if(*str >= 'A' && *str <= 'Z')
//		{
//			*str = *str + ('a' - 'A');
//		}
//		str++;
//	}
//}
//
//int main()
//{
//	char arr[] = "Hello, World! 123";
//	str_convert(arr);
//	cout << arr << endl;
//	return 0;
//}


//两个int(32位)数,交换两个数的值,要求不能使用临时变量.
//void swap(int& a, int& b)
//{
//	a = a ^ b;
//	b = a ^ b;
//	a = a ^ b;
//}
//
//int main()
//{
//	int a = 10;
//	int b = 20;
//	swap(a, b);
//	cout << "a: " << a << endl;
//	cout << "b: " << b << endl;
//	return 0;
//}
//
////另一种方法
//void swap(int& a, int& b)
//{
//	a = a + b;
//	b = a - b;
//	a = a - b;
//}


//两个int(32)位整数m和n的二进制表示中,有多少个位(bit)不同?
//  int count_bits(int m, int n)
// {
// 	int count = 0;
// 	int xor_result = m ^ n;//异或运算,不同为1,相同为0
// 	while(xor_result)
// 	{
// 		xor_result = xor_result & (xor_result - 1);//将最右边的1变成0
// 		count++;
// 	}
// 	return count;
//  }

//



//获取一个整数二进制序列中所有的偶数位和奇数位,分别打印出二进制序列
//int main()
//{
//	int i = 0;
//	int num;
//	cin >> num;
//
//	//获取奇数位
//	for(i = 0; i <= 30; i+=2)
//	{
//		cout << ((num >> i) & 1) << " ";
//	}
//	cout << endl;
//	//获取偶数位
//	for(i = 1; i <= 31; i+=2)
//	{
//		cout << ((num >> i) & 1) << " ";
//	}
//	return 0;
//}

//编写一个函数,实现字符串反转.例如:输入"abcdef",输出"fedcba"
//void reverse_string(char* str)
//{
//	char* left = str;
//	char* right = str;
//	//移动right指针到字符串末尾
//	while(*right != '\0')
//	{
//		right++;
//	}
//	right--;//指向最后一个字符
//	//交换left和right指针所指向的字符
//	while(left < right)
//	{
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//}
//
//int main()
//{
//	char arr[] = "abcdef";
//	reverse_string(arr);
//	cout << arr << endl;
//	return 0;
//}

//编写一个函数,实现字符串的左旋操作.例如:输入"abcdef"和2,输出"cdefab"
//void left_rotate_string(char* str, int n)
//{
//	//计算字符串长度
//	int len = 0;
//	char* p = str;
//	while(*p != '\0')
//	{
//		len++;
//		p++;
//	}
//	n = n % len; //防止n大于字符串长度
//	//反转前n个字符
//	char* left = str;
//	char* right = str + n - 1;
//	while(left < right)
//	{
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//	//反转剩余字符
//	left = str + n;
//	right = str + len - 1;
//	while(left < right)
//	{
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//	//反转整个字符串
//	left = str;
//	right = str + len - 1;
//	while(left < right)
//	{
//		char temp = *left;
//		*left = *right;
//		*right = temp;
//		left++;
//		right--;
//	}
//}
//
//int main()
//{
//	char arr[] = "abcdef";
//	int n = 2;
//	left_rotate_string(arr, n);
//	cout << arr << endl;
//	return 0;
//}


