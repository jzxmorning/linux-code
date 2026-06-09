#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#define Command_size 1024
const int Maxargv = 128;
char *argv[Maxargv];
int g_argv = 0;
char *GetHostName()
{
    char *hostname = getenv("HOSTNAME");
    return hostname;
}
char *GetUserName()
{
    char *UserName = getenv("USER");
    return UserName;
}
char *GetPWD()
{
    char *pwd = getenv("PWD");
    return pwd;
}
void Makecommand(char *command, int size)
{
    snprintf(command, size, "[%s@%s:%s]#", GetUserName(), GetHostName(), GetPWD());
}
void printfcommand()
{
    char command[Command_size];
    Makecommand(command, sizeof(command));
    printf("%s", command);
    fflush(stdout);
}
bool GetCommand(char *out, int size)
{
    char *c = fgets(out, size, stdin);
    if (c == nullptr)
    {
        return false;
    }
    out[strlen(out) - 1] = 0; // 去除\n
    if (strlen(out) == 0)     // 判断是否是一个\n指令
    {
        return false;
    }
    // 有效指令
    return true;
}
bool AnalyseCommand(char *command)
{
// 拆分指令到一个数组中
#define ELF " "
    g_argv = 0;
    argv[g_argv++] = strtok(command, ELF);
    while ((bool)(argv[g_argv++] = strtok(nullptr, ELF)))
    {
    }
    g_argv--;
    return true;
}
void excute()
{
    pid_t id = fork();
    if (id == -1)
    {
        perror("fork error\n");
        exit(1);
    }
    else if (id == 0)
    {
        // child
        execvp(argv[0], argv);
        printf("错误指令\n");
        exit(1);
    }
    int n = waitpid(id, nullptr, 0);
    (void)n;
    return;
}
// 判断是否为内建命令
bool isandexcutebuiltin()
{
    if (strcmp(argv[0], "cd") == 0)
    {
        if (g_argv == 1)
        {
            printf("cd: missing operand\n");
        }
        else if (g_argv > 2)
        {
            printf("cd: too many arguments\n");
        }
        else
        {
            if (chdir(argv[1]) == -1)
            {
                perror("cd");
            }
        }
        return true;
    }
    // 还有很多的内建命令
    //  ...
    return false;
}

int main()
{
    while (1)
    {
        // 打印命令行提示符
        printfcommand();
        char command[Command_size];
        if (!GetCommand(command, sizeof(command)))
        {
            continue;
        }
        // 分析指令
        AnalyseCommand(command);
        // 判断是否为内建命令
        if (isandexcutebuiltin())
        {
            continue;
        }
        // 执行命令
        excute();
    }

    return 0;
}