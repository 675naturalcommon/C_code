#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20
#define MAX_SUBJECTS 10
#define MAX_SUBJECT_NAME_LENGTH 30

// 成绩结构体
typedef struct {
    char subject[MAX_SUBJECT_NAME_LENGTH];  // 科目名称
    float score;                            // 成绩
} Grade;

// 学生结构体
typedef struct {
    char id[MAX_ID_LENGTH];                // 学号
    char name[MAX_NAME_LENGTH];            // 姓名
    Grade grades[MAX_SUBJECTS];            // 成绩数组
    int grade_count;                       // 成绩数量
    float total;                           // 总分
    float average;                         // 平均分
} Student;

Student students[MAX_STUDENTS];            // 学生数组
int student_count = 0;                     // 当前学生数量

// 函数声明
void display_menu();
void add_student();
void delete_student();
void modify_student();
void search_student();
void display_all_students();
void calculate_statistics();
void save_to_file();
void load_from_file();
void clear_input_buffer();
int is_id_exists(const char *id);
void sort_students_by_total();
void add_grade_to_student(Student *student);
void remove_grade_from_student(Student *student);
void modify_grade_in_student(Student *student);
void display_student_grades(const Student *student);
void calculate_student_total_and_average(Student *student);

// 主函数
int main() {
    int choice;

    // 从文件加载数据
    load_from_file();

    printf("=== 学生成绩管理系统 ===\n");

    while (1) {
        display_menu();
        printf("请选择操作 (1-8): ");

        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                delete_student();
                break;
            case 3:
                modify_student();
                break;
            case 4:
                search_student();
                break;
            case 5:
                display_all_students();
                break;
            case 6:
                calculate_statistics();
                break;
            case 7:
                save_to_file();
                break;
            case 8:
                printf("感谢使用学生成绩管理系统！\n");
                save_to_file(); // 退出前保存数据
                return 0;
            default:
                printf("无效选择，请重新输入！\n");
        }

        printf("\n");
    }

    return 0;
}

// 显示菜单
void display_menu() {
    printf("\n========== 菜单 ==========\n");
    printf("1. 添加学生信息\n");
    printf("2. 删除学生信息\n");
    printf("3. 修改学生信息\n");
    printf("4. 查询学生信息\n");
    printf("5. 显示所有学生\n");
    printf("6. 统计信息\n");
    printf("7. 保存数据\n");
    printf("8. 退出系统\n");
    printf("==========================\n");
}

// 添加学生
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("学生数量已达上限，无法添加！\n");
        return;
    }

    Student new_student;
    new_student.grade_count = 0;  // 初始化成绩数量

    printf("请输入学号: ");
    fgets(new_student.id, MAX_ID_LENGTH, stdin);
    new_student.id[strcspn(new_student.id, "\n")] = 0; // 移除换行符

    // 检查学号是否已存在
    if (is_id_exists(new_student.id)) {
        printf("学号已存在，添加失败！\n");
        return;
    }

    printf("请输入姓名: ");
    fgets(new_student.name, MAX_NAME_LENGTH, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;

    // 添加成绩
    printf("是否添加成绩？(y/n): ");
    char add_grade;
    scanf("%c", &add_grade);
    clear_input_buffer();

    if (add_grade == 'y' || add_grade == 'Y') {
        add_grade_to_student(&new_student);
    }

    // 计算总分和平均分
    calculate_student_total_and_average(&new_student);

    students[student_count] = new_student;
    student_count++;

    printf("学生信息添加成功！\n");
}

// 删除学生
void delete_student() {
    if (student_count == 0) {
        printf("没有学生信息可删除！\n");
        return;
    }

    char id[MAX_ID_LENGTH];
    printf("请输入要删除的学生学号: ");
    fgets(id, MAX_ID_LENGTH, stdin);
    id[strcspn(id, "\n")] = 0;

    int found_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("未找到该学号的学生！\n");
        return;
    }

    // 显示要删除的学生信息
    printf("找到学生信息:\n");
    printf("学号: %s, 姓名: %s\n", students[found_index].id, students[found_index].name);
    display_student_grades(&students[found_index]);

    printf("确认删除？(y/n): ");
    char confirm;
    scanf("%c", &confirm);
    clear_input_buffer();

    if (confirm == 'y' || confirm == 'Y') {
        // 移动数组元素
        for (int i = found_index; i < student_count - 1; i++) {
            students[i] = students[i + 1];
        }
        student_count--;
        printf("学生信息删除成功！\n");
    } else {
        printf("取消删除操作。\n");
    }
}

