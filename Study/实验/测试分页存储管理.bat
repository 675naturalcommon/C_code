@echo off
echo 正在测试分页存储管理系统...
echo.

echo 测试1: 显示系统信息
echo 1 > input.txt
echo 7 >> input.txt

echo 测试2: 分配内存给进程
echo 2 > input.txt
echo 7 >> input.txt

echo 测试3: 逻辑地址转换
echo 2 > input.txt
echo 3 >> input.txt
echo 8192 >> input.txt
echo 7 >> input.txt

echo 测试4: 显示页表和内存状态
echo 2 > input.txt
echo 4 >> input.txt
echo 5 >> input.txt
echo 7 >> input.txt

echo 测试5: 修改页表项
echo 2 > input.txt
echo 6 >> input.txt
echo 1 >> input.txt
echo 1 >> input.txt
echo 7 >> input.txt

echo 测试6: 越界检查
echo 2 > input.txt
echo 3 >> input.txt
echo 20000 >> input.txt
echo 7 >> input.txt

echo 开始自动测试...
分页存储管理.exe < input.txt

echo.
echo 测试完成！
pause
