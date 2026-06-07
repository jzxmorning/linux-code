#include<iostream>
#include<stdlib.h>
#include<unistd.h> //fork
#include<sys/types.h> //pid_t
#include<sys/wait.h> //wait
#include<errno.h> //perror
#include<cstdio> //printf
#include<cstdlib> //exit
#include<cstring> //strerror
using namespace std;
int main()
{
   printf("我是一个C++的程序,我的pid是%d\n",getpid());
    return 0;
}