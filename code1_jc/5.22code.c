#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
    printf("我要开始创建进程了\n");
    int id=fork();
    if(id==-1)
    {
        perror("创建进程失败\n");
        exit(1);
    }else if(id==0)
    {
        //child
        int cout=3;
        while(cout)
        {
            cout--;
            sleep(1);
        }
        exit(1);
    }else
    {
        //father
         int x=wait(NULL);
         if(x==-1)
         {
            perror("等待失败\n");
         }else{
            printf("我等待的进程的pid是:%d",x);
         }
    }

    return 0;
}