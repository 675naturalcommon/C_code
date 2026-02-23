#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fseek()函数的使用
//
// int main()
// {
//     FILE *pf = fopen("data2.txt", "r");
//     if (pf == NULL)
//     {
//         perror("fopen");
//         return 1;
//     }
//     // 读文件
//     char ch = fgetc(pf);
//     printf("%c\n", ch);

//     // fseek(pf, 6, SEEK_SET);
//     // fseek(pf, 5, SEEK_CUR);
//     fseek(pf, -3, SEEK_END);

//     ch = fgetc(pf);
//     printf("%c\n", ch);
//     fclose(pf);
//     pf = NULL;

//     return 0;
// }

// int main()
// {
//     FILE *pf = fopen("data2.txt", "w");
//     if (pf == NULL)
//     {
//         perror("fopen");
//         return 1;
//     }
//     // 写文件
//     fputs("abcdefghi", pf);
//     fseek(pf, -3, SEEK_END);

//     fputc('x', pf);

//     fseek(pf, 0, SEEK_END);
//     int ret = ftell(pf);
//     printf("ftell: %d\n", ret);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }

// rewind()函数的使用
// 让文件指针的位置回到起始位置
// int main()
// {
//     FILE *pf = fopen("data2.txt", "w");
//     if (pf == NULL)
//     {
//         perror("fopen");
//         return 1;
//     }
//     // 写文件
//     fputs("abcdefghi", pf);
//     fseek(pf, -3, SEEK_END);

//     fputc('x', pf);

//     fseek(pf, 0, SEEK_END);
//     int ret = ftell(pf);
//     printf("文件的字节数:ftell: %d\n", ret);
//     rewind(pf); // 文件指针回到文件的起始位置
//     // fseek(pf, 0, SEEK_SET);//和rewind()效果一样
//     fputc('q', pf);

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }

// fflush()函数的使用
// int fflush(FILE *stream);
// 作用：强制将缓冲区中的数据立即写入文件，并清空缓冲区。
// 一般情况下，系统会自动调用fflush()函数，因此一般不需要手动调用。
// 对输出流（如stdout、stderr）调用fflush()，可以将缓冲区中的数据立即写入文件，并刷新缓冲区。

#include <windows.h>
// int main()
// {
//     FILE *pf = fopen("text.txt", "w");
//     fputs("hello world", pf); // 先将代码放在输出缓冲区
//     printf("睡眠10秒-已经写数据了,打开test.txt文件,发现文件没有内容\n");
//     Sleep(10000); // 睡眠10秒
//     printf("刷新缓冲区\n");
//     fflush(pf); // 刷新缓冲区时,才将输出缓冲区的数据写到文件中(磁盘)
//     // fflush在高版本的VS中不能使用
//     printf("睡眠10秒-已经刷新缓冲区了,打开test.txt文件,发现文件有内容\n");
//     Sleep(10000); // 睡眠10秒
//     fclose(pf);   // 关闭文件时,也会刷新缓冲区
//     pf = NULL;

//     return 0;
// }

// int main()
// {
//     FILE *pf = fopen("text.txt", "w+");
//     if (pf == NULL)
//     {
//         perror("fopen");
//         return 1;
//     }
//     // 写文件
//     fputs("hello world", pf);
//     fflush(pf); // 刷新缓冲区

//     // 读文件
//     // fseek(pf, 0, SEEK_SET);
//     rewind(pf); // 文件指针回到文件的起始位置,和fseek(pf, 0, SEEK_SET)效果一样
//     char ch = fgetc(pf);
//     printf("%c\n", ch);
//     // hello world
//     fseek(pf, 2, SEEK_CUR);
//     fputs("xxx", pf);   // helxxxworld
//     //  char ch;
//     //  while ((ch = fgetc(pf)) != EOF)
//     //  {
//     //      printf("%c", ch);
//     //  }

//     fclose(pf);
//     pf = NULL;

//     return 0;
// }