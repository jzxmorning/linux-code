#include "Thread.hpp"
#include<stdio.h>
#include <unistd.h>
using namespace ThreadMoudle;
void *fun1()
{
    int cnt = 3;
    while (cnt--)
    {
        printf("我是一个下载的工作.........\n");
        sleep(1);
    }
    return nullptr;
}
void *fun2()
{
    printf("我是一个日志的工作.........\n");
    return nullptr;
}
void *fun3()
{
    printf("我是一个上传的工作.........\n");
    return nullptr;
}
int main()
{
    Thread t1(fun1);
    t1.Start();
    Thread t2(fun2);
    t2.Start();
    t1.Join();
    t2.Join();

    return 0;
}