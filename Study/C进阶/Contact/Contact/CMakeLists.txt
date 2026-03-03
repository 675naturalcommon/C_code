# 指定最低 CMake 版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言
project(ContactDemo C)

#添加可执行文件并列出所有源文件
add_executable(demo text.c contact.c)
