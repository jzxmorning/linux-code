#include<iostream>
using namespace std;
#define  ONE 0x0001
#define  TWO 0x0010
#define  THREE 0x0100
#define  FOUR 0x1000
void fun(int flag)
{
    if((flag&ONE))
    {
        printf("flag has ONE\n");
    }
    if((flag&TWO))
    {
        printf("flag has TWO\n");
    }
    if((flag&THREE))
    {
        printf("flag has THREE\n");
    }
    if((flag&FOUR))
    {
        printf("flag has FOUR\n");
    }
}
int main()
{
    fun(ONE);
    cout<<endl;
    fun(ONE|FOUR);
    cout<<endl;
    fun(ONE|THREE|FOUR);
    cout<<endl;
    return 0;
}