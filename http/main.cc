#include"http.hpp"
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        std::cout<<"use error"<<std::endl;
        std::cerr << "Usage: " << argv[0] << " local-port" << std::endl;
        exit(1);
    }
    Enable_Console_Log_Strategy();
    Http Server(std::atoi(argv[1]));
    Server.Start();
    return 0;
}