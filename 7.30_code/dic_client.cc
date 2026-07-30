#include "udp_client.hpp"
#include <iostream>
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "use error" << std::endl;
        std::cout << "携带服务器的ip和端口号" << std::endl;
        exit(1);
    }
    udp_client Client(argv[1], atoi(argv[2]));
    while (1)
    {
        std::cout << "请输入你要翻译的单词 #" << std::endl;
        std::string word;
        std::cin >> word;
        if (!std::cin)
        {
            std::cout << "用户退出" << std::endl;
            break;
        }
        Client.SendTo(word);
        std::string result;
        Client.RcvForm(&result);
        std::cout << word << " 意思是 " << result << std::endl;
    }

    return 0;
}