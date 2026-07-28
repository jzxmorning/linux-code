#include <iostream>
#include <cerrno>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
void Usage(const std::string &process)
{
    std::cout << "Usage: " << process << " server_ip server_port" << std::endl;
}
// ./udp_client server_ip server_port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        return 1;
    }
    std::string server_ip = argv[1];
    uint16_t server_port = std::stoi(argv[2]);
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("socket error");
        exit(1);
    }
    std::cout << "create socket success: " << sock << std::endl;
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip.c_str());
    while (true)
    {
        std::string buf;
        std::cout << "Please Enter #";
        std::getline(std::cin, buf);
        ssize_t n = sendto(sock, buf.c_str(), buf.size(), 0, (struct sockaddr *)&server, sizeof(server));
        if (n > 0)
        {
            char buffer[1024];
            struct sockaddr_in temp;
            socklen_t len = sizeof(temp);
            ssize_t m = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&temp, &len);
            if (m > 0)
            {
                buffer[n] = 0;
                std::cout << "Server Echo #" << buffer << std::endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    return 0;
}
