#pragma once
#include <iostream>
#include <users.pb.h>
#include <AccountData.h>

class ProtoReadWrite{
    AccountData accountdata;

    public:
        ProtoReadWrite(AccountData &a);

        bankcli::Customers read_proto();

        void write_proto();
        void write_proto(bankcli::Account&, double&);

        void show_all_accounts();
        void show_account(int);
        void show_account(std::string, std::string);
        void write_data(bankcli::Account *account);

    private:
        
};