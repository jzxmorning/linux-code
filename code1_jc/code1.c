#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h> 
#include<sys/wait.h>
int main()
{
    int id=fork();
    if(id==-1)
    {
        perror("创建进程失败\n");
        exit(1);
    }else if(id==0)
    {
        //child
        printf("子进程开始运行了,我的pid是%d,将会运行20秒\n",getpid());
        int cnt=20;
        while(cnt)
        {
            sleep(1);
            cnt--;
        }
        printf("子进程运行结束,设置的退出码是1\n");
        exit(1);
    }else
    {
        //father
        int status;
        int x=waitpid(id,&status,0);
        if((status&0x7f)==0&&x==id)
        {
            printf("正常退出,退出码是%d\n",(status>>8)&0xff);
        }else if(id==x)
        {
            printf("异常退出,退出码是%d\n",status&0x7f);
        }
    }

    return 0;
}