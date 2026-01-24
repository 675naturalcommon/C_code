@echo off
echo 测试Clock算法和改进Clock算法
echo.
echo 测试用例1: 物理块数=3, 手动输入访问序列
echo.
echo 3 > input.txt
echo 1 >> input.txt
echo 10 >> input.txt
echo 1 2 3 1 4 2 5 1 2 3 >> input.txt

页面置换算法模拟_完整_with_clock_fixed.exe < input.txt
pause
