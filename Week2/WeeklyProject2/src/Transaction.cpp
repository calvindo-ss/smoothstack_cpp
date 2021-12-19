#include <iostream>

#include <Transaction.h>
#include <ProtoReadWrite.h>

Transaction::Transaction(AccountData &a, bankcli::Account &b){
    data = &a;
    account = b;
    balance = data->getBalance();

    int choice;

    std::cout << "1. Show balance" << std::endl;    
    std::cout << "2. Deposit into account" << std::endl;
    std::cout << "3. Withdraw from account" << std::endl;
    std::cout << "0. Cancel transaction" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> choice;

    switch(choice){
        case 1:
            std::cout << balance << std::endl;
            break;
        case 2:
            debit();
            break;
        case 3:
            credit();
            break;
        case 0:
            return;
    }
}

void Transaction::debit(){
    double amnt;

    std::cout << "Enter amount to deposit into accout: ";
    std::cin >> amnt;

    balance += amnt;

    update_balance();

}

void Transaction::credit(){
    double amnt;

    std::cout << "Enter amount to withdraw from accout: ";
    std::cin >> amnt;

    if(check_balance(amnt)){
        balance -= amnt;
        std::cout << "Withdrawl successful" << std::endl;
    }
    else{
        std::cout << "Not enough funds to withdraw" << std::endl;
    }
    update_balance();
}

bool Transaction::check_balance(double &a){

    if(a < balance){
        return true;
    }
    return false;
}

void Transaction::update_balance(){

    ProtoReadWrite *proto = new ProtoReadWrite(*data);
    data->setBalance(balance);

    proto->write_proto(account, balance);
}
