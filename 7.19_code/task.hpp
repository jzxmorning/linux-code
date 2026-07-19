#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

#define __MAIN__

/////////////////////////////任务测试代码///////////////////////////////////////
// 定义任务类型：无参数无返回值的函数对象
using task_t = std::function<void()>;

// 具体任务1：打印日志（带进程ID标识）
void PrintLog()
{
    std::cout << "我是一个打印日志的任务, pid" << getpid() << std::endl;
}

// 具体任务2：模拟下载
void DownLoad()
{
    std::cout << "我是一个下载任务, pid" << getpid() << std::endl;
}

// 具体任务3：模拟访问MySQL
void ReadMysql()
{
    std::cout << "我是一个访问数据库的任务, pid" << getpid() << std::endl;
}

// 具体任务4：模拟访问Redis
void WriteRedies()
{
    std::cout << "我是一个访问redies的任务, pid" << getpid() << std::endl;
}

// 全局任务列表：存储所有可执行的任务
std::vector<task_t> gtasks;
// 加载所有任务到全局列表
void LoadTask()
{
    gtasks.push_back(PrintLog);
    gtasks.push_back(DownLoad);
    gtasks.push_back(ReadMysql);
    gtasks.push_back(WriteRedies);
}
void RandomTask(std::vector<int>* out)
{
    for(int i = 0; i < 50; i++)
    {
        // 随机选择任务（0~3）
        int code = rand() % gtasks.size();
        usleep(23223); // 模拟任务产生的时间间隔
        out->push_back(code);
    }
}
