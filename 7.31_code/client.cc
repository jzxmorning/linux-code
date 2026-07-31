#include "tcp_client.hpp"
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "use error" << std::endl;
        std::cout << "携带服务器的ip和端口号" << std::endl;
        exit(1);
    }
    Enable_Console_Log_Strategy();
    tcp_client Client(argv[1], std::atoi(argv[2]));
    Client.Connect();
    while (true)
    {
        std::cout << "请输入#" << std::endl;
        std::string message;
        std::cin >> message;
        if (!std::cin)
        {
            break;
        }
        bool ret = Client.Write(message);
        if (ret == true)
        {
            std::string res;
            Client.Read(&res);
            std::cout << res << std::endl;
        }
    }
    return 0;
}