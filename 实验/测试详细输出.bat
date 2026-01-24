@echo off
echo 测试分页存储管理系统的详细输出...
echo.

echo 创建测试输入文件...
echo 1 > test_input.txt
echo 2 >> test_input.txt
echo 3 >> test_input.txt
echo 8192 >> test_input.txt
echo 4 >> test_input.txt
echo 5 >> test_input.txt
echo 7 >> test_input.txt

echo 运行程序进行测试...
分页存储管理.exe < test_input.txt

echo.
echo 测试完成！
echo 检查输出是否包含：
echo - 初始值显示
echo - 运算过程
echo - 运行结果
echo - 详细的步骤说明

pause
