/**
 * 动态分区分配算法模拟程序
 * 实现四种分配算法：首次适应、循环首次适应、最佳适应、最坏适应
 * 以及相应的回收算法
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

// 分区结构体
struct Partition {
    int start;      // 分区起始地址
    int size;       // 分区大小
    bool free;      // 是否空闲
    string process; // 占用进程名（如果被占用）

    Partition(int s, int sz, bool f = true, string p = "")
        : start(s), size(sz), free(f), process(p) {}
};

// 动态分区分配类
class DynamicPartitionAllocator {
private:
    vector<Partition> partitions;  // 分区表
    int totalMemory;               // 总内存大小
    int lastAllocatedIndex;        // 上次分配的位置（用于循环首次适应）

public:
    // 构造函数
    DynamicPartitionAllocator(int totalMem) : totalMemory(totalMem), lastAllocatedIndex(0) {
        // 初始化一个大的空闲分区
        partitions.push_back(Partition(0, totalMemory, true, ""));
    }

    // 显示当前分区状态
    void displayPartitions() {
        cout << "\n当前分区状态：" << endl;
        cout << "起始地址\t大小\t状态\t\t进程" << endl;
        cout << "----------------------------------------" << endl;

        for (const auto& part : partitions) {
            cout << part.start << "\t\t" << part.size << "\t";
            if (part.free) {
                cout << "空闲\t\t-";
            } else {
                cout << "已分配\t\t" << part.process;
            }
            cout << endl;
        }
        cout << endl;
    }

    // 首次适应算法
    bool firstFit(int size, const string& processName) {
        cout << "使用首次适应算法分配 " << size << "KB 给进程 " << processName << endl;

        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i].free && partitions[i].size >= size) {
                allocatePartition(i, size, processName);
                return true;
            }
        }

        cout << "分配失败：没有足够的连续空间" << endl;
        return false;
    }

    // 循环首次适应算法
    bool nextFit(int size, const string& processName) {
        cout << "使用循环首次适应算法分配 " << size << "KB 给进程 " << processName << endl;

        int startIndex = lastAllocatedIndex;
        int currentIndex = startIndex;

        do {
            if (partitions[currentIndex].free && partitions[currentIndex].size >= size) {
                allocatePartition(currentIndex, size, processName);
                lastAllocatedIndex = currentIndex;
                return true;
            }

            currentIndex = (currentIndex + 1) % partitions.size();
        } while (currentIndex != startIndex);

        cout << "分配失败：没有足够的连续空间" << endl;
        return false;
    }

    // 最佳适应算法
    bool bestFit(int size, const string& processName) {
        cout << "使用最佳适应算法分配 " << size << "KB 给进程 " << processName << endl;

        int bestIndex = -1;
        int minSize = totalMemory + 1;  // 初始化为一个很大的值

        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i].free && partitions[i].size >= size) {
                if (partitions[i].size < minSize) {
                    minSize = partitions[i].size;
                    bestIndex = i;
                }
            }
        }

        if (bestIndex != -1) {
            allocatePartition(bestIndex, size, processName);
            return true;
        }

        cout << "分配失败：没有足够的连续空间" << endl;
        return false;
    }

    // 最坏适应算法
    bool worstFit(int size, const string& processName) {
        cout << "使用最坏适应算法分配 " << size << "KB 给进程 " << processName << endl;

        int worstIndex = -1;
        int maxSize = -1;

        for (int i = 0; i < partitions.size(); i++) {
            if (partitions[i].free && partitions[i].size >= size) {
                if (partitions[i].size > maxSize) {
                    maxSize = partitions[i].size;
                    worstIndex = i;
                }
            }
        }

        if (worstIndex != -1) {
            allocatePartition(worstIndex, size, processName);
            return true;
        }

        cout << "分配失败：没有足够的连续空间" << endl;
        return false;
    }

    // 回收分区
    bool freePartition(const string& processName) {
        cout << "回收进程 " << processName << " 占用的分区" << endl;

        for (int i = 0; i < partitions.size(); i++) {
            if (!partitions[i].free && partitions[i].process == processName) {
                // 标记为空闲
                partitions[i].free = true;
                partitions[i].process = "";

                // 合并相邻的空闲分区
                mergeFreePartitions();

                cout << "成功回收进程 " << processName << " 的分区" << endl;
                return true;
            }
        }

        cout << "回收失败：未找到进程 " << processName << " 占用的分区" << endl;
        return false;
    }

private:
    // 分配分区（内部方法）
    void allocatePartition(int index, int size, const string& processName) {
        Partition& part = partitions[index];

        if (part.size == size) {
            // 分区大小正好等于请求大小
            part.free = false;
            part.process = processName;
        } else {
            // 分区大小大于请求大小，需要分割
            Partition newPart(part.start + size, part.size - size, true, "");
            part.size = size;
            part.free = false;
            part.process = processName;

            partitions.insert(partitions.begin() + index + 1, newPart);
        }

        cout << "成功分配 " << size << "KB 给进程 " << processName
             << "，起始地址：" << part.start << endl;
    }

    // 合并相邻的空闲分区（内部方法）
    void mergeFreePartitions() {
        for (int i = 0; i < partitions.size() - 1; i++) {
            if (partitions[i].free && partitions[i+1].free) {
                // 合并相邻的空闲分区
                partitions[i].size += partitions[i+1].size;
                partitions.erase(partitions.begin() + i + 1);
                i--;  // 重新检查当前位置
            }
        }
    }
};

// 演示函数
void demonstrateAllocationAlgorithms() {
    cout << "=== 动态分区分配算法演示 ===" << endl;
    cout << "总内存大小：100KB" << endl;

    // 创建分配器
    DynamicPartitionAllocator allocator(100);

    // 初始状态
    allocator.displayPartitions();

    // 演示首次适应算法
    cout << "\n=== 首次适应算法演示 ===" << endl;
    allocator.firstFit(20, "P1");
    allocator.displayPartitions();

    allocator.firstFit(15, "P2");
    allocator.displayPartitions();

    allocator.firstFit(30, "P3");
    allocator.displayPartitions();

    // 回收一些分区
    cout << "\n=== 回收分区演示 ===" << endl;
    allocator.freePartition("P2");
    allocator.displayPartitions();

    // 演示循环首次适应算法
    cout << "\n=== 循环首次适应算法演示 ===" << endl;
    allocator.nextFit(10, "P4");
    allocator.displayPartitions();

    // 演示最佳适应算法
    cout << "\n=== 最佳适应算法演示 ===" << endl;
    allocator.bestFit(5, "P5");
    allocator.displayPartitions();

    // 演示最坏适应算法
    cout << "\n=== 最坏适应算法演示 ===" << endl;
    allocator.worstFit(25, "P6");
    allocator.displayPartitions();

    // 最终状态
    cout << "\n=== 最终分区状态 ===" << endl;
    allocator.displayPartitions();
}

// 交互式演示
void interactiveDemo() {
    cout << "=== 动态分区分配交互式演示 ===" << endl;

    int totalMemory;
    cout << "请输入总内存大小（KB）：";
    cin >> totalMemory;

    DynamicPartitionAllocator allocator(totalMemory);

    int choice;
    do {
        cout << "\n=== 菜单 ===" << endl;
        cout << "1. 显示当前分区状态" << endl;
        cout << "2. 首次适应算法分配" << endl;
        cout << "3. 循环首次适应算法分配" << endl;
        cout << "4. 最佳适应算法分配" << endl;
        cout << "5. 最坏适应算法分配" << endl;
        cout << "6. 回收分区" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作：";
        cin >> choice;

        switch (choice) {
            case 1:
                allocator.displayPartitions();
                break;

            case 2: {
                int size;
                string process;
                cout << "请输入分配大小（KB）：";
                cin >> size;
                cout << "请输入进程名：";
                cin >> process;
                allocator.firstFit(size, process);
                break;
            }

            case 3: {
                int size;
                string process;
                cout << "请输入分配大小（KB）：";
                cin >> size;
                cout << "请输入进程名：";
                cin >> process;
                allocator.nextFit(size, process);
                break;
            }

            case 4: {
                int size;
                string process;
                cout << "请输入分配大小（KB）：";
                cin >> size;
                cout << "请输入进程名：";
                cin >> process;
                allocator.bestFit(size, process);
                break;
            }

            case 5: {
                int size;
                string process;
                cout << "请输入分配大小（KB）：";
                cin >> size;
                cout << "请输入进程名：";
                cin >> process;
                allocator.worstFit(size, process);
                break;
            }

            case 6: {
                string process;
                cout << "请输入要回收的进程名：";
                cin >> process;
                allocator.freePartition(process);
                break;
            }

            case 0:
                cout << "程序结束" << endl;
                break;

            default:
                cout << "无效选择，请重新输入" << endl;
        }

    } while (choice != 0);
}

int main() {
    cout << "动态分区分配算法模拟程序" << endl;
    cout << "1. 自动演示" << endl;
    cout << "2. 交互式演示" << endl;
    cout << "请选择演示模式：";

    int mode;
    cin >> mode;

    if (mode == 1) {
        demonstrateAllocationAlgorithms();
    } else if (mode == 2) {
        interactiveDemo();
    } else {
        cout << "无效选择" << endl;
    }

    return 0;
}
