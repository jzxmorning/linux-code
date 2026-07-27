#include<iostream>
#include <pthread.h>
void* fun(void* argc)
{
    printf("我是一个线程,%s\n",(char*)argc);
    return nullptr;
}
int main()
{
    pthread_t t_id;
    pthread_create(&t_id,NULL,fun,(void*)"hhh");
    pthread_join(t_id, NULL);  // 等待线程执行完毕

    return 0;
}