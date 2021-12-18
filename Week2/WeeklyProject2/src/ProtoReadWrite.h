#include <iostream>
#include <users.pb.h>
#include <AccountData.h>

class ProtoReadWrite{
    AccountData accountdata;

    public:
        ProtoReadWrite(AccountData &a);

        bankcli::Customers read_proto();
        //void read_proto(std::string &username, std::string &password);

        void write_proto();

    private:
        void write_data(bankcli::Account *account);
};