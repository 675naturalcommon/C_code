#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

class ImprovedBankerAlgorithm {
private:
    int processCount;    // 进程数量
    int resourceCount;   // 资源类型数量
    vector<vector<int>> maxMatrix;      // 最大需求矩阵
    vector<vector<int>> allocationMatrix; // 已分配矩阵
    vector<vector<int>> needMatrix;     // 需求矩阵
    vector<int> available;             // 可用资源向量
    vector<bool> finished;             // 进程完成标记
    vector<int> safeSequence;          // 安全序列

public:
    // 构造函数
    ImprovedBankerAlgorithm(int p = 5, int r = 3) : processCount(p), resourceCount(r) {
        initializeMatrices();
    }

    // 初始化矩阵
    void initializeMatrices() {
        maxMatrix.resize(processCount, vector<int>(resourceCount, 0));
        allocationMatrix.resize(processCount, vector<int>(resourceCount, 0));
        needMatrix.resize(processCount, vector<int>(resourceCount, 0));
        available.resize(resourceCount, 0);
        finished.resize(processCount, false);
        safeSequence.clear();
    }

    // 设置系统状态
    void setSystemState(const vector<vector<int>>& max,
                       const vector<vector<int>>& allocation,
                       const vector<int>& avail) {
        maxMatrix = max;
        allocationMatrix = allocation;
        available = avail;
        calculateNeedMatrix();
    }

    // 设置预设测试数据
    void setDefaultTestData() {
        // 经典银行家算法测试数据
        vector<vector<int>> defaultMax = {
            {7, 5, 3},
            {3, 2, 2},
            {9, 0, 2},
            {2, 2, 2},
            {4, 3, 3}
        };

        vector<vector<int>> defaultAllocation = {
            {0, 1, 0},
            {2, 0, 0},
            {3, 0, 2},
            {2, 1, 1},
            {0, 0, 2}
        };

        vector<int> defaultAvailable = {3, 3, 2};

        setSystemState(defaultMax, defaultAllocation, defaultAvailable);
        cout << "✓ 预设测试数据已加载\n";
    }

    // 手动输入系统状态
    void inputSystemState() {
        cout << "\n=== 手动输入系统状态 ===\n";

        cout << "请输入可用资源向量 (" << resourceCount << "种资源): ";
        for (int i = 0; i < resourceCount; i++) {
            cin >> available[i];
        }

        cout << "\n请输入最大需求矩阵 (" << processCount << "个进程 × " << resourceCount << "种资源):\n";
        for (int i = 0; i < processCount; i++) {
            cout << "进程 P" << i << ": ";
            for (int j = 0; j < resourceCount; j++) {
                cin >> maxMatrix[i][j];
            }
        }

        cout << "\n请输入已分配矩阵 (" << processCount << "个进程 × " << resourceCount << "种资源):\n";
        for (int i = 0; i < processCount; i++) {
            cout << "进程 P" << i << ": ";
            for (int j = 0; j < resourceCount; j++) {
                cin >> allocationMatrix[i][j];
                // 验证分配不超过最大需求
                if (allocationMatrix[i][j] > maxMatrix[i][j]) {
                    cout << "错误：进程 P" << i << "的资源" << j << "分配超过最大需求！\n";
                    cout << "请重新输入: ";
                    j--; // 重新输入当前资源
                }
            }
        }

        calculateNeedMatrix();
        cout << "✓ 系统状态输入完成\n";
    }

