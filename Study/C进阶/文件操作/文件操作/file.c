#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int main()
//{
//	int a = 10000;
//
//	return 0;
// }

// int main()
//{
//	FILE* fp = fopen("data.txt", "r");
//	if (fp == NULL)
//	{
//		perror("fopen");
//		return 1;
//	}
//	int i = 0;
//	for (i = 0; i < 10; i++)
//	{
//		int c = fgetc(fp);
//		if (c == EOF)
//		{
//			if (feof(fp))
//			{
//				printf("End of file reached.\n");
//			}
//			else if (ferror(fp))
//			{
//				perror("fgetc");
//				fclose(fp);
//				return 1;
//			}
//		}
//		else
//		{
//			fputc(c, stdout);
//		}
//	}
//
//	//关闭文件
//	fclose(fp);
//	fp = NULL;//避免野指针
//	return 0;
// }

// 以写的形式打开文件,再去读文件,就会发生错误
// int main()
//{
//	FILE *fp = fopen("data.txt", "w");
//	if (fp == NULL)
//	{
//		perror("fopen\n");
//		return 1;
//	}
//	int c = fgetc(fp);
//	if (c == EOF)
//	{
//		if (feof(fp))
//		{
//			printf("End of file reached.\n");
//		}
//		else if (ferror(fp))
//		{
//			perror("fgetc");
//			fclose(fp);
//			return 1;
//		}
//	}
//	else
//	{
//		fputc(c, stdout);
//	}
//
//	// 关闭文件
//	fclose(fp);
//	fp = NULL; // 避免野指针
//	return 0;
//}

// fputs,不包含结尾的'\0'
// int main()
//{
//	FILE* fp = fopen("data.txt", "w");
//	if (fp == NULL)
//	{
//		perror("fopen\n");
//		return 1;
//	}
//	// 写入字符串到文件
//	char str[] = "Hello, World!";
//	fputs(str, fp);//遇到'\0'就停止了
//	fputc('\n', fp);//换行
//	fputs("abc", fp);
//	// 关闭文件
//	fclose(fp);
//	fp = NULL; // 避免野指针
//	return 0;
// }

// fgets,会把'\n'也读入到字符串中
// int main()
//{
//	FILE* fp = fopen("data.txt", "r");
//	if (fp == NULL)
//	{
//		perror("fopen\n");
//		return 1;
//	}
//	char buffer[100];
//	while (fgets(buffer, sizeof(buffer), fp) != NULL)
//	{
//		printf("%s", buffer);
//	}
//	// 关闭文件
//	fclose(fp);
//	fp = NULL; // 避免野指针
//	return 0;
// }

// fprintf
// struct Stu
// {
// 	char name[20];
// 	int age;
// 	float score;
// };
// int main()
// {
// 	struct Stu s = {"Tom", 20, 80.5};

// 	FILE *fp = fopen("data.txt", "w");
// 	if (fp == NULL)
// 	{
// 		perror("fopen\n");
// 		return 1;
// 	}

// 	// 写文件
// 	// printf("name: %s, age: %d, score: %.2f\n", s.name, s.age, s.score);
// 	fprintf(fp, "name: %s, age: %d, score: %.2f\n", s.name, s.age, s.score);
// 	// fprintf(stdout, "name: %s, age: %d, score: %.2f\n", s.name, s.age, s.score);

// 	// 关闭文件
// 	fclose(fp);
// 	fp = NULL; // 避免野指针

// 	return 0;
// }

// fscanf
// struct Stu
// {
// 	char name[20];
// 	int age;
// 	float score;
// };
// int main()
// {
// 	struct Stu s = {0};

// 	FILE *fp = fopen("data.txt", "r");
// 	if (fp == NULL)
// 	{
// 		perror("fopen\n");
// 		return 1;
// 	}

// 	// 读文件
// 	// 注意：%s会读取到逗号，所以使用%[^,]来读取直到逗号
// 	// %.2f在scanf中无效，应该使用%f
// 	int ret = fscanf(fp, "name: %19[^,], age: %d, score: %f", s.name, &(s.age), &(s.score));
// 	printf("name: %s, age: %d, score: %.2f\n", s.name, s.age, s.score);

// 	printf("ret: %d\n", ret);

// 	// 关闭文件
// 	fclose(fp);
// 	fp = NULL; // 避免野指针

// 	return 0;
// }

// fread,fwrite
// struct S
// {
//     char name[20];
//     int age;
//     float score;
// };

// int main()
// {
//     struct S s = {"Tom", 20, 80.5};

//     FILE *pf = fopen("data1.txt", "wb");
//     if (pf == NULL)
//     {
//         perror("fopen\n");
//         return 1;
//     }
//     // 写文件
//     fwrite(&s, sizeof(struct S), 1, pf);

