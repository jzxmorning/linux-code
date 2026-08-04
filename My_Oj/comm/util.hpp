#pragma once
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
namespace util
{
    const std::string temp_path = "./temp/";
    class PathUtil
    {
    public:
        PathUtil()
        {
        }
        ~PathUtil()
        {
        }

    public:
        static std::string AddSuffix(const std::string &file_name, const std::string &suffix)
        {
            std::string path_name = temp_path;
            path_name += file_name;
            path_name += suffix;
            return path_name;
        }
        static std::string Src(const std::string &file_name)
        {
            return AddSuffix(file_name, ".cpp");
        }
        static std::string Exe(const std::string &file_name)
        {
            return AddSuffix(file_name, ".exe");
        }
        static std::string CompilerError(const std::string &file_name)
        {
            return AddSuffix(file_name, ".stderror");
        }
    };
    class FileUtil
    {
    public:
        FileUtil()
        {
        }
        ~FileUtil()
        {
        }

    public:
        static bool IsFileExists(const std::string &file_name)
        {
            struct stat st;
            if (stat(file_name.c_str(), &st) == 0)
            {
                return true;
            }
            return false;
        }
    };
};