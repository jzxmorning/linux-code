#include <cstdio>
#include<iostream>
#include <stdlib.h>
int main()
{
    // FILE *f = fopen("text.txt", "w");
    // if (f == nullptr)
    // {
    //     printf("open error\n");
    //     exit(1);
    // }
    // fprintf(f, "hello\n");
    // fclose(f);
    // FILE *fp = fopen("text.txt", "a");
    // if (fp == nullptr)
    // {
    //     printf("open error\n");
    //     exit(1);
    // }
    // fprintf(fp, "world\n");
    // fclose(fp);
    // FILE *fil=fopen("text.txt","r");
    // char buf[128];
    // while(1)
    // {
    //     ssize_t n= fread(buf,1,sizeof(buf),fil);
    //     if(n>0)
    //     {
    //         buf[n]=0;
    //         // std::cout<<n;
    //         printf("%s\n",buf);
    //     }
    //     if(feof(fil))
    //     {
    //         break;
    //     }
    // }
    // fclose(fil);
    fprintf(stdout,"hello\n");
    return 0;
}