#pragma once
#include <iostream>
enum
{
    OK=0,
    SOCKET_ERROR,
    BIND_ERROR,
    LISTEN_ERROR,
    FORK_ERROR,
    CONNECT_ERROR,
};

class nocopy
{
public:
    nocopy()
    {
    }
    nocopy(const nocopy &) = delete;
    const nocopy &operator=(const nocopy &) = delete;
    ~nocopy() {}
};
#define COVE(addr_ptr) ((struct sockaddr*)addr_ptr)