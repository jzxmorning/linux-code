#pragma once

#include <iostream>
#include <fstream>
#include <string>
class Uli
{
public:
    static bool ReadOneLine(std::string text, std::string *ret, const std::string &sep)
    {
        auto pos = text.find(sep);
        if (pos == std::string::npos)
            return false;
        *ret = text.substr(0, pos);
        text.erase(0, pos + sep.size());
        return true;
    }
    static bool ReadFileContent(std::string path,std::string *_text)
    {
        std::ifstream in(path);
        if(!in.is_open())
        {
            return false;
        }
        std::string line; 
        while(getline(in,line))
        {
            *_text+=line;
        }
        in.close();
        return true;
    }
};
