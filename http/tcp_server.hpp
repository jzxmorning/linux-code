#include "Socket.hpp"
#include <sys/wait.h>
#include <functional>
using namespace SocketModule;
using ioservice_t = std::function<void(std::shared_ptr<Socket> &sock, Inadder &client)>;
class Tcp_Server
{
public:
    Tcp_Server(uint16_t port)
        : _port(port), _listensockptr(std::make_unique<TcpSocket>()), _isrunning(false)
    {
        _listensockptr->BuildTcpSocketMethod(_port);
    }
    ~Tcp_Server() {}
    void Start(ioservice_t callback)
    {
        _isrunning = true;
        while (_isrunning)
        {
            Inadder client;
            auto sock = _listensockptr->Accept(&client);
            if (sock == nullptr)
            {
                continue;
            }
            LOG(LogLevel::INFO) << "accept success..  " << client.Debug();
            pid_t fd = fork();
            if (fd < 0)
            {
                LOG(LogLevel::ERROR) << "fork error";
                exit(FORK_ERROR);
            }
            else if (fd == 0)
            {
                _listensockptr->Close();
                if (fork() > 0)
                {
                    exit(OK);
                }
                callback(sock, client);
                sock->Close();
                exit(OK);
            }
            else
            {
                sock->Close();
                pid_t rid = ::waitpid(fd, nullptr, 0);
                (void)rid;
            }
        }
        _isrunning = false;
    }

private:
    uint16_t _port;
    std::unique_ptr<Socket> _listensockptr;
    bool _isrunning;
};