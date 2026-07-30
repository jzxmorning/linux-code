#include "udp_server.hpp"
#include <unordered_map>
#include<iostream>
std::unordered_map<std::string, std::string> g_dict;
void fun(std::string rep, std::string *resp)
{
   auto it = g_dict.find(rep);
   if(it==g_dict.end())
   {
    *resp="没找到";
   }else
   {
    *resp=it->second;
   }
}
void Inint()
{
    std::cout<<"正在下载数据中....."<<std::endl;
    sleep(1);
    g_dict.insert(std::make_pair("hello", "你好"));
    g_dict.insert(std::make_pair("world", "世界"));
    g_dict.insert(std::make_pair("c++", "最好的编程语⾔"));
    g_dict.insert(std::make_pair("xsy", "晨虾"));
    g_dict.insert(std::make_pair("laq", "蛋哥"));
    g_dict.insert(std::make_pair("hch", "行吧"));
    g_dict.insert(std::make_pair("jzx", "彭于晏"));
    std::cout<<"下载完毕..."<<std::endl;
}

int main()
{
    udp_server Serve;
    std::string ip = "0.0.0.0";
    uint16_t port = 8080;
    Inint();
    Serve.Start(ip, port, fun);
    return 0;
}