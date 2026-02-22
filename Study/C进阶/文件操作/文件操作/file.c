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
//{
//	char name[20];
//	int age;
//	float score;
//};
//
// int main()
//{
//	struct S s = {"Tom", 20, 80.5};
//
//	FILE *pf = fopen("data1.txt", "wb");
//	if (pf == NULL)
//	{
//		perror("fopen\n");
//		return 1;
//	}
//	// 写文件
//	fwrite(&s, sizeof(struct S), 1, pf);
//
//	return 0;
//}

//int main()
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
//}