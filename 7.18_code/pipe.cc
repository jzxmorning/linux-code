#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
const int SIZE = 1024;
int main()
{
    int fd[2] = {0};
    int k = pipe(fd);
    if (k < 0)
    {
        perror("pipe error");
        exit(1);
    }
    // fd[0]->read fd[1]->write
    int n = fork();
    if (n < 0)
    {
        perror("fork error");
        exit(1);
    }
    else if (n == 0)
    {
        // child 读端
        close(fd[1]);
        char buf[SIZE];
       ssize_t size = read(fd[0], buf, sizeof(buf));
        if (size > 0)
        {
            buf[size] = 0;
            std::cout << buf << std::endl;
        }

        close(fd[0]);
        exit(0);
    }
    // father 写端
    close(fd[0]);
    write(fd[1], "hello", 5);
    close(fd[1]);
    return 0;
}