#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main()
{
    int id = fork();
    int g_value = 10;
    if (id == -1)
    {
        perror("fork error\n");
    }
    else if (id == 0)
    {
        // child
        printf("i am child my pid is %d the g_value is %d my g_value is %p\n", getpid(), g_value, &g_value);
    }
    else
    {
        // father
        g_value = 100;
        printf("i am father my pid is %d the g_value is %d my g_value is %p\n", getpid(), g_value,&g_value);
    }
    return 0;
}