#pragma once
#include <iostream>
#include <Account.pb.h>
#include <AccountData.h>
#include <Logging.h>

class ProtoReadWrite{
    public:
        pb::Accounts db;
        std::string protodata;
        Logger logger;

        ProtoReadWrite(std::string &protodata, pb::Accounts &db):
        protodata(protodata), db(db) {};

        bool check_account_exists(std::string&, std::string&);
        bool check_account_exists(int &accountnum);

        
        void read_proto();
        void write_proto();
        void write_proto(pb::Account&, double&);

        
        void show_all_accounts();
        void show_account_num(int);
        void show_account_num();
        void show_account_name();

        void new_account();

        void write_data(pb::Account&, AccountData&);
        void write_data_transaction(double&, int&);

        AccountData get_account(std::string&, std::string&);
        
        void close_account();
    private:
        pb::Account *laccount;
        
};