// 修改学生信息
void modify_student() {
    if (student_count == 0) {
        printf("没有学生信息可修改！\n");
        return;
    }

    char id[MAX_ID_LENGTH];
    printf("请输入要修改的学生学号: ");
    fgets(id, MAX_ID_LENGTH, stdin);
    id[strcspn(id, "\n")] = 0;

    int found_index = -1;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("未找到该学号的学生！\n");
        return;
    }

    printf("找到学生信息:\n");
    printf("学号: %s, 姓名: %s\n", students[found_index].id, students[found_index].name);
    display_student_grades(&students[found_index]);

    int choice;
    do {
        printf("\n修改选项:\n");
        printf("1. 修改姓名\n");
        printf("2. 添加成绩\n");
        printf("3. 修改成绩\n");
        printf("4. 删除成绩\n");
        printf("5. 完成修改\n");
        printf("请选择操作: ");

        if (scanf("%d", &choice) != 1) {
            printf("输入无效！\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("请输入新的姓名: ");
                char new_name[MAX_NAME_LENGTH];
                fgets(new_name, MAX_NAME_LENGTH, stdin);
                new_name[strcspn(new_name, "\n")] = 0;
                strcpy(students[found_index].name, new_name);
                printf("姓名修改成功！\n");
                break;
            case 2:
                add_grade_to_student(&students[found_index]);
                break;
            case 3:
                modify_grade_in_student(&students[found_index]);
                break;
            case 4:
                remove_grade_from_student(&students[found_index]);
                break;
            case 5:
                printf("修改完成！\n");
                break;
            default:
                printf("无效选择！\n");
        }
    } while (choice != 5);

    // 重新计算总分和平均分
    calculate_student_total_and_average(&students[found_index]);
}

// 查询学生信息
void search_student() {
    if (student_count == 0) {
        printf("没有学生信息可查询！\n");
        return;
    }

    int choice;
    printf("查询方式:\n");
    printf("1. 按学号查询\n");
    printf("2. 按姓名查询\n");
    printf("请选择查询方式: ");

    if (scanf("%d", &choice) != 1) {
        printf("输入无效！\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (choice == 1) {
        char id[MAX_ID_LENGTH];
        printf("请输入学号: ");
        fgets(id, MAX_ID_LENGTH, stdin);
        id[strcspn(id, "\n")] = 0;

        int found = 0;
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].id, id) == 0) {
                printf("找到学生信息:\n");
                printf("学号: %s\n", students[i].id);
                printf("姓名: %s\n", students[i].name);
                display_student_grades(&students[i]);
                printf("总分: %.1f\n", students[i].total);
                printf("平均分: %.1f\n", students[i].average);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("未找到该学号的学生！\n");
        }
    } else if (choice == 2) {
        char name[MAX_NAME_LENGTH];
        printf("请输入姓名: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = 0;

        int found = 0;
        for (int i = 0; i < student_count; i++) {
            if (strstr(students[i].name, name) != NULL) {
                printf("找到学生信息:\n");
                printf("学号: %s\n", students[i].id);
                printf("姓名: %s\n", students[i].name);
                display_student_grades(&students[i]);
                printf("总分: %.1f\n", students[i].total);
                printf("平均分: %.1f\n", students[i].average);
                printf("------------------------\n");
                found = 1;
            }
        }

        if (!found) {
            printf("未找到该姓名的学生！\n");
        }
    } else {
        printf("无效的选择！\n");
    }
}

// 显示所有学生信息
void display_all_students() {
    if (student_count == 0) {
        printf("没有学生信息可显示！\n");
        return;
    }

    // 按总分排序
    sort_students_by_total();

    printf("\n=== 所有学生信息 (按总分排序) ===\n");
    printf("序号\t学号\t\t姓名\t\t科目数量\t总分\t平均分\n");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        printf("%d\t%s\t\t%s\t\t%d\t\t%.1f\t%.1f\n",
               i + 1,
               students[i].id,
               students[i].name,
               students[i].grade_count,
               students[i].total,
               students[i].average);
    }
    printf("------------------------------------------------------------------------\n");
    printf("总计: %d 名学生\n", student_count);
}

