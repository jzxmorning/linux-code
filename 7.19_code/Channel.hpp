#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
class Channel
{
public:
    Channel(int fd, pid_t pid)
        : w_fd(fd), _pid(pid)
    {
        _name = "Channel" + std::to_string(_pid) + "-" + std::to_string(w_fd);
    }
    int Fd() // 获取写端
    {
        return w_fd;
    }
    std::string GetName() // 获取管道名称
    {
        return _name;
    }
    void Close() // 关闭写端
    {
        if (w_fd > 0)
        {
            ::close(w_fd);
        }
    }
    void Wait() // 回收资源
    {
        waitpid(_pid, nullptr, 0);
    }
    void Send_Task(int tasknode) // 发送任务码
    {
        write(w_fd, &tasknode, sizeof(tasknode));
    }
    ~Channel()
    {
    }

private:
    std::string _name;
    int w_fd;
    pid_t _pid;
};