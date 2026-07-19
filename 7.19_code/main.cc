#include <iostream>
#include "ProcesspPool.hpp"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "use error" << std::endl;
        return 1;
    }
    int num = std::stoi(argv[1]);
    // 加载任务
    LoadTask();
    std::vector<int> tasknode;
    srand(time(nullptr) ^ getpid());
    RandomTask(&tasknode);
    ProcesspPool p(num);
    // 加载管道
    p.Start();
    for(auto& v:tasknode)
    {
        p.PushTask(v);
        usleep(500000);
    }
    p.Stop();
    return 0;
}