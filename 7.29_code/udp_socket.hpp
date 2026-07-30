#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class udp_socket
{
public:
    udp_socket(int fd = -1)
        : _fd(fd) {}
    bool Socket()
    {
        _fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_fd < 0)
        {
            perror("socket ,error");
            return false;
        }
        return true;
    }
    bool Bind(uint16_t port, std::string ip = INADDR_ANY)
    {
        struct sockaddr_in peer;
        peer.sin_family = AF_INET;
        peer.sin_port = ntohs(port);
        peer.sin_addr.s_addr = inet_addr(ip.c_str());
        int ret = bind(_fd, (struct sockaddr *)&peer, sizeof(peer));
        if (ret < 0)
        {
            perror("bind error");
            return false;
        }
        return true;
    }
    bool RecvFrom(std::string *buf, std::string *ip = NULL, uint16_t *port = NULL)
    {
        char buffer[1024];
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        ssize_t n = recvfrom(_fd, buffer, sizeof(buf) - 1, 0, (struct sockaddr *)&temp, &len);
        if (n < 0)
        {
            perror("revform error");
            return false;
        }
        buf->assign(buffer, n);
        if (ip != NULL)
        {
            *ip = inet_ntoa(temp.sin_addr);
        }
        if (port != NULL)
        {
            *port = ntohs(temp.sin_port);
        }
    }
    bool SendTo(std::string &buf, const std::string &ip, uint16_t port)
    {
        struct sockaddr_in peer;
        peer.sin_family = AF_INET;
        peer.sin_port = ntohs(port);
        peer.sin_addr.s_addr = inet_addr(ip.c_str());
        ssize_t n = sendto(_fd, buf.c_str(), buf.size(), 0, (struct sockaddr *)&peer, sizeof(peer));
        if (n < 0)
        {
            perror("sendto error");
            return false;
        }
        return true;
    }
    bool Close()
    {
        close(_fd);
        return true;
    }

private:
    int _fd;
};