#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 第7章：综合项目实践
 * 7.2 简易文本编辑器
 */

#define MAX_LINES 100
#define MAX_LINE_LENGTH 80

typedef struct {
    char text[MAX_LINE_LENGTH];
} Line;

void addLine(Line lines[], int *lineCount) {
    if (*lineCount >= MAX_LINES) {
        printf("行数已达上限！\n");
        return;
    }

    Line line;
    printf("请输入一行文本 (最多%d个字符): ", MAX_LINE_LENGTH - 1);
    fgets(line.text, MAX_LINE_LENGTH, stdin);

    // 移除换行符
    size_t len = strlen(line.text);
    if (len > 0 && line.text[len - 1] == '\n') {
        line.text[len - 1] = '\0';
    }

    lines[*lineCount] = line;
    (*lineCount)++;

    printf("行添加成功！\n");
}

void displayLines(Line lines[], int lineCount) {
    printf("\n文本内容：\n");
    printf("--------------------\n");

    for (int i = 0; i < lineCount; i++) {
        printf("%d: %s\n", i + 1, lines[i].text);
    }

    printf("--------------------\n");
}

void insertLine(Line lines[], int *lineCount, int position) {
    if (*lineCount >= MAX_LINES) {
        printf("行数已达上限！\n");
        return;
    }

    if (position < 1 || position > *lineCount + 1) {
        printf("无效的位置！\n");
        return;
    }

    // 将指定位置之后的行向后移动
    for (int i = *lineCount; i > position - 1; i--) {
        lines[i] = lines[i - 1];
    }

    Line line;
    printf("请在位置%d插入新行: ", position);
    fgets(line.text, MAX_LINE_LENGTH, stdin);

    // 移除换行符
    size_t len = strlen(line.text);
    if (len > 0 && line.text[len - 1] == '\n') {
        line.text[len - 1] = '\0';
    }

    lines[position - 1] = line;
    (*lineCount)++;

    printf("行插入成功！\n");
}

void deleteLine(Line lines[], int *lineCount, int position) {
    if (position < 1 || position > *lineCount) {
        printf("无效的位置！\n");
        return;
    }

    // 将指定位置之后的行向前移动
    for (int i = position - 1; i < *lineCount - 1; i++) {
        lines[i] = lines[i + 1];
    }

    (*lineCount)--;

    printf("行删除成功！\n");
}

int main() {
    Line lines[MAX_LINES];
    int lineCount = 0;
    int choice;

    while (1) {
        printf("\n简易文本编辑器\n");
        printf("1. 添加行\n");
        printf("2. 显示所有行\n");
        printf("3. 在指定位置插入行\n");
        printf("4. 删除指定位置的行\n");
        printf("5. 退出编辑器\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addLine(lines, &lineCount);
                break;
            case 2:
                displayLines(lines, lineCount);
                break;
            case 3:
                int pos;
                printf("请输入要插入行的位置: ");
                scanf("%d", &pos);
                insertLine(lines, &lineCount, pos);
                break;
            case 4:
                int pos;
                printf("请输入要删除行的位置: ");
                scanf("%d", &pos);
                deleteLine(lines, &lineCount, pos);
                break;
            case 5:
                printf("谢谢使用简易文本编辑器！\n");
                return 0;
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }

    return 0;
}
