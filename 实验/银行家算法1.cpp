#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class BankerAlgorithm {
private:
    int processCount;    // 进程数量
    int resourceCount;   // 资源类型数量
    vector<vector<int>> maxMatrix;      // 最大需求矩阵
    vector<vector<int>> allocationMatrix; // 已分配矩阵
    vector<vector<int>> needMatrix;     // 需求矩阵
    vector<int> available;             // 可用资源向量
    vector<bool> finished;             // 进程完成标记

public:
    // 构造函数
    BankerAlgorithm(int p, int r) : processCount(p), resourceCount(r) {
        // 初始化矩阵和向量
        maxMatrix.resize(processCount, vector<int>(resourceCount, 0));
        allocationMatrix.resize(processCount, vector<int>(resourceCount, 0));
        needMatrix.resize(processCount, vector<int>(resourceCount, 0));
        available.resize(resourceCount, 0);
        finished.resize(processCount, false);
    }

    // 设置最大需求矩阵
    void setMaxMatrix(const vector<vector<int>>& max) {
        maxMatrix = max;
        calculateNeedMatrix();
    }

    // 设置已分配矩阵
    void setAllocationMatrix(const vector<vector<int>>& allocation) {
        allocationMatrix = allocation;
        calculateNeedMatrix();
    }

    // 设置可用资源
    void setAvailable(const vector<int>& avail) {
        available = avail;
    }

    // 计算需求矩阵
    void calculateNeedMatrix() {
        for (int i = 0; i < processCount; i++) {
            for (int j = 0; j < resourceCount; j++) {
                needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
            }
        }
    }

    // 安全性检查算法
    bool safetyCheck() {
        vector<int> work = available;
        vector<bool> finish = finished;
        vector<int> safeSequence;

        cout << "开始安全性检查..." << endl;
        cout << "初始可用资源: ";
        printVector(work);

        bool found;
        do {
            found = false;
            for (int i = 0; i < processCount; i++) {
                if (!finish[i] && checkNeedLessThanWork(i, work)) {
                    cout << "进程 P" << i << " 可以执行，需求: ";
                    printVector(needMatrix[i]);
                    cout << "当前可用: ";
                    printVector(work);

                    // 模拟进程执行完成，释放资源
                    for (int j = 0; j < resourceCount; j++) {
                        work[j] += allocationMatrix[i][j];
                    }

                    finish[i] = true;
                    safeSequence.push_back(i);
                    found = true;

                    cout << "进程 P" << i << " 执行完成，释放资源后可用: ";
                    printVector(work);
                    cout << "安全序列当前: ";
                    for (int seq : safeSequence) {
                        cout << "P" << seq << " ";
                    }
                    cout << endl << endl;
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

        if (safe) {
            cout << "系统处于安全状态！安全序列: ";
            for (int i = 0; i < safeSequence.size(); i++) {
                cout << "P" << safeSequence[i];
                if (i != safeSequence.size() - 1) cout << " -> ";
            }
            cout << endl;
        } else {
            cout << "系统处于不安全状态！" << endl;
        }

        return safe;
    }

    // 资源请求算法
    bool requestResources(int processId, const vector<int>& request) {
        cout << "\n进程 P" << processId << " 请求资源: ";
        printVector(request);

        // 步骤1：检查请求是否超过需求
        for (int i = 0; i < resourceCount; i++) {
            if (request[i] > needMatrix[processId][i]) {
                cout << "错误：请求资源超过声明的最大需求！" << endl;
                return false;
            }
        }

        // 步骤2：检查请求是否超过可用资源
        for (int i = 0; i < resourceCount; i++) {
            if (request[i] > available[i]) {
                cout << "资源不足，进程 P" << processId << " 必须等待" << endl;
                return false;
            }
        }

        // 步骤3：尝试分配资源
        cout << "尝试分配资源..." << endl;
        vector<int> oldAvailable = available;
        vector<vector<int>> oldAllocation = allocationMatrix;
        vector<vector<int>> oldNeed = needMatrix;

        // 模拟分配
        for (int i = 0; i < resourceCount; i++) {
            available[i] -= request[i];
            allocationMatrix[processId][i] += request[i];
            needMatrix[processId][i] -= request[i];
        }

        cout << "分配后状态：" << endl;
        printCurrentState();

        // 步骤4：执行安全性检查
        if (safetyCheck()) {
            cout << "资源分配成功！系统保持安全状态" << endl;
            return true;
        } else {
            // 步骤5：如果不安全，恢复原状态
            cout << "资源分配会导致系统不安全，取消分配" << endl;
            available = oldAvailable;
            allocationMatrix = oldAllocation;
            needMatrix = oldNeed;
            return false;
        }
    }

    // 打印当前状态
    void printCurrentState() {
        cout << "\n当前系统状态：" << endl;
        cout << "进程\\资源";
        for (int j = 0; j < resourceCount; j++) {
            cout << "  R" << j;
        }
        cout << endl;

        cout << "最大需求矩阵：" << endl;
        for (int i = 0; i < processCount; i++) {
            cout << "P" << i << ":     ";
            printVector(maxMatrix[i]);
        }

        cout << "已分配矩阵：" << endl;
        for (int i = 0; i < processCount; i++) {
            cout << "P" << i << ":     ";
            printVector(allocationMatrix[i]);
        }

        cout << "需求矩阵：" << endl;
        for (int i = 0; i < processCount; i++) {
            cout << "P" << i << ":     ";
            printVector(needMatrix[i]);
        }

        cout << "可用资源：";
        printVector(available);
        cout << endl;
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
        for (int value : vec) {
            cout << value << " ";
        }
        cout << endl;
    }
};

// 测试函数
int main() {
    cout << "=== 银行家算法实现 ===" << endl;

    // 创建银行家算法实例：5个进程，3种资源
    BankerAlgorithm banker(5, 3);

    // 设置最大需求矩阵
    vector<vector<int>> maxMatrix = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // 设置已分配矩阵
    vector<vector<int>> allocationMatrix = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // 设置可用资源
    vector<int> available = {3, 3, 2};

    // 初始化银行家算法
    banker.setMaxMatrix(maxMatrix);
    banker.setAllocationMatrix(allocationMatrix);
    banker.setAvailable(available);

    // 显示初始状态
    banker.printCurrentState();

    // 执行安全性检查
    banker.safetyCheck();

    // 测试资源请求
    cout << "\n=== 测试资源请求 ===" << endl;

    // 测试1：进程1请求资源 [1, 0, 2]
    vector<int> request1 = {1, 0, 2};
    banker.requestResources(1, request1);

    // 测试2：进程4请求资源 [3, 3, 0] (这个请求会导致不安全)
    cout << "\n=== 测试不安全请求 ===" << endl;
    vector<int> request2 = {3, 3, 0};
    banker.requestResources(4, request2);

    // 测试3：进程0请求资源 [0, 2, 0]
    cout << "\n=== 测试安全请求 ===" << endl;
    vector<int> request3 = {0, 2, 0};
    banker.requestResources(0, request3);

    return 0;
}