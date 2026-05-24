#include <iostream>
#include <string.h>
using namespace std;
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        // printf("%d\n",argc);
        printf("用法错误,这个程序需要两个选项\n");
        return 1;
    }
    if (strcmp(argv[1], "-a") == 0)
    {
        printf("这是a功能\n");
        printf("hhhh\n");
    }
    else if (strcmp(argv[1], "-b") == 0)
    {
        printf("这是b功能\n");
        printf("xxxxx\n");
    }
    if (strcmp(argv[2], "-a") == 0)
    {
        printf("这是a功能\n");
        printf("hhhh\n");
    }
    else if (strcmp(argv[2], "-b") == 0)
    {
        printf("这是b功能\n");
        printf("xxxxx\n");
    }
    return 0;
}