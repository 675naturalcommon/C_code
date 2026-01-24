/*
 * C语言数组和指针综合示例
 *
 * 本文件展示数组和指针在实际项目中的综合应用
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 1. 学生成绩管理系统
typedef struct {
    char name[50];
    int id;
    float scores[5];  // 5门课程成绩
    float average;
} Student;

// 从文件读取学生数据
int read_students_from_file(const char *filename, Student **students_ptr) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("无法打开文件: %s\n", filename);
        return 0;
    }

    // 先统计文件行数
    int count = 0;
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    // 重新定位到文件开头
    fseek(file, 0, SEEK_SET);

    // 动态分配内存
    Student *students = (Student*)malloc(count * sizeof(Student));
    if(students == NULL) {
        printf("内存分配失败！\n");
        fclose(file);
        return 0;
    }

    // 读取数据
    int actual_count = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        Student *student = &students[actual_count];

        // 解析每行数据：姓名 学号 成绩1 成绩2 成绩3 成绩4 成绩5
        if(sscanf(buffer, "%s %d %f %f %f %f %f",
                  student->name, &student->id,
                  &student->scores[0], &student->scores[1],
                  &student->scores[2], &student->scores[3],
                  &student->scores[4]) == 7) {

            // 计算平均分
            float sum = 0;
            for(int i = 0; i < 5; i++) {
                sum += student->scores[i];
            }
            student->average = sum / 5;
            actual_count++;
        }
    }

    fclose(file);
    *students_ptr = students;
    return actual_count;
}

void input_student_data(Student *student) {
    printf("请输入学生姓名: ");
    scanf("%s", student->name);
    printf("请输入学号: ");
    scanf("%d", &student->id);

    printf("请输入5门课程成绩: ");
    float sum = 0;
    for(int i = 0; i < 5; i++) {
        scanf("%f", &student->scores[i]);
        sum += student->scores[i];
    }
    student->average = sum / 5;
}

void print_student_info(const Student *student) {
    printf("姓名: %s, 学号: %d, 平均分: %.2f\n",
           student->name, student->id, student->average);
    printf("各科成绩: ");
    for(int i = 0; i < 5; i++) {
        printf("%.1f ", student->scores[i]);
    }
    printf("\n");
}

void student_management_system() {
    printf("=== 学生成绩管理系统 ===\n");

    int choice;
    printf("选择数据输入方式:\n");
    printf("1. 从文件读取 (students_data.txt)\n");
    printf("2. 手动输入\n");
    printf("请选择: ");
    scanf("%d", &choice);

    Student *students = NULL;
    int num_students = 0;

    if(choice == 1) {
        // 从文件读取
        num_students = read_students_from_file("students_data.txt", &students);
        if(num_students > 0) {
            printf("成功从文件读取 %d 个学生信息\n", num_students);
        } else {
            printf("文件读取失败，请手动输入\n");
            choice = 2;
        }
    }

    if(choice == 2) {
        printf("请输入学生人数: ");
        scanf("%d", &num_students);

        // 动态分配学生数组
        students = (Student*)malloc(num_students * sizeof(Student));
        if(students == NULL) {
            printf("内存分配失败！\n");
            return;
        }

        // 输入学生数据
        for(int i = 0; i < num_students; i++) {
            printf("\n学生 %d:\n", i + 1);
            input_student_data(&students[i]);
        }
    }

    if(num_students == 0) {
        printf("没有学生数据\n");
        return;
    }

    // 显示所有学生信息
    printf("\n所有学生信息:\n");
    for(int i = 0; i < num_students; i++) {
        print_student_info(&students[i]);
    }

    // 计算班级平均分
    float class_average = 0;
    for(int i = 0; i < num_students; i++) {
        class_average += students[i].average;
    }
    class_average /= num_students;
    printf("\n班级平均分: %.2f\n", class_average);

    // 查找最高分学生
    int best_index = 0;
    for(int i = 1; i < num_students; i++) {
        if(students[i].average > students[best_index].average) {
            best_index = i;
        }
    }
    printf("最高分学生: ");
    print_student_info(&students[best_index]);

    free(students);
    printf("\n");
}

// 2. 矩阵运算库
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix* create_matrix(int rows, int cols) {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;

    // 分配行指针
    matrix->data = (double**)malloc(rows * sizeof(double*));
    for(int i = 0; i < rows; i++) {
        matrix->data[i] = (double*)malloc(cols * sizeof(double));
        // 初始化为0
        for(int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0.0;
        }
    }
    return matrix;
}

void free_matrix(Matrix *matrix) {
    for(int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

void print_matrix(const Matrix *matrix) {
    for(int i = 0; i < matrix->rows; i++) {
        for(int j = 0; j < matrix->cols; j++) {
            printf("%8.2f ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* matrix_multiply(const Matrix *a, const Matrix *b) {
    if(a->cols != b->rows) {
        printf("矩阵维度不匹配，无法相乘\n");
        return NULL;
    }

    Matrix *result = create_matrix(a->rows, b->cols);

    for(int i = 0; i < a->rows; i++) {
        for(int j = 0; j < b->cols; j++) {
            for(int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}

void matrix_operations() {
    printf("=== 矩阵运算 ===\n");

    // 创建矩阵A (2x3)
    Matrix *A = create_matrix(2, 3);
    A->data[0][0] = 1; A->data[0][1] = 2; A->data[0][2] = 3;
    A->data[1][0] = 4; A->data[1][1] = 5; A->data[1][2] = 6;

    // 创建矩阵B (3x2)
    Matrix *B = create_matrix(3, 2);
    B->data[0][0] = 7; B->data[0][1] = 8;
    B->data[1][0] = 9; B->data[1][1] = 10;
    B->data[2][0] = 11; B->data[2][1] = 12;

    printf("矩阵A (2x3):\n");
    print_matrix(A);

    printf("\n矩阵B (3x2):\n");
    print_matrix(B);

    // 矩阵乘法
    Matrix *C = matrix_multiply(A, B);
    if(C != NULL) {
        printf("\n矩阵乘积 C = A * B (2x2):\n");
        print_matrix(C);
        free_matrix(C);
    }

    free_matrix(A);
    free_matrix(B);
    printf("\n");
}

// 3. 字符串处理工具集
typedef struct {
    char **strings;
    int count;
    int capacity;
} StringArray;

StringArray* create_string_array(int capacity) {
    StringArray *array = (StringArray*)malloc(sizeof(StringArray));
    array->count = 0;
    array->capacity = capacity;
    array->strings = (char**)malloc(capacity * sizeof(char*));
    return array;
}

void add_string(StringArray *array, const char *str) {
    if(array->count >= array->capacity) {
        // 扩容
        array->capacity *= 2;
        array->strings = (char**)realloc(array->strings,
                                       array->capacity * sizeof(char*));
    }

    array->strings[array->count] = (char*)malloc(strlen(str) + 1);
    strcpy(array->strings[array->count], str);
    array->count++;
}

void free_string_array(StringArray *array) {
    for(int i = 0; i < array->count; i++) {
        free(array->strings[i]);
    }
    free(array->strings);
    free(array);
}

void sort_strings(StringArray *array) {
    // 使用冒泡排序对字符串进行字典序排序
    for(int i = 0; i < array->count - 1; i++) {
        for(int j = 0; j < array->count - i - 1; j++) {
            if(strcmp(array->strings[j], array->strings[j + 1]) > 0) {
                // 交换指针
                char *temp = array->strings[j];
                array->strings[j] = array->strings[j + 1];
                array->strings[j + 1] = temp;
            }
        }
    }
}

void string_processing_tools() {
    printf("=== 字符串处理工具 ===\n");

    StringArray *words = create_string_array(10);

    add_string(words, "apple");
    add_string(words, "zebra");
    add_string(words, "banana");
    add_string(words, "cherry");
    add_string(words, "date");

    printf("原始字符串数组:\n");
    for(int i = 0; i < words->count; i++) {
        printf("%s ", words->strings[i]);
    }
    printf("\n");

    sort_strings(words);

    printf("排序后的字符串数组:\n");
    for(int i = 0; i < words->count; i++) {
        printf("%s ", words->strings[i]);
    }
    printf("\n");

    free_string_array(words);
    printf("\n");
}

// 4. 动态数组实现（泛型）
typedef struct {
    void **data;
    int size;
    int capacity;
    size_t element_size;
} DynamicArray;

DynamicArray* create_dynamic_array(size_t element_size, int initial_capacity) {
    DynamicArray *array = (DynamicArray*)malloc(sizeof(DynamicArray));
    array->size = 0;
    array->capacity = initial_capacity;
    array->element_size = element_size;
    array->data = (void**)malloc(initial_capacity * sizeof(void*));
    return array;
}

void dynamic_array_push_back(DynamicArray *array, void *element) {
    if(array->size >= array->capacity) {
        array->capacity *= 2;
        array->data = (void**)realloc(array->data,
                                    array->capacity * sizeof(void*));
    }

    array->data[array->size] = malloc(array->element_size);
    memcpy(array->data[array->size], element, array->element_size);
    array->size++;
}

void* dynamic_array_get(DynamicArray *array, int index) {
    if(index < 0 || index >= array->size) {
        return NULL;
    }
    return array->data[index];
}

void free_dynamic_array(DynamicArray *array) {
    for(int i = 0; i < array->size; i++) {
        free(array->data[i]);
    }
    free(array->data);
    free(array);
}

void generic_dynamic_array() {
    printf("=== 泛型动态数组 ===\n");

    // 整数动态数组
    DynamicArray *int_array = create_dynamic_array(sizeof(int), 5);

    for(int i = 0; i < 10; i++) {
        int value = i * 10;
        dynamic_array_push_back(int_array, &value);
    }

    printf("整数动态数组内容:\n");
    for(int i = 0; i < int_array->size; i++) {
        int *value = (int*)dynamic_array_get(int_array, i);
        printf("%d ", *value);
    }
    printf("\n");

    free_dynamic_array(int_array);

    // 浮点数动态数组
    DynamicArray *float_array = create_dynamic_array(sizeof(float), 5);

    for(int i = 0; i < 5; i++) {
        float value = i * 1.5f;
        dynamic_array_push_back(float_array, &value);
    }

    printf("浮点数动态数组内容:\n");
    for(int i = 0; i < float_array->size; i++) {
        float *value = (float*)dynamic_array_get(float_array, i);
        printf("%.1f ", *value);
    }
    printf("\n");

    free_dynamic_array(float_array);
    printf("\n");
}

// 5. 内存池实现
typedef struct {
    void *memory;
    size_t block_size;
    int total_blocks;
    int *free_blocks;
    int free_count;
} MemoryPool;

MemoryPool* create_memory_pool(size_t block_size, int total_blocks) {
    MemoryPool *pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    pool->block_size = block_size;
    pool->total_blocks = total_blocks;

    // 分配内存块
    pool->memory = malloc(block_size * total_blocks);

    // 初始化空闲块索引数组
    pool->free_blocks = (int*)malloc(total_blocks * sizeof(int));
    pool->free_count = total_blocks;

    for(int i = 0; i < total_blocks; i++) {
        pool->free_blocks[i] = i;
    }

    return pool;
}

void* memory_pool_alloc(MemoryPool *pool) {
    if(pool->free_count == 0) {
        return NULL;  // 内存池已满
    }

    int block_index = pool->free_blocks[--pool->free_count];
    return (char*)pool->memory + block_index * pool->block_size;
}

void memory_pool_free(MemoryPool *pool, void *block) {
    if(block == NULL) return;

    // 计算块索引
    size_t offset = (char*)block - (char*)pool->memory;
    int block_index = offset / pool->block_size;

    if(block_index >= 0 && block_index < pool->total_blocks) {
        pool->free_blocks[pool->free_count++] = block_index;
    }
}

void free_memory_pool(MemoryPool *pool) {
    free(pool->memory);
    free(pool->free_blocks);
    free(pool);
}

void memory_pool_demo() {
    printf("=== 内存池实现 ===\n");

    MemoryPool *pool = create_memory_pool(sizeof(int), 5);

    int *blocks[5];

    // 分配内存块
    printf("分配内存块:\n");
    for(int i = 0; i < 5; i++) {
        blocks[i] = (int*)memory_pool_alloc(pool);
        if(blocks[i] != NULL) {
            *blocks[i] = i * 100;
            printf("分配块 %d: 地址=%p, 值=%d\n",
                   i, (void*)blocks[i], *blocks[i]);
        }
    }

    // 尝试分配更多（应该失败）
    int *extra = (int*)memory_pool_alloc(pool);
    if(extra == NULL) {
        printf("内存池已满，无法分配更多块\n");
    }

    // 释放一些块
    printf("\n释放块 1 和 3:\n");
    memory_pool_free(pool, blocks[1]);
    memory_pool_free(pool, blocks[3]);

    // 重新分配
    int *new_block = (int*)memory_pool_alloc(pool);
    if(new_block != NULL) {
        *new_block = 999;
        printf("重新分配块: 地址=%p, 值=%d\n", (void*)new_block, *new_block);
    }

    free_memory_pool(pool);
    printf("\n");
}

// 6. 性能测试：数组 vs 指针
void performance_comparison() {
    printf("=== 性能测试：数组 vs 指针 ===\n");

    const int SIZE = 1000000;
    int *data = (int*)malloc(SIZE * sizeof(int));

    // 初始化数据
    for(int i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // 测试1：数组下标访问
    clock_t start = clock();
    long long sum1 = 0;
    for(int i = 0; i < SIZE; i++) {
        sum1 += data[i];
    }
    clock_t end = clock();
    double time1 = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    printf("数组下标访问: %.2f ms, 总和: %lld\n", time1, sum1);

    // 测试2：指针访问
    start = clock();
    long long sum2 = 0;
    int *ptr = data;
    for(int i = 0; i < SIZE; i++) {
        sum2 += *ptr++;
    }
    end = clock();
    double time2 = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    printf("指针访问: %.2f ms, 总和: %lld\n", time2, sum2);

    // 测试3：指针优化访问
    start = clock();
    long long sum3 = 0;
    int *end_ptr = data + SIZE;
    for(ptr = data; ptr < end_ptr; ptr++) {
        sum3 += *ptr;
    }
    end = clock();
    double time3 = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    printf("指针优化访问: %.2f ms, 总和: %lld\n", time3, sum3);

    free(data);

    printf("性能提升: %.1f%%\n", (time1 - time3) / time1 * 100);
    printf("\n");
}

int main() {
    printf("C语言数组和指针综合示例\n");
    printf("=======================\n\n");

    student_management_system();
    matrix_operations();
    string_processing_tools();
    generic_dynamic_array();
    memory_pool_demo();
    performance_comparison();

    printf("综合应用总结:\n");
    printf("1. 数组和指针是C语言的核心概念\n");
    printf("2. 动态内存管理使程序更加灵活\n");
    printf("3. 多维数组和指针可以表示复杂数据结构\n");
    printf("4. 字符串处理依赖于字符数组和指针\n");
    printf("5. 泛型编程可以通过void指针实现\n");
    printf("6. 内存池可以提高内存分配效率\n");
    printf("7. 指针运算可以优化性能\n");
    printf("8. 理解数组和指针的关系至关重要\n");

    return 0;
}
