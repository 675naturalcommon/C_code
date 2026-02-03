#include<iostream>
using namespace std;


//int main()
//{
//	int a = 10;
//	int* p = &a;    //int *p中的*说明p是一个一级指针变量,用来存放整形变量的地址,int表明p指向的地址存放的是整形数据
//	int** ppa = &p; //ppa是一个二级指针变量,用来存放一级指针变量p的地址
//	//int **ppa中的**说明ppa是一个二级指针变量,靠近ppa的*能表明ppa是一个指针,
//	//用来存放一级指针变量的地址,int*表明ppa指向的地址存放的是整形指针变量的
//	return 0;
//}


//指针数组
//存放指针的数组就是指针数组

int main()
{
	//int a = 10;
	//int b = 20;
	//int c = 30;
	//
	//int* pa = &a;
	//int* pb = &b;
	//int* pc = &c;

	////parr就是存放指针的数组

	//int* parr[10] = {&a,&b,&c};
	//for (int i = 0; i < 3; i++)
	//{
	//	cout << *(parr[i]) << " "; //10 20 30
	//}
	/*int arr[3][4] = {
		{1,2,3,4},
		{2,3,4,5},
		{3,4,5,6}
	};
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for(j=0;j<4;j++)
		{
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}*/

//	int arr1[4] = { 1,2,3,4 };
//	int arr2[4] = { 5,6,7,8 };
//	int arr3[4] = { 9,10,11,12 };
//
//	int* parr[3] = { arr1,arr2,arr3 };
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			//cout << *(parr[i] + j) << " ";
//			//cout << parr[i][j] << " ";//当i等于零时,相当于访问arr1数组的元素,[j]是在这个基础上进行便宜
//			//cout << parr[i] + j << " ";//打印的是每一个元素的地址
//			//parr[i]第i个一维数组的首地址,+j相当于在这个地址上偏移j个整形元素的字节数
//			cout << parr + i + j << " ";//打印的是地址,但是会发生越界,当i+j大于等于3时,就会访问越界
//
//
//
//		}
//		cout << endl;
//	}
//
//	return 0;
//}