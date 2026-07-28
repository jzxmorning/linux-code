#include <iostream>
#include "Com.hpp"
#include "Log.hpp"
#include "Mutex.hpp"
#include <string>
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Inadder.hpp"
using namespace LogMoudle;
using namespace MutexModule;
const int defaultsockfd = -1;
const int defaultport = 8080;
const int SIZE = 1024;
    class UdpServe : public nocopy
    {
    public:
        UdpServe(int sockfd = defaultsockfd, uint16_t port = defaultport)
            : _sockfd(sockfd), _port(port)
        {
        }
        void Inint()
        {
            _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_sockfd < 0)
            {
                LOG(LogLevel::ERROR) << "socket erroe";
                exit(SOCKET_ERROR);
            }
            LOG(LogLevel::INFO) << "socket success";
            struct sockaddr_in local;
            memset(&local, 0, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(_port);
            local.sin_addr.s_addr = INADDR_ANY;
            int n = ::bind(_sockfd, (struct sockaddr *)&local, sizeof(local));
            if (n < 0)
            {
                LOG(LogLevel::ERROR) << "Bind error";
                exit(BIND_ERROR);
            }
            LOG(LogLevel::INFO) << "Bind success";
        }
        void Start()
        {
            char buffer[SIZE];
            while (1)
            {
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                ssize_t n = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&peer, &len);
                if (n > 0)
                {
                    Inadder add(peer);
                    buffer[n] = 0;
                    std::cout << "[" << add.Debug() << "]" << " # " << buffer << std::endl;
                    sendto(_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&peer, len);
                }
            }
        }
        ~UdpServe()
        {

        }
    private:
        int _sockfd;
        uint16_t _port;
    };