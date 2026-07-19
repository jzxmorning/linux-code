#pragma once
#include <iostream>
#include <vector>
#include "Channel.hpp"
#include "task.hpp"
class ProcesspPool
{
public:
    ProcesspPool(int num)
        : _num(num), next_choice(0)
    {
    }
    int Next()
    {
        int new_choice = next_choice;
        next_choice++;
        next_choice = next_choice % _num;
        return new_choice;
    }
    void Start()
    {
        for (int i = 0; i < _num; i++)
        {
            int fd[2] = {0};
            int k = pipe(fd);
            if (k < 0)
            {
                perror("pipe error");
                exit(1);
            }
            int n = fork();
            if (n < 0)
            {
                perror("fork error");
                exit(1);
            }
            else if (n == 0)
            {
                // 子进程 读端 关闭写端
                for(auto&v:channels)
                {
                   v.Close();
                }
                close(fd[1]);
                // 进入工作
                Work(fd[0]);
                // 工作结束
                close(fd[0]);
                // 正常退出
                exit(0);
            }
            else
            {
                // 父进程 关闭读端
                close(fd[0]);
                channels.emplace_back(fd[1], n);
            }
        }
    }
    void Work(int fd)
    {
        while (1)
        {
            int tasknode = 0;
            ssize_t n = read(fd, &tasknode, sizeof(tasknode));
            if (n > 0 && n == sizeof(int)) // 成功获取到任务码
            {
                if (tasknode >= 0 && tasknode < (int)gtasks.size())
                {
                    gtasks[tasknode]();
                }
            }
            else if (n == 0)
            {
                break;
            }
            else
            {
                break;
            }
        }
    }
    void Stop()
    {
        for (auto &ch : channels)
        {
            ch.Close();
            std::cout << ch.GetName() << " close success!" << std::endl;
        }
        sleep(3);
        for (auto &ch : channels)
        {
            ch.Wait();
            std::cout << ch.GetName() << " wait success!" << std::endl;
        }
    }
    void PushTask(int tasknode)
    {
        int op = Next();
        channels[op].Send_Task(tasknode);
        std::cout << "发送了一个任务 -> " << channels[op].GetName() << std::endl;
    }

private:
    int _num;
    int next_choice;
    std::vector<Channel> channels;
};