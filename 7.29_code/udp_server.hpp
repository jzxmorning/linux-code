#pragma once
#include "udp_socket.hpp"
#include <functional>
typedef std::function<void(const std::string &, std::string *resp)> Handler;
class udp_server
{
public:
    udp_server()
    {
        assert(_sock.Socket());
    }
    ~udp_server()
    {
        _sock.Close();
    }
    bool Start(std::string ip, uint16_t port, Handler handler)
    {
        bool ret = _sock.Bind(port, ip);
        if (!ret)
        {
            return false;
        }
        while (1)
        {
            std::string rcv;
            std::string rcvip;
            uint16_t rcvport;
            bool res = _sock.RecvFrom(&rcv, &rcvip, &rcvport);
            if (!res)
            {
                continue;
            }
            std::string resp;
            handler(rcv, &resp);
            _sock.SendTo(resp, rcvip, rcvport);
            printf("[%s:%d] req: %s, resp: %s\n", rcvip.c_str(), rcvport,
                   rcv.c_str(), resp.c_str());
        }
        _sock.Close();
        return true;
    }

private:
    udp_socket _sock;
};
