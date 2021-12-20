#include <iostream>

#include <AccountData.h>
#include <ProtoReadWrite.h>

class Transaction{
    ProtoReadWrite &prw;
    double balance;
    AccountData &accountdata;

    public:
        Transaction(ProtoReadWrite protoreadwrite, double lbalance, AccountData &laccountdata):
        prw(protoreadwrite), balance(lbalance), accountdata(laccountdata){};

        void run();
        bool check_balance(double &amnt);

    private:
        void debit(); // deposit cash
        void credit(); // withdraw cash
        void update_balance();
};