#include "tcp_server.hpp"

// usage: ./server 8888
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " local-port" << std::endl;
        return 1;
    }
    Enable_Console_Log_Strategy();

    uint16_t port = static_cast<uint16_t>(std::stoi(argv[1]));
    tcp_server Server(port); // 传实参，不是 uint16_t port
    Server.Init();
    Server.Start();

    return 0;
}
