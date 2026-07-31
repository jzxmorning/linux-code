#pragma once
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class Inadder 
{
public:
    Inadder(struct sockaddr_in &in)
        : _addr(in)
    {
        _port = ntohs(_addr.sin_port);
        _ip = inet_ntoa(_addr.sin_addr);
    }
    std::string IP()
    {
        return _ip;
    }
    uint16_t Port()
    {
        return _port;
    }
    std::string Debug()
    {
        return _ip + ":" + std::to_string(_port);
    }
    ~Inadder()
    {
    }

private:
    std::string _ip;
    uint16_t _port;
    struct sockaddr_in _addr;
};