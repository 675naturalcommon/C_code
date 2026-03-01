#include <stdio.h>
#include <string.h>

/**
 * 第7章：综合项目实践
 * 7.1 学生成绩管理系统
 */

#define MAX_STUDENTS 50

typedef struct {
    char name[50];
    int id;
    float chinese;
    float math;
    float english;
    float average;
} Student;

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("学生数量已达上限！\n");
        return;
    }

    Student s;
    printf("请输入学生姓名: ");
    scanf("%s", s.name);
    printf("请输入学生ID: ");
    scanf("%d", &s.id);
    printf("请输入语文成绩: ");
    scanf("%f", &s.chinese);
    printf("请输入数学成绩: ");
    scanf("%f", &s.math);
    printf("请输入英语成绩: ");
    scanf("%f", &s.english);

    s.average = (s.chinese + s.math + s.english) / 3.0;

    students[*count] = s;
    (*count)++;

    printf("学生信息添加成功！\n");
}

void displayStudents(Student students[], int count) {
    printf("\n学生信息列表：\n");
    printf("---------------------------------\n");
    printf("ID\t姓名\t语文\t数学\t英语\t平均分\n");
    printf("---------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%.1f\t%.1f\t%.1f\t%.1f\n",
               students[i].id, students[i].name,
               students[i].chinese, students[i].math,
               students[i].english, students[i].average);
    }

    printf("---------------------------------\n");
}

void searchStudentById(Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\n找到学生信息：\n");
            printf("ID: %d\n", students[i].id);
            printf("姓名: %s\n", students[i].name);
            printf("语文: %.1f\n", students[i].chinese);
            printf("数学: %.1f\n", students[i].math);
            printf("英语: %.1f\n", students[i].english);
            printf("平均分: %.1f\n", students[i].average);
            return;
        }
    }
    printf("未找到该学生！\n");
}

void deleteStudent(Student students[], int *count, int id) {
    int foundIndex = -1;

    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("未找到该学生！\n");
        return;
    }

    // 将后面的学生向前移动
    for (int i = foundIndex; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--;
    printf("学生信息删除成功！\n");
}

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    while (1) {
        printf("\n学生成绩管理系统\n");
        printf("1. 添加学生信息\n");
        printf("2. 显示所有学生信息\n");
        printf("3. 按ID查找学生\n");
        printf("4. 按ID删除学生\n");
        printf("5. 退出系统\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                displayStudents(students, studentCount);
                break;
            case 3: {
                int search_id;
                printf("请输入学生ID: ");
                scanf("%d", &search_id);
                searchStudentById(students, studentCount, search_id);
                break;
            }
            case 4: {
                int delete_id;
                printf("请输入学生ID: ");
                scanf("%d", &delete_id);
                deleteStudent(students, &studentCount, delete_id);
                break;
            }
            case 5:
                printf("谢谢使用学生成绩管理系统！\n");
                return 0;
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }

    return 0;
}