    // 计算需求矩阵
    void calculateNeedMatrix() {
        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
                // 确保需求非负
                if (needMatrix[i][j] < 0) {
                    needMatrix[i][j] = 0;
                }
            }
        }
    }

    // 安全性检查算法（改进版本）
    bool safetyCheck(bool verbose = true) {
        vector<int> work = available;
        vector<bool> finish(processCount, false);
        safeSequence.clear();

        if (verbose) {
            cout << "\n=== 安全性检查过程 ===\n";
            cout << "初始可用资源: ";
            printVector(work);
            cout << endl;
        }

        bool found;
        int iteration = 0;

        do {
            found = false;
            iteration++;

            if (verbose) {
                cout << "第 " << iteration << " 轮查找:\n";
            }

            for (int i = 0; i < processCount; i++) {
                if (!finish[i] && checkNeedLessThanWork(i, work)) {
                    if (verbose) {
                        cout << "  ✓ 找到进程 P" << i << ": 需求";
                        printVector(needMatrix[i]);
                        cout << "    <= 可用";
                        printVector(work);
                    }

                    // 模拟进程执行完成，释放资源
                    for (int j = 0; j < resourceCount; j++) {
                        work[j] += allocationMatrix[i][j];
                    }

                    finish[i] = true;
                    safeSequence.push_back(i);
                    found = true;

                    if (verbose) {
                        cout << "    进程 P" << i << " 执行完成，释放资源后可用: ";
                        printVector(work);
                        cout << "    当前安全序列: ";
                        printSafeSequence();
                        cout << endl;
                    }
                    break;
                }
            }
        } while (found);

        // 检查是否所有进程都完成
        bool safe = true;
        for (int i = 0; i < processCount; i++) {
            if (!finish[i]) {
                safe = false;
                break;
            }
        }

        if (verbose) {
            if (safe) {
                cout << "✓ 系统处于安全状态！\n";
                cout << "最终安全序列: ";
                printSafeSequence();
            } else {
                cout << "✗ 系统处于不安全状态！\n";
                cout << "无法找到完整的安全序列\n";
            }
            cout << endl;
        }

        return safe;
    }

    // 资源请求算法（改进版本）
    bool requestResources(int processId, const vector<int>& request, bool verbose = true) {
        if (verbose) {
            cout << "\n=== 处理进程 P" << processId << " 的资源请求 ===\n";
            cout << "请求资源: ";
            printVector(request);
        }

        // 输入验证
        if (processId < 0 || processId >= processCount) {
            cout << "错误：无效的进程号！\n";
            return false;
        }

        // 步骤1：检查请求是否超过需求
        for (int i = 0; i < resourceCount; i++) {
            if (request[i] > needMatrix[processId][i]) {
                cout << "错误：请求资源超过声明的最大需求！\n";
                cout << "进程 P" << processId << " 的需求: ";
                printVector(needMatrix[processId]);
                return false;
            }
        }

        // 步骤2：检查请求是否超过可用资源
        for (int i = 0; i < resourceCount; i++) {
            if (request[i] > available[i]) {
                cout << "错误：请求资源超过可用资源！\n";
                cout << "当前可用资源: ";
                printVector(available);
                return false;
            }
        }

        // 步骤3：尝试分配资源
        if (verbose) {
            cout << "进行试探性分配...\n";
        }

        // 保存原始状态以便回滚
        vector<int> oldAvailable = available;
        vector<vector<int>> oldAllocation = allocationMatrix;
        vector<vector<int>> oldNeed = needMatrix;

        // 模拟分配
        for (int i = 0; i < resourceCount; i++) {
            available[i] -= request[i];
            allocationMatrix[processId][i] += request[i];
            needMatrix[processId][i] -= request[i];
        }

        if (verbose) {
            cout << "分配后系统状态:\n";
            printCurrentState();
        }

        // 步骤4：执行安全性检查
        bool safe = safetyCheck(verbose);

        if (safe) {
            if (verbose) {
                cout << "✓ 资源分配成功！系统保持安全状态\n";
            }
            return true;
        } else {
            // 步骤5：如果不安全，恢复原状态
            if (verbose) {
                cout << "✗ 资源分配会导致系统不安全，取消分配\n";
            }
            available = oldAvailable;
            allocationMatrix = oldAllocation;
            needMatrix = oldNeed;
            return false;
        }
    }

    // 显示系统状态（改进显示格式）
    void printCurrentState() {
        cout << "\n=== 当前系统状态 ===\n";

        // 显示可用资源
        cout << "可用资源 Available: ";
        printVector(available);
        cout << endl;

        // 显示表头
        cout << setw(8) << "进程" << setw(15) << "最大需求(Max)"
             << setw(15) << "已分配(Alloc)" << setw(15) << "需求(Need)" << endl;

        cout << setw(8) << " ";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < resourceCount; j++) {
                cout << "R" << j << " ";
            }
            cout << setw(5);
        }
        cout << endl;

        // 显示每个进程的信息
        for (int i = 0; i < processCount; i++) {
            cout << setw(6) << "P" << i << "  ";

            // 显示最大需求
            for (int j = 0; j < resourceCount; j++) {
                cout << setw(2) << maxMatrix[i][j] << " ";
            }
            cout << "   ";

            // 显示已分配
            for (int j = 0; j < resourceCount; j++) {
                cout << setw(2) << allocationMatrix[i][j] << " ";
            }
            cout << "   ";

            // 显示需求
            for (int j = 0; j < resourceCount; j++) {
                cout << setw(2) << needMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // 显示安全序列
    void printSafeSequence() {
        if (safeSequence.empty()) {
            cout << "无安全序列";
            return;
        }

        for (int i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i];
            if (i < safeSequence.size() - 1) {
                cout << " → ";
            }
        }
    }

    // 获取最后的安全序列
    vector<int> getSafeSequence() const {
        return safeSequence;
    }

    // 获取资源类型数量
    int getResourceCount() const {
        return resourceCount;
    }

    // 检查系统是否处于死锁状态
    bool checkDeadlock() {
        return !safetyCheck(false);
    }

    // 显示系统摘要信息
    void printSystemSummary() {
        cout << "\n=== 系统摘要信息 ===\n";
        cout << "进程数量: " << processCount << endl;
        cout << "资源类型: " << resourceCount << endl;

        int totalAllocated = 0;
        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                totalAllocated += allocationMatrix[i][j];
            }
        }
        cout << "已分配资源总量: " << totalAllocated << endl;

        cout << "系统安全状态: " << (safetyCheck(false) ? "安全" : "不安全") << endl;

        if (!safeSequence.empty()) {
            cout << "安全序列: ";
            printSafeSequence();
            cout << endl;
        }
    }

