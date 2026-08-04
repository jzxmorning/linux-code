#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../comm/util.hpp"
#include "../comm/Log.hpp"
using namespace util;
using namespace LogMoudle;
class Compile
{
public:
    Compile()
    {
    }
    ~Compile()
    {
    }

public:
    static bool my_compile(const std::string &file_name)
    {
        pid_t id = fork();
        if (id < 0)
        {
            LOG(LogLevel::ERROR) << "fork error";
            return false;
        }
        else if (id == 0)
        {
            // child
            // 进行进程替换
            umask(0);
            int open_error = open(PathUtil::CompilerError(file_name).c_str(), O_CREAT | O_WRONLY, 0644);
            if (open_error < 0)
            {
                LOG(LogLevel::ERROR) << "open error";
                exit(1);
            }
            dup2(open_error, 2);
            execlp("g++", "g++", "-o", PathUtil::Exe(file_name).c_str(), PathUtil::Src(file_name).c_str(), nullptr);
            LOG(LogLevel::ERROR) << "execlp error";
            exit(2);
        }
        else
        {
            waitpid(id, nullptr, 0);
            if (FileUtil::IsFileExists(PathUtil::Exe(file_name)))
            {
                LOG(LogLevel::INFO) << PathUtil::Src(file_name) << "编译成功";
                return true;
            }
            else
            {
                LOG(LogLevel::DEBUG)<<"编译失败，没有形成可执⾏程序";
                return false;
            }
        }
    }
};