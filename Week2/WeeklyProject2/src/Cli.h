#include <iostream>
#include <ProtoReadWrite.h>

class Cli{
    ProtoReadWrite &prw;
    public:
        Cli(ProtoReadWrite protoreadwrite):
        prw(protoreadwrite){}
       
        void run();
        
    private:
        bool login();
        bool showMenu();
        void closeAccount();
};