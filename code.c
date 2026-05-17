#include<stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
int main()
{
int id = fork();
if(id==0)
{
//child
sleep(1);
}else
{
//father
sleep(5);
}

return 0;
}
