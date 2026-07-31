#pragma once
#include <iostream>
#include <string>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
class Inadder
{
public:
    Inadder()
    {
    }
    Inadder(struct sockaddr_in &in)
    {
        Setadder(in);
    }
    Inadder(std::string ip, uint16_t port)
        : _ip(ip), _port(port)
    {
        memset(&_addr, 0, sizeof(_addr));
        _addr.sin_port = htons(_port);
        _addr.sin_family = AF_INET;
        inet_pton(AF_INET, _ip.c_str(), &_addr.sin_addr);
    }
    Inadder(uint16_t port)
        : _ip(), _port(port)
    {
        memset(&_addr, 0, sizeof(_addr));
        _addr.sin_port = htons(_port);
        _addr.sin_family = AF_INET;
        _addr.sin_addr.s_addr = INADDR_ANY;
    }
    void Setadder(struct sockaddr_in &in)
    {
        _addr = in;
        _port = ntohs(in.sin_port);
        char ipbuffer[64];
        inet_ntop(AF_INET, &_addr.sin_addr, ipbuffer, sizeof(_addr));
        _ip = ipbuffer;
    }
    std::string IP()
    {
        return _ip;
    }
    uint16_t Port()
    {
        return _port;
    }
    struct sockaddr_in *Addr()
    {
        return &_addr;
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