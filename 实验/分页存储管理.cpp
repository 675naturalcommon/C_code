/**
 * 分页存储管理系统
 * 实现逻辑地址到物理地址的转换
 * 包括页表管理、越界检查、内存空间模拟等功能
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

// 页表项结构体
struct PageTableEntry {
    int pageNumber;     // 页号
    int blockNumber;    // 块号
    bool valid;         // 有效位
    bool modified;      // 修改位
    bool referenced;    // 引用位

    PageTableEntry() : pageNumber(-1), blockNumber(-1), valid(false), modified(false), referenced(false) {}
};

// 内存块结构体
struct MemoryBlock {
    int blockNumber;    // 块号
    bool allocated;     // 是否已分配
    int processId;      // 占用进程ID
    int pageNumber;     // 占用页号

    MemoryBlock() : blockNumber(-1), allocated(false), processId(-1), pageNumber(-1) {}
};

// 分页存储管理类
class PagingMemoryManager {
private:
    int pageSize;               // 页面大小（字节）
    int totalMemorySize;        // 总内存大小（字节）
    int totalBlocks;            // 总块数
    int totalPages;             // 总页数
    int processMemorySize;      // 进程内存需求大小（字节）

    vector<PageTableEntry> pageTable;   // 页表
    vector<MemoryBlock> memoryBlocks;   // 内存块

public:
    // 构造函数
    PagingMemoryManager(int pageSize, int totalMemory, int processMemory) {
        this->pageSize = pageSize;
        this->totalMemorySize = totalMemory;
        this->processMemorySize = processMemory;

        // 计算总块数和总页数
        totalBlocks = totalMemorySize / pageSize;
        totalPages = processMemorySize / pageSize;

        // 如果进程内存需求不能整除页面大小，需要额外一页
        if (processMemorySize % pageSize != 0) {
            totalPages++;
        }

        // 初始化页表
        pageTable.resize(totalPages);
        for (int i = 0; i < totalPages; i++) {
            pageTable[i].pageNumber = i;
        }

        // 初始化内存块
        memoryBlocks.resize(totalBlocks);
        for (int i = 0; i < totalBlocks; i++) {
            memoryBlocks[i].blockNumber = i;
        }

        cout << "分页存储管理系统初始化完成！" << endl;
        cout << "页面大小: " << pageSize << " 字节" << endl;
        cout << "总内存大小: " << totalMemorySize << " 字节" << endl;
        cout << "进程内存需求: " << processMemorySize << " 字节" << endl;
        cout << "总块数: " << totalBlocks << endl;
        cout << "总页数: " << totalPages << endl;
    }

    // 分配内存给进程
    bool allocateMemory(int processId) {
        cout << "\n=== 为进程 " << processId << " 分配内存 ===" << endl;

        // 显示初始值
        cout << "\n【初始值】" << endl;
        cout << "进程ID: " << processId << endl;
        cout << "进程内存需求: " << processMemorySize << " 字节" << endl;
        cout << "页面大小: " << pageSize << " 字节" << endl;
        cout << "总内存大小: " << totalMemorySize << " 字节" << endl;
        cout << "总块数: " << totalBlocks << endl;

        int pagesNeeded = totalPages;
        int allocatedBlocks = 0;

        cout << "\n【计算所需页面数】" << endl;
        cout << "所需页面数 = 进程内存需求 / 页面大小" << endl;
        cout << "所需页面数 = " << processMemorySize << " / " << pageSize << " = " << pagesNeeded << " 页" << endl;

        // 检查是否有足够的空闲块
        cout << "\n【检查内存可用性】" << endl;
        cout << "扫描内存块，统计可用块数..." << endl;
        for (int i = 0; i < totalBlocks && allocatedBlocks < pagesNeeded; i++) {
            if (!memoryBlocks[i].allocated) {
                allocatedBlocks++;
            }
        }

        cout << "可用块数: " << allocatedBlocks << " 个" << endl;
        cout << "需要块数: " << pagesNeeded << " 个" << endl;

        if (allocatedBlocks < pagesNeeded) {
            cout << "\n❌ 错误：内存不足！需要 " << pagesNeeded << " 个块，但只有 " << allocatedBlocks << " 个可用块。" << endl;
            return false;
        }
        cout << "✅ 内存足够，可以分配" << endl;

        // 分配内存块
        cout << "\n【分配内存块】" << endl;
        allocatedBlocks = 0;
        for (int i = 0; i < totalBlocks && allocatedBlocks < pagesNeeded; i++) {
            if (!memoryBlocks[i].allocated) {
                // 分配内存块
                memoryBlocks[i].allocated = true;
                memoryBlocks[i].processId = processId;
                memoryBlocks[i].pageNumber = allocatedBlocks;

                // 更新页表
                pageTable[allocatedBlocks].blockNumber = i;
                pageTable[allocatedBlocks].valid = true;
                pageTable[allocatedBlocks].modified = false;
                pageTable[allocatedBlocks].referenced = false;

                cout << "分配: 页 " << allocatedBlocks << " -> 块 " << i << endl;
                allocatedBlocks++;
            }
        }

        cout << "\n【运行结果】" << endl;
        cout << "✅ 成功为进程 " << processId << " 分配 " << pagesNeeded << " 个页面！" << endl;
        cout << "页表已建立，可以开始地址转换" << endl;
        return true;
    }

    // 逻辑地址到物理地址转换
    bool logicalToPhysical(int logicalAddress, int& physicalAddress) {
        cout << "\n=== 逻辑地址转换 ===" << endl;
        cout << "输入逻辑地址: " << logicalAddress << endl;

        // 显示初始值
        cout << "\n【初始值】" << endl;
        cout << "页面大小: " << pageSize << " 字节" << endl;
        cout << "逻辑地址: " << logicalAddress << endl;

        // 计算页号和页内偏移
        cout << "\n【运算过程】" << endl;
        cout << "1. 计算页号: 逻辑地址 / 页面大小" << endl;
        cout << "   页号 = " << logicalAddress << " / " << pageSize << " = " << (logicalAddress / pageSize) << endl;
        int pageNumber = logicalAddress / pageSize;

        cout << "2. 计算页内偏移: 逻辑地址 % 页面大小" << endl;
        cout << "   页内偏移 = " << logicalAddress << " % " << pageSize << " = " << (logicalAddress % pageSize) << endl;
        int offset = logicalAddress % pageSize;

        cout << "\n【中间结果】" << endl;
        cout << "页号: " << pageNumber << ", 页内偏移: " << offset << endl;

        // 检查页号是否越界
        cout << "\n【边界检查】" << endl;
        cout << "检查页号 " << pageNumber << " 是否在有效范围内 [0, " << (totalPages - 1) << "]" << endl;
        if (pageNumber < 0 || pageNumber >= totalPages) {
            cout << "❌ 错误：页号 " << pageNumber << " 越界！有效页号范围: 0 ~ " << (totalPages - 1) << endl;
            return false;
        }
        cout << "✅ 页号在有效范围内" << endl;

        // 检查页表项是否有效
        cout << "\n【页表项检查】" << endl;
        cout << "检查页 " << pageNumber << " 是否在内存中" << endl;
        if (!pageTable[pageNumber].valid) {
            cout << "❌ 错误：页 " << pageNumber << " 不在内存中！" << endl;
            return false;
        }
        cout << "✅ 页 " << pageNumber << " 在内存中" << endl;

        // 获取块号
        cout << "\n【获取块号】" << endl;
        int blockNumber = pageTable[pageNumber].blockNumber;
        cout << "从页表获取块号: 页 " << pageNumber << " -> 块 " << blockNumber << endl;

        // 计算物理地址
        cout << "\n【计算物理地址】" << endl;
        cout << "物理地址 = 块号 × 页面大小 + 页内偏移" << endl;
        cout << "物理地址 = " << blockNumber << " × " << pageSize << " + " << offset << endl;
        physicalAddress = blockNumber * pageSize + offset;
        cout << "物理地址 = " << physicalAddress << endl;

        // 更新页表引用位
        pageTable[pageNumber].referenced = true;
        cout << "✅ 更新页 " << pageNumber << " 的引用位" << endl;

        cout << "\n【运行结果】" << endl;
        cout << "逻辑地址 " << logicalAddress << " 成功转换为物理地址 " << physicalAddress << endl;
        cout << "转换公式: 物理地址 = " << blockNumber << " × " << pageSize << " + " << offset << " = " << physicalAddress << endl;

        return true;
    }

    // 显示页表
    void displayPageTable() {
        cout << "\n=== 页表内容 ===" << endl;
        cout << setw(8) << "页号" << setw(8) << "块号" << setw(8) << "有效"
             << setw(8) << "修改" << setw(8) << "引用" << endl;
        cout << string(40, '-') << endl;

        for (int i = 0; i < totalPages; i++) {
            cout << setw(8) << pageTable[i].pageNumber
                 << setw(8) << (pageTable[i].valid ? to_string(pageTable[i].blockNumber) : "-")
                 << setw(8) << (pageTable[i].valid ? "是" : "否")
                 << setw(8) << (pageTable[i].modified ? "是" : "否")
                 << setw(8) << (pageTable[i].referenced ? "是" : "否") << endl;
        }
    }

    // 显示内存状态
    void displayMemoryStatus() {
        cout << "\n=== 内存状态 ===" << endl;
        cout << setw(8) << "块号" << setw(12) << "状态" << setw(12) << "进程ID" << setw(12) << "页号" << endl;
        cout << string(44, '-') << endl;

        for (int i = 0; i < totalBlocks; i++) {
            cout << setw(8) << memoryBlocks[i].blockNumber
                 << setw(12) << (memoryBlocks[i].allocated ? "已分配" : "空闲")
                 << setw(12) << (memoryBlocks[i].allocated ? to_string(memoryBlocks[i].processId) : "-")
                 << setw(12) << (memoryBlocks[i].allocated ? to_string(memoryBlocks[i].pageNumber) : "-") << endl;
        }
    }

    // 修改页表项
    void modifyPage(int pageNumber, bool modified) {
        if (pageNumber >= 0 && pageNumber < totalPages && pageTable[pageNumber].valid) {
            pageTable[pageNumber].modified = modified;
            cout << "页 " << pageNumber << " 修改位已设置为: " << (modified ? "是" : "否") << endl;
        } else {
            cout << "错误：无效的页号或页不在内存中！" << endl;
        }
    }

    // 获取系统信息
    void displaySystemInfo() {
        cout << "\n=== 系统信息 ===" << endl;
        cout << "页面大小: " << pageSize << " 字节" << endl;
        cout << "总内存大小: " << totalMemorySize << " 字节" << endl;
        cout << "进程内存需求: " << processMemorySize << " 字节" << endl;
        cout << "总块数: " << totalBlocks << endl;
        cout << "总页数: " << totalPages << endl;

        // 计算地址位数
        int logicalAddressBits = 0;
        int temp = processMemorySize - 1;
        while (temp > 0) {
            temp >>= 1;
            logicalAddressBits++;
        }

        int pageBits = 0;
        temp = pageSize - 1;
        while (temp > 0) {
            temp >>= 1;
            pageBits++;
        }

        cout << "逻辑地址位数: " << logicalAddressBits << " 位" << endl;
        cout << "页内偏移位数: " << pageBits << " 位" << endl;
        cout << "页号位数: " << (logicalAddressBits - pageBits) << " 位" << endl;
    }
};

// 显示菜单
void displayMenu() {
    cout << "\n=== 分页存储管理系统菜单 ===" << endl;
    cout << "1. 显示系统信息" << endl;
    cout << "2. 分配内存给进程" << endl;
    cout << "3. 逻辑地址转换" << endl;
    cout << "4. 显示页表" << endl;
    cout << "5. 显示内存状态" << endl;
    cout << "6. 修改页表项" << endl;
    cout << "7. 退出" << endl;
    cout << "请选择操作 (1-7): ";
}

int main() {
    cout << "=== 分页存储管理系统 ===" << endl;

    // 硬编码系统参数
    int pageSize = 4096;        // 4KB页面大小
    int totalMemorySize = 65536; // 64KB总内存
    int processMemorySize = 16384; // 16KB进程内存需求

    // 创建分页存储管理器
    PagingMemoryManager manager(pageSize, totalMemorySize, processMemorySize);

    int choice;
    int processId = 1;
    bool memoryAllocated = false;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                manager.displaySystemInfo();
                break;

            case 2:
                if (manager.allocateMemory(processId)) {
                    memoryAllocated = true;
                    processId++;
                }
                break;

            case 3:
                if (!memoryAllocated) {
                    cout << "错误：请先为进程分配内存！" << endl;
                    break;
                }
                int logicalAddress;
                cout << "请输入逻辑地址: ";
                cin >> logicalAddress;

                int physicalAddress;
                if (manager.logicalToPhysical(logicalAddress, physicalAddress)) {
                    cout << "转换成功！物理地址: " << physicalAddress << endl;
                } else {
                    cout << "地址转换失败！" << endl;
                }
                break;

            case 4:
                manager.displayPageTable();
                break;

            case 5:
                manager.displayMemoryStatus();
                break;

            case 6:
                if (!memoryAllocated) {
                    cout << "错误：请先为进程分配内存！" << endl;
                    break;
                }
                int pageNum;
                bool modified;
                cout << "请输入要修改的页号: ";
                cin >> pageNum;
                cout << "是否修改 (0-否, 1-是): ";
                cin >> modified;
                manager.modifyPage(pageNum, modified);
                break;

            case 7:
                cout << "感谢使用分页存储管理系统！" << endl;
                break;

            default:
                cout << "无效选择，请重新输入！" << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}
