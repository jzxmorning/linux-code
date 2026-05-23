#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include<vector>
typedef void (*hander_t)();
std::vector<hander_t> hander;
void fun_1()
{
    printf("这是一个任务1\n");
}
void fun_2()
{
    printf("这是任务2\n");
}
void otherwork()
{
    hander.push_back(fun_1);
    hander.push_back(fun_2);
   for(auto &t : hander)
   {
    t();
   }
}
int main()
{
    int id = fork();
    if (id == -1)
    {
        perror("创建进程失败\n");
    }
    else if (id == 0)
    {
        // child
        int cnt = 5;
        printf("我是一个子进程,我要运行5秒\n");
        while (cnt)
        {
            sleep(1);
            cnt--;
        }
        exit(1);
    }
    else
    {
        // father
        int status;
        int x = 0;
        do
        {
            x = waitpid(id, &status, 1);
            if(x == 0 )
            {
                printf("子进程正在运行...\n");
            }
            sleep(1);
            otherwork();
        } while (x == 0);
        if(WIFEXITED(status)&&x==id)
        {
            printf("进程正常退出,进程的退出码是:%d\n",WEXITSTATUS(status));
        }else
        {
            printf("进程等待失败\n");
        }
    }

    return 0;
}