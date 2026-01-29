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
