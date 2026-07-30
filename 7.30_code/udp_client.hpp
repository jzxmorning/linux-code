#pragma once
#include"udp_socket.hpp"
class udp_client
{
    public:
    udp_client(const std::string& ip, uint16_t port)
    :_ip(ip)
    ,_port(port)
    {
        assert(_sock.Socket());
    }
    ~udp_client()
    {
        _sock.Close();
    }
    void SendTo(std::string buf)
    {
        _sock.SendTo(buf,_ip,_port);
    }
    void RcvForm(std::string * buf)
    {
        _sock.RecvFrom(buf);
    }
    private:
    udp_socket _sock;
    std::string _ip;
    uint16_t _port;
};