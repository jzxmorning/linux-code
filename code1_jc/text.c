#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
void Myexit()
{
    printf("hello exit");
    exit(1);
}
void My_exit()
{
    printf("hello _exit");
    _exit(1);
}
int main()
{
   //Myexit();
   My_exit();
    return 0;
}