#include "SeqList.h"

// void SLTest01()
// {
//     SL s1;
//     InitList(&s1);
//     printf("Length = %d, Capacity = %d\n", s1.length, s1.capacity);
//     // 执行一些增删查改操作

//     // 尾插
//     InsertTail(&s1, 1);
//     InsertTail(&s1, 2);
//     InsertTail(&s1, 3);
//     InsertTail(&s1, 4);
//     InsertTail(&s1, 5);
//     SLprint(s1);
//     printf("Length = %d, Capacity = %d\n", s1.length, s1.capacity);

//     // // 头插
//     // // InsertHead(&s1, 6);

//     // // 头删
//     // DeleteHead(&s1);
//     // SLprint(s1);
//     // // 尾删
//     // DeleteTail(&s1);
//     // SLprint(s1);

//     printf("Length = %d, Capacity = %d\n", s1.length, s1.capacity);

//     DestroyList(&s1);
// }

void Test02()
{
    SL s1;
    InitList(&s1);

    // 尾插
    InsertTail(&s1, 1);
    InsertTail(&s1, 2);
    InsertTail(&s1, 3);
    InsertTail(&s1, 4);
    InsertTail(&s1, 5);
    SLprint(s1);

    // 在指定位置插入数据
    // InsertPos(&s1, 0, 420);
    // SLprint(s1);
    // InsertPos(&s1, s1.length, 450);
    // SLprint(s1);

    // 在指定位置删除数据
    // DeletePos(&s1, 0);
    // SLprint(s1);

    // 查找指定的数据
    // int find = SLFind(&s1, 1);
    // if (find < 0)
    // {
    //     printf("没有找到.\n");
    // }
    // else
    // {
    //     printf("找到了,在位置%d处.", find);
    // }

    SLFind(s1, 1);

    DestroyList(&s1);
}

int main()
{
    // SLTest01();
    Test02();
    return 0;
}