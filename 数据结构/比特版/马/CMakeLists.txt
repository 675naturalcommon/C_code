# 指定最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言（C）
project(SeqListDemo C)

# 添加可执行文件，并列出所有源文件
add_executable(demo test.c SeqList.c)