private:
    // 检查进程需求是否小于等于工作向量
    bool checkNeedLessThanWork(int processId, const vector<int>& work) {
        for (int i = 0; i < resourceCount; i++) {
            if (needMatrix[processId][i] > work[i]) {
                return false;
            }
        }
        return true;
    }

    // 打印向量
    void printVector(const vector<int>& vec) {
        cout << "[";
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i < vec.size() - 1) cout << ", ";
        }
        cout << "]";
    }
};

// 清空输入缓冲区
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// 主菜单函数
void showMainMenu() {
    cout << "\n========== 改进银行家算法模拟系统 ==========\n";
    cout << "1. 显示系统状态\n";
    cout << "2. 安全性检查\n";
    cout << "3. 资源请求\n";
    cout << "4. 死锁检测\n";
    cout << "5. 系统摘要\n";
    cout << "6. 加载预设测试数据\n";
    cout << "7. 手动输入系统状态\n";
    cout << "8. 批量测试用例\n";
    cout << "0. 退出\n";
    cout << "请选择操作: ";
}

// 批量测试函数
void runBatchTests(ImprovedBankerAlgorithm& banker) {
    cout << "\n=== 批量测试用例 ===\n";

    // 测试1：安全请求
    cout << "\n测试1：进程1请求资源 [1, 0, 2]\n";
    vector<int> request1 = {1, 0, 2};
    banker.requestResources(1, request1);

    // 测试2：不安全请求
    cout << "\n测试2：进程4请求资源 [3, 3, 0] (会导致不安全)\n";
    vector<int> request2 = {3, 3, 0};
    banker.requestResources(4, request2);

    // 测试3：安全请求
    cout << "\n测试3：进程0请求资源 [0, 2, 0]\n";
    vector<int> request3 = {0, 2, 0};
    banker.requestResources(0, request3);
}

int main() {
    ImprovedBankerAlgorithm banker;

    cout << "========== 改进银行家算法模拟系统 ==========\n";
    cout << "作者：Cline - 基于经典银行家算法的改进实现\n";
    cout << "功能特点：\n";
    cout << "  • 面向对象设计\n";
    cout << "  • 详细的执行过程显示\n";
    cout << "  • 完善的错误处理\n";
    cout << "  • 死锁检测功能\n";
    cout << "  • 批量测试支持\n";

    // 默认加载预设数据
    banker.setDefaultTestData();

    int choice;
    while (true) {
        showMainMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                banker.printCurrentState();
                break;

            case 2:
                banker.safetyCheck(true);
                break;

            case 3: {
                int process;
                vector<int> request(banker.getResourceCount());

                cout << "请输入请求资源的进程号: ";
                cin >> process;
                clearInputBuffer();

                cout << "请输入请求的资源量: ";
                for (int i = 0; i < banker.getResourceCount(); i++) {
                    cin >> request[i];
                }
                clearInputBuffer();

                banker.requestResources(process, request, true);
                break;
            }

            case 4:
                if (banker.checkDeadlock()) {
                    cout << "✗ 系统可能处于死锁状态！\n";
                } else {
                    cout << "✓ 系统无死锁风险\n";
                }
                break;

            case 5:
                banker.printSystemSummary();
                break;

            case 6:
                banker.setDefaultTestData();
                break;

            case 7:
                banker.inputSystemState();
                break;

            case 8:
                runBatchTests(banker);
                break;

            case 0:
                cout << "感谢使用改进银行家算法模拟系统！\n";
                return 0;

            default:
                cout << "无效选择，请重新输入！\n";
        }
    }

    return 0;
}