// 统计信息
void calculate_statistics() {
    if (student_count == 0) {
        printf("没有学生信息可统计！\n");
        return;
    }

    // 收集所有科目
    char all_subjects[MAX_SUBJECTS][MAX_SUBJECT_NAME_LENGTH];
    int subject_count = 0;

    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < students[i].grade_count; j++) {
            int found = 0;
            for (int k = 0; k < subject_count; k++) {
                if (strcmp(all_subjects[k], students[i].grades[j].subject) == 0) {
                    found = 1;
                    break;
                }
            }
            if (!found && subject_count < MAX_SUBJECTS) {
                strcpy(all_subjects[subject_count], students[i].grades[j].subject);
                subject_count++;
            }
        }
    }

    printf("\n=== 成绩统计信息 ===\n");
    printf("学生总数: %d\n", student_count);
    printf("科目总数: %d\n", subject_count);

    // 统计每个科目的成绩
    for (int i = 0; i < subject_count; i++) {
        float total = 0, max_score = 0, min_score = 100;
        int count = 0;

        for (int j = 0; j < student_count; j++) {
            for (int k = 0; k < students[j].grade_count; k++) {
                if (strcmp(students[j].grades[k].subject, all_subjects[i]) == 0) {
                    total += students[j].grades[k].score;
                    if (students[j].grades[k].score > max_score) max_score = students[j].grades[k].score;
                    if (students[j].grades[k].score < min_score) min_score = students[j].grades[k].score;
                    count++;
                    break;
                }
            }
        }

        if (count > 0) {
            printf("\n%s成绩统计:\n", all_subjects[i]);
            printf("  平均分: %.2f\n", total / count);
            printf("  最高分: %.1f\n", max_score);
            printf("  最低分: %.1f\n", min_score);
            printf("  参考人数: %d\n", count);
        }
    }

    // 显示前三名
    sort_students_by_total();
    printf("\n=== 总分前三名 ===\n");
    int display_count = student_count < 3 ? student_count : 3;
    for (int i = 0; i < display_count; i++) {
        printf("第%d名: %s (%s) - 总分: %.1f\n",
               i + 1, students[i].name, students[i].id, students[i].total);
    }
}

// 保存数据到文件
void save_to_file() {
    FILE *file = fopen("项目/学生成绩管理系统/students_data.txt", "w");
    if (file == NULL) {
        printf("无法创建数据文件！\n");
        return;
    }

    fprintf(file, "%d\n", student_count);
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s\n%s\n%d %.1f %.1f\n",
                students[i].id,
                students[i].name,
                students[i].grade_count,
                students[i].total,
                students[i].average);

        for (int j = 0; j < students[i].grade_count; j++) {
            fprintf(file, "%s %.1f\n",
                    students[i].grades[j].subject,
                    students[i].grades[j].score);
        }
    }

    fclose(file);
    printf("数据保存成功！\n");
}

// 从文件加载数据
void load_from_file() {
    FILE *file = fopen("项目/学生成绩管理系统/students_data.txt", "r");
    if (file == NULL) {
        printf("未找到数据文件，将创建新文件。\n");
        return;
    }

    fscanf(file, "%d", &student_count);
    for (int i = 0; i < student_count; i++) {
        fscanf(file, "%s", students[i].id);
        fscanf(file, " %[^\n]", students[i].name);
        fscanf(file, "%d %f %f",
               &students[i].grade_count,
               &students[i].total,
               &students[i].average);

        for (int j = 0; j < students[i].grade_count; j++) {
            fscanf(file, "%s %f",
                   students[i].grades[j].subject,
                   &students[i].grades[j].score);
        }
    }

    fclose(file);
    printf("数据加载成功！\n");
}

// 清空输入缓冲区
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 检查学号是否已存在
int is_id_exists(const char *id) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

