#include "my_file.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main()
{
myfile *fp = myopen("./log.txt", "a");
 if(fp == NULL)
 {
 return 1;
 }
 int cnt = 10;
 while(cnt)
 {
 printf("write %d\n", cnt);
 char buffer[64];
 snprintf(buffer, sizeof(buffer),"hello message, number is : %d", cnt);
 cnt--;
 mywrite(buffer, strlen(buffer), fp);
 myfllush(fp);
 sleep(1);
 }
 myclose(fp);
}
