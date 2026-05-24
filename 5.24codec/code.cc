#include <iostream>
#include<stdlib.h>
using namespace std;

int main()
{
    char *P=getenv("MYENV");
    if(P!=NULL)
    {
        cout<<"MYENV="<<P<<endl;
    }

    return 0;
}