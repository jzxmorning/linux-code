#pragma once
#include <iostream>
enum
{
    SOCKET_ERROR,
    BIND_ERROR,

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