@echo off
cd /d "%~dp0"
echo 正在测试页面置换算法模拟系统...
echo.
echo 测试用例1: 物理块数=3, 随机生成序列
echo.
echo 3 > input.txt
echo 2 >> input.txt
echo 10 >> input.txt
echo.
echo 运行程序...
type input.txt | 页面置换算法模拟_完整.exe
echo.
echo 测试完成!
pause
