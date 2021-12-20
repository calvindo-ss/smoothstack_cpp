#include <iostream>

#include "Cli.h"
#include <Account.pb.h>
#include <ProtoReadWrite.h>

int main(){
    std::string protofile = "Account.data";
    // init protobuf
    auto accounts = pb::Accounts();

    ProtoReadWrite prw(protofile, accounts);

    //prw.new_account();

    Cli cli(prw);
    cli.run();

    return 0;
}