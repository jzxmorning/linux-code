#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include "Com.hpp"
#include "Log.hpp"
#include "Inadder.hpp"
namespace SocketModule
{
    using namespace LogMoudle;
    using namespace MutexModule;
    const static int gbacklog = 6;
    class Socket
    {
    public:
        virtual ~Socket() {}
        virtual void SocketOrDie() = 0;
        virtual void BindOrDie(uint16_t port) = 0;
        virtual void ListenOrDie(int backlog) = 0;
        virtual std::shared_ptr<Socket> Accept(Inadder *client) = 0;
        virtual void Close() = 0;
        virtual int Recv(std::string *out) = 0;
        virtual int Send(const std::string &message) = 0;
        virtual int Connect(const std::string &server_ip, uint16_t port) = 0;

    public:
        void BuildTcpSocketMethod(uint16_t port, int backlog = gbacklog)
        {
            SocketOrDie();
            BindOrDie(port);
            ListenOrDie(backlog);
        }
    };
    const static int defaultfd = -1;
    class TcpSocket : public Socket
    {
    public:
        TcpSocket() : _sockfd(defaultfd)
        {
        }
        TcpSocket(int fd) : _sockfd(fd)
        {
        }
        ~TcpSocket() {}
        void SocketOrDie() override
        {
            _sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (_sockfd < 0)
            {
                LOG(LogLevel::ERROR) << "socket error";
                exit(SOCKET_ERROR);
            }
            int opt = 1;
            setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            LOG(LogLevel::INFO) << "Socket successs";
        }
        void BindOrDie(uint16_t port) override
        {
            Inadder addr(port);
            int n = bind(_sockfd, COVE(addr.Addr()), sizeof(struct sockaddr_in));
            if (n < 0)
            {
                LOG(LogLevel::ERROR) << "bind error";
                exit(BIND_ERROR);
            }
            LOG(LogLevel::INFO) << "bind success";
        }
        void ListenOrDie(int backlog) override
        {
            int n = listen(_sockfd, backlog);
            if (n < 0)
            {
                LOG(LogLevel::ERROR) << "listen error";
                exit(LISTEN_ERROR);
            }
            LOG(LogLevel::INFO) << "listen success";
        }
        std::shared_ptr<Socket> Accept(Inadder *client) override
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int sock = accept(_sockfd, COVE(&peer), &len);
            if (sock < 0)
            {
                LOG(LogLevel::ERROR) << "accept error";
                return nullptr;
            }
            LOG(LogLevel::INFO) << "accept success";
            client->Setadder(peer);
            return std::make_shared<TcpSocket>(sock);
        }
        void Close() override
        {
            close(_sockfd);
        }
        int Recv(std::string *out) override
        {
            char buf[4096];
            ssize_t n = recv(_sockfd, buf, sizeof(buf) - 1,0);
            if (n > 0)
            {
                buf[n] = 0;
                *out += buf;
            }
            return n;
        }
        int Send(const std::string &message) override
        {
            return send(_sockfd,message.c_str(),message.size(),0);
        }
        int Connect(const std::string &server_ip, uint16_t port) override
        {
            Inadder addr(server_ip,port);
            return connect(_sockfd,COVE(addr.Addr()),sizeof(struct sockaddr_in));
        }
    private:
        int _sockfd;
    };
}