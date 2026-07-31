#pragma once
#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Log.hpp"
#include "Com.hpp"
#include "Inadder.hpp"
using namespace LogMoudle;
using namespace MutexModule;
const static int default_backlog = 6;
class tcp_server : public nocopy
{
public:
    tcp_server(uint16_t port)
        : _isrunning(false), _listensock(-1), _port(port) // 顺序须与下面成员声明一致
    {
    }
    void Init()
    {
        _listensock = socket(AF_INET, SOCK_STREAM, 0);
        if (_listensock < 0)
        {
            LOG(LogLevel::ERROR) << "socket errror";
            exit(SOCKET_ERROR);
        }
        LOG(LogLevel::INFO) << "socket success";
        struct sockaddr_in peer;
        memset(&peer, 0, sizeof(peer));
        peer.sin_addr.s_addr = htonl(INADDR_ANY);
        peer.sin_family = AF_INET;
        peer.sin_port = htons(_port);
        int n = bind(_listensock, (struct sockaddr *)&peer, sizeof(peer));
        if (n < 0)
        {
            LOG(LogLevel::ERROR) << "Bind error";
            exit(BIND_ERROR);
        }
        LOG(LogLevel::INFO) << "Bind success";
        int k = listen(_listensock, default_backlog);
        if (k < 0)
        {
            LOG(LogLevel::ERROR) << "listen error";
            exit(LISTEN_ERROR);
        }
        LOG(LogLevel::INFO) << "listen success";
    }
    void Start()
    {
        _isrunning = true;
        while (_isrunning == true)
        {
            struct sockaddr_in temp;
            socklen_t len = sizeof(temp);
            int sock = accept(_listensock, COVE(&temp), &len);
            if (sock < 0)
            {
                LOG(LogLevel::ERROR) << "accept error";
                continue;
            }
            LOG(LogLevel::INFO) << "accept success";
            pid_t n = fork();
            if (n < 0)
            {
                LOG(LogLevel::ERROR) << "fork error";
                exit(FORK_ERROR);
            }
            else if (n == 0)
            {
                // child
                close(_listensock);
                if (fork() != 0)
                {
                    exit(0);
                }
                Server(sock);
                close(sock);
                exit(0); // 孙子干完必须退出，否则会回到 while 里对已关闭的 _listensock 做 accept
            }
            else
            {
                // father
                close(sock);
                pid_t rid = waitpid(n, nullptr, 0);
                if (rid == n)
                {
                    // do nothing
                }
            }
        }
    }
    void Server(int sock)
    {
        char buffer[1024];
        while (true)
        {
            ssize_t n = read(sock, buffer, sizeof(buffer) - 1);
            if (n > 0)
            {
                buffer[n] = 0;
                std::cout << "Client say#" << buffer << std::endl;
                std::string echo_string = "server echo# ";
                echo_string += buffer;
                write(sock, echo_string.c_str(), echo_string.size());
            }
            else if (n == 0)
            {
                LOG(LogLevel::INFO) << "客户端退出,我也退出";
                break;
            }
            else
            {
                break;
            }
        }
    }

private:
    bool _isrunning;
    int _listensock;
    uint16_t _port;
};