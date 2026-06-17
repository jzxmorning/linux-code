#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;
int main()
{
  close(1);
  int fd = open("text.txt", O_CREAT | O_WRONLY, 0666);
  if (fd == -1)
  {
    perror("open");
  }
  printf("我开始了\n");
  printf("hello world\n");
  fflush(stdout);
  close(fd);
  return 0;
}