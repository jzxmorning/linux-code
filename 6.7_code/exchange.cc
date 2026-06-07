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
    pid_t id  = fork();
    if(id == -1)
    {
        perror("fork error\n");
        exit(1);
    }else if(id == 0)
    {
        char* v[]={"ls","-l",nullptr};
        char* myenv[]={"PATH=/bin:/usr/bin", "TERM=console", NULL};
        //child process
        printf("child process my id is %d\n",getpid());
        printf("我要进行替换进程了,我将会把子进程替换为一个自己代码进程\n");
        // execl("/home/jiao/study/6.7/mycode","mycode",nullptr);
        // execvp("ls",v);
        execve("/bin/ls",v,myenv);
        printf("这句话会被执行吗???\n");
        perror("execlp error\n");
        exit(1);
    }else
    {
        //parent process
        printf("parent process my id is %d\n",getpid());
        printf("我要等待子进程\n");
        int sta;
        int n=waitpid(id,&sta,0);
        if(n==id&&(sta&0x7f)==0)
        {
            printf("子进程正常退出,退出码是:%d\n",(sta>>8)&0xff);

        }else
        {
            printf("子进程异常退出,退出的信号是:%d\n",sta&0x7f);
        }
    }

    return 0;
}