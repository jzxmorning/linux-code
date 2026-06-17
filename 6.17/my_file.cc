#include "my_file.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
myfile *myopen(const char *filename, const char *mode)
{
    int fd = -1;
    if (strcmp(mode, "r") == 0)
    {
         fd = open(filename, O_RDONLY);
    }
    else if (strcmp(mode, "w") == 0)
    {
         fd = open(filename, O_WRONLY | O_CREAT, 0666);
    }
    else if (strcmp(mode, "a") == 0)
    {
         fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
    }
    if (fd < 0)
    {
        return nullptr;
    }
    myfile *fp = (myfile *)malloc(sizeof(myfile));
    if (fp == nullptr)
    {
        return nullptr;
    }
    fp->cap = SIZE;
    fp->flag = FLUSH_LINE;
    fp->fdnm = fd;
    return fp;
}
void myfllush(myfile *fp)
{
    if(fp->size>0)
    {
        write(fp->fdnm,fp->outbuffer,fp->size);
        fsync(fp->fdnm);
        fp->size=0;
    }
}
int mywrite(const char *ptr, int num, myfile *fp)
{
    memcpy(fp->outbuffer + fp->size, ptr, num);
    fp->size += num;
    if (fp->size > 0 && fp->flag == FLUSH_LINE && fp->outbuffer[fp->size - 1] == '\n')
    {
        myfllush(fp);
    }
    return num;
}
void myclose(myfile *fp)
{
    if(fp->size>0)
    {
        myfllush(fp);
    }
    close(fp->fdnm);
}