// 按总分排序学生（降序）
void sort_students_by_total() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (students[j].total < students[j + 1].total) {
                // 交换学生信息
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// 添加成绩到学生
void add_grade_to_student(Student *student) {
    if (student->grade_count >= MAX_SUBJECTS) {
        printf("该学生的科目数量已达上限！\n");
        return;
    }

    Grade new_grade;

    printf("请输入科目名称: ");
    fgets(new_grade.subject, MAX_SUBJECT_NAME_LENGTH, stdin);
    new_grade.subject[strcspn(new_grade.subject, "\n")] = 0;

    // 检查科目是否已存在
    for (int i = 0; i < student->grade_count; i++) {
        if (strcmp(student->grades[i].subject, new_grade.subject) == 0) {
            printf("该科目已存在！\n");
            return;
        }
    }

    printf("请输入成绩: ");
    while (scanf("%f", &new_grade.score) != 1 || new_grade.score < 0 || new_grade.score > 100) {
        printf("成绩无效，请输入0-100之间的数字: ");
        clear_input_buffer();
    }
    clear_input_buffer();

    student->grades[student->grade_count] = new_grade;
    student->grade_count++;

    // 重新计算总分和平均分
    calculate_student_total_and_average(student);

    printf("成绩添加成功！\n");
}

// 从学生删除成绩
void remove_grade_from_student(Student *student) {
    if (student->grade_count == 0) {
        printf("该学生没有成绩可删除！\n");
        return;
    }

    printf("当前成绩列表:\n");
    display_student_grades(student);

    char subject[MAX_SUBJECT_NAME_LENGTH];
    printf("请输入要删除的科目名称: ");
    fgets(subject, MAX_SUBJECT_NAME_LENGTH, stdin);
    subject[strcspn(subject, "\n")] = 0;

    int found_index = -1;
    for (int i = 0; i < student->grade_count; i++) {
        if (strcmp(student->grades[i].subject, subject) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("未找到该科目！\n");
        return;
    }

    // 移动数组元素
    for (int i = found_index; i < student->grade_count - 1; i++) {
        student->grades[i] = student->grades[i + 1];
    }
    student->grade_count--;

    // 重新计算总分和平均分
    calculate_student_total_and_average(student);

    printf("成绩删除成功！\n");
}

// 修改学生成绩
void modify_grade_in_student(Student *student) {
    if (student->grade_count == 0) {
        printf("该学生没有成绩可修改！\n");
        return;
    }

    printf("当前成绩列表:\n");
    display_student_grades(student);

    char subject[MAX_SUBJECT_NAME_LENGTH];
    printf("请输入要修改的科目名称: ");
    fgets(subject, MAX_SUBJECT_NAME_LENGTH, stdin);
    subject[strcspn(subject, "\n")] = 0;

    int found_index = -1;
    for (int i = 0; i < student->grade_count; i++) {
        if (strcmp(student->grades[i].subject, subject) == 0) {
            found_index = i;
            break;
        }
    }

    if (found_index == -1) {
        printf("未找到该科目！\n");
        return;
    }

    printf("当前成绩: %.1f\n", student->grades[found_index].score);
    printf("请输入新的成绩: ");
    float new_score;
    while (scanf("%f", &new_score) != 1 || new_score < 0 || new_score > 100) {
        printf("成绩无效，请输入0-100之间的数字: ");
        clear_input_buffer();
    }
    clear_input_buffer();

    student->grades[found_index].score = new_score;

    // 重新计算总分和平均分
    calculate_student_total_and_average(student);

    printf("成绩修改成功！\n");
}

// 显示学生成绩
void display_student_grades(const Student *student) {
    if (student->grade_count == 0) {
        printf("  暂无成绩\n");
        return;
    }

    printf("  科目\t\t成绩\n");
    printf("  --------------------\n");
    for (int i = 0; i < student->grade_count; i++) {
        printf("  %s\t\t%.1f\n", student->grades[i].subject, student->grades[i].score);
    }
}

// 计算学生总分和平均分
void calculate_student_total_and_average(Student *student) {
    student->total = 0;
    for (int i = 0; i < student->grade_count; i++) {
        student->total += student->grades[i].score;
    }

    if (student->grade_count > 0) {
        student->average = student->total / student->grade_count;
    } else {
        student->average = 0;
    }
}
