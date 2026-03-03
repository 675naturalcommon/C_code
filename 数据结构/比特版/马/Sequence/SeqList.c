#include "SeqList.h"

// 顺序表初始化
void InitList(SL *L)
{
    L->arr = 0;
    L->length = L->capacity = 0;
}

// 顺序表销毁
void DestroyList(SL *L)
{
    if (L->arr)
    {
        free(L->arr);
        L->arr = NULL;
    }
    L->length = L->capacity = 0;
}

void SLCheckCapacity(SL *L)
{
    if (L->capacity == L->length)
    {
        int Newcapacity = L->capacity == 0 ? 4 : L->capacity * 2;
        ElemType *NewArr = (ElemType *)realloc(L->arr, Newcapacity * sizeof(ElemType));
        if (!NewArr)
        {
            perror("realloc\n");
            return;
        }
        L->capacity = Newcapacity;
        L->arr = NewArr;
    }
}

// 尾插
void InsertTail(SL *L, ElemType e)
{
    // 判断指针是否合法,温柔的解决方式
    //  if(!L)
    //  {
    //      fprintf(stderr, "Invalid list pointer\n");
    //      return;
    //  }
    // assert暴力的解决方式,如果条件不满足,程序会直接崩溃,适合调试阶段使用
    assert(L);
    // if (L->length == L->capacity)
    // {
    //     // 判断L->capacity是否为0,如果为0那么接下来realloc内存分配会申请失败
    //     int newCapacity = L->capacity == 0 ? 4 : L->capacity * 2;
    //     // newArray为中间变量,如果分配失败,可以避免影响原数据,newCapacity是纯数字
    //     ElemType *newArray = (ElemType *)realloc(L->arr, newCapacity * sizeof(ElemType));
    //     // 判断newArray是否开辟成功
    //     if (!newArray)
    //     {
    //         perror("realloc"); // 没有开辟成功,返回错误信息
    //         return;
    //     }
    //     // 开辟成功
    //     L->arr = newArray;
    //     L->capacity = newCapacity;
    // }
    // 将上述代码封装成函数
    SLCheckCapacity(L);
    L->arr[L->length++] = e;
}

// 头插
void InsertHead(SL *L, ElemType e)
{
    assert(L);
    // 检查存储空间是否足够,不够分配内存
    SLCheckCapacity(L);
    for (int i = L->length; i >= 0; --i)
    {
        L->arr[i + 1] = L->arr[i];
    }
    L->arr[0] = e;
    L->length++;
}

// 打印数据
void SLprint(SL L)
{
    for (int i = 0; i < L.length; i++)
    {
        printf("%d ", L.arr[i]);
    }
    printf("\n");
}

// 删除尾部数据
void DeleteTail(SL *L)
{
    assert(L);
    // if(L->length == 0)
    // {
    //     return;
    // }
    assert(L->length);
    L->length--;
}

// 删除头部数据
void DeleteHead(SL *L)
{
    assert(L);
    assert(L->length);
    for (int i = 0; i < L->length - 1; i++)
    {
        L->arr[i] = L->arr[i + 1];
    }
    L->length--;
}

// 在指定位置插入数据
void InsertPos(SL *L, int pos, ElemType e)
{
    // 防止传入空指针
    assert(L);
    // 防止传入非法位置
    assert(pos >= 0 && pos <= L->length);
    // 检查存储空间是否足够,不够分配内存
    SLCheckCapacity(L);
    // 从pos位置包括pos开始,将数据往后移一格
    for (int i = L->length; i >= pos; i--)
    {
        L->arr[i + 1] = L->arr[i];
    }
    L->arr[pos] = e;
    L->length++;
}

// 在指定位置删除数据
void DeletePos(SL *L, int pos)
{
    // 防止传入指针为非法指针
    assert(L);
    // 防止传入非法位置
    assert(pos >= 0 && pos < L->length);
    for (int i = pos; i < L->length - 1; i++)
    {
        L->arr[i] = L->arr[i + 1]; // L->arr[length-2] = L->arr[length-1]
    }
    L->length--;
}

// 顺序表的查找
// int SLFind(SL *L, ElemType e)
// {
//     assert(L);
//     assert(L->length);
//     for (int i = 0; i < L->length; i++)
//     {
//         if (L->arr[i] == e)
//         {
//             // printf("%d在顺序表中下标为%d的位置", e, i);
//             return i;
//         }
//     }
//     // 没有找到
//     return -1;
// }

void SLFind(SL L, ElemType e)
{
    // assert(L);
    assert(L.length);
    for (int i = 0; i < L.length; i++)
    {
        if (L.arr[i] == e)
        {
            printf("%d在顺序表中下标为%d的位置", e, i);
            return;
        }
    }
    // 没有找到
    printf("没有找到\n");
}