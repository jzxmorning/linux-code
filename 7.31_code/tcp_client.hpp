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
class tcp_client
{
public:
    tcp_client(std::string ip, uint16_t port)
        : _ip(ip), _port(port)
    {
        _sock = socket(AF_INET, SOCK_STREAM, 0); // 不能写 int _sock，那样是局部变量，成员永远不会被赋值
        if (_sock < 0)
        {
            LOG(LogLevel::ERROR) << "socket error";
            exit(SOCKET_ERROR);
        }
    }
    bool Connect()
    {
        struct sockaddr_in peer;
        memset(&peer, 0, sizeof(peer));
        peer.sin_addr.s_addr = inet_addr(_ip.c_str());
        peer.sin_family = AF_INET;
        peer.sin_port = htons(_port);
        int n = connect(_sock, COVE(&peer), sizeof(peer));
        if (n < 0)
        {
            LOG(LogLevel::ERROR) << "connect error: " << strerror(errno);
            exit(CONNECT_ERROR);
        }
        LOG(LogLevel::INFO) << "connect success";
        return true;
    }
    bool Write(std::string buf)
    {
        ssize_t n = write(_sock, buf.c_str(), buf.size()); // 不是 sizeof(buf)，那拿到的是 string 对象的大小
        if (n > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Read(std::string *buf)
    {
        char temp[1024];
        ssize_t n = read(_sock, temp, sizeof(temp));
        if (n > 0)
        {
            buf->assign(temp, n);
            return true;
        }
        else
        {
            LOG(LogLevel::ERROR) << "read error";
            return false;
        }
    }

private:
    std::string _ip;
    uint16_t _port;
    int _sock;
};