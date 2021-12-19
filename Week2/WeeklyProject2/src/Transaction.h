#include <iostream>

#include <AccountData.h>
#include <ProtoReadWrite.h>

class Transaction{
    public:
        Transaction(AccountData &data, bankcli::Account &account);
        

    private:
        void debit(); // deposit cash
        void credit(); // withdraw cash

        bool check_balance(double &amnt);
        void update_balance();

        AccountData *data;
        bankcli::Account account;
        double balance;
};