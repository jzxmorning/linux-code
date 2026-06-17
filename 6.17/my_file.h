#pragma once
#define SIZE 1024
#define FLUSH_NONE 0
#define FLUSH_LINE 1
#define FLUSH_FULL 2
struct IO_FILE
{
  int fdnm;//fd
  int size=0;//size;
  char outbuffer[SIZE];
  int flag;//刷新的方式
  int cap;
};

typedef struct IO_FILE myfile;
myfile* myopen(const char* filename,const char *mode);
int mywrite(const char* ptr,int num, myfile* fp);
void myfllush(myfile*fp);
void myclose(myfile* fp);