//     return 0;
// }

// int main()
//{
//	int data[] = {1, 2, 3, 4, 5};
//	// 打开文件
//	FILE *pf = fopen("data1.txt", "wb");
//
//	// 检查文件是否成功打开
//	if (pf == NULL)
//	{
//		perror("fopen\n");
//		return 1;
//	}
//
//	// 写入数据到文件
//	if (fwrite(data, sizeof(int), 5, pf) != 5)
//	{
//		perror("fwrite\n");
//		return 1;
//	}
//	// 关闭文件
//	fclose(pf);
//	pf = NULL; // 避免野指针
//
//	return 0;
// }

// struct S
// {
//     char name[20];
//     int age;
//     float score;
// };

// int main()
// {
//     struct S s = {0};
//     FILE *pf = fopen("data1.txt", "rb");
//     if (pf == NULL) // 检查文件是否成功打开
//     {
//         perror("fopen\n");
//         return 1;
//     }

//     // 读文件
//     size_t ret = fread(&s, sizeof(struct S), 1, pf);
//     if (ret != 1)
//     {
//         // 读到文件结尾
//         if (feof(pf))
//         {
//             printf("End of file reached.\n");
//         }
//         // 读取发生错误
//         else if (ferror(pf))
//         {
//             printf("Error occurred.\n");
//         }
//     }
//     printf("name: %s, age: %d, score: %.2f\n", s.name, s.age, s.score);

//     // 关闭文件
//     fclose(pf);
//     pf = NULL; // 避免野指针

//     return 0;
// }

// scanf,printf  -- 针对标准输入/输出的格式化的输入函数和输出函数
// fscanf,fprintf -- 针对所有输入流/所有输出流的格式化的输入函数和输出函数

// sscanf,sprintf --
// int sprintf(char *str,const char *format,...)
// 将格式化的数据写入字符数组(字符串),它类似于printf,但输出目标不是控制台或文件,而是用户指定的内存缓冲区,常用于动态生成字符串,拼接数据或转换数据格式.简而言之就是将格式化的数据转换成字符串.
// str--指向字符数组的指针,用于存储生成的字符串(需确保足够大以防止溢出)
// format--格式字符串,用于指定输出的格式,格式字符串的语法与printf相同,但不支持%s,只能使用%c,%d,%f,%u等格式.
//...--可变参数,用于指定要输出的数据,格式字符串中%s时,参数为字符串指针,格式字符串中%d,%f,%u时,参数为相应的整型或浮点型变量.
// 返回值--返回写入的字符数,不包括结尾的'\0'.

// int printf(const char *format,...) -- 格式化输出到标准输出(屏幕)

// struct S
// {
//     char name[20];
//     int age;
//     float score;
// };

// int main()
// {
//     struct S s = {"zhangsan", 20, 95.5f};
//     char buffer[100] = {0};

//     // printf("name: %s,score: %.2f,age: %d\n", s.name, s.score, s.age);
//     sprintf(buffer, "name: %s,score: %.2f,age: %d\n", s.name, s.score, s.age);
//     // printf(buffer); //buffer:"name: zhangsan,score: 95.50,age: 20\n"
//     printf("%s\n", buffer);
//     struct S t = {0};
//     // scanf("name:" % 19 [^, ] ",score:%f,age:%d", t.name, &(t.score), &(t.age));

//     sscanf(buffer, "name: %19[^,],score:%f,age:%d", t.name, &(t.score), &(t.age));
//     printf("name: %s,score: %.2f,age: %d\n", t.name, t.score, t.age);

//     return 0;
// }
// int sscanf(const char *str,const char *format,...)
// 从字符串读取格式化数据.它与scanf类似,但输入源是内存中的字符串而非控制台或文件.常用于解析字符串中的结构化数据(如提取数字,分割文本等)
// str--要解析的源字符串(输入数据来源)
// format--格式字符串,用于指定输入的格式,格式字符串的语法与scanf相同,但不支持%s,只能使用%c,%d,%f,%u等格式.
//...--可变参数,用于指定要读取的数据,格式字符串中%s时,参数为字符串指针,格式字符串中%d,%f,%u时,参数为相应的整型或浮点型变量.
// 返回值--返回读取的字符数,不包括结尾的'\0'.若输入结束或解析失败,返回EOF(通常是-1)

// int scanf(const char *format,...)
// 从键盘上读取格式化的数据放到变量中.它与fscanf类似,但输入源是控制台而不是文件.常用于从控制台读取用户输入.
// int scanf(const char *format,...)
// 从键盘上读取格式化的数据放到变量中