#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Cli.h"
#include "AccountData.h"
#include <ProtoReadWrite.h>
#include <Transaction.h>

// TODO:
// input validation of incorrect types
// make search by account name case insensitive
// input validation in newAccount() function
// password encryption / not plain text

AccountData *currentUser;
bankcli::Account currentAccount;

Cli::Cli(){

}

void Cli::run(){
    currentUser = new AccountData();
    
    if(login()){ // if login returns true, run program
        bool runProgram = true;

        while(runProgram){
            runProgram = showMenu();
        }
    }
}

bool Cli::login(){
    for(int i = 0; i < 3; i++){
        std::string username, password;

        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if(checkIfAccountExists(username, password) == true){
            std::cout << std::endl << "Login successful!" << std::endl;
            return true;
        }
        else{
            std::cout << "Incorrect username or password. Attempt " << i+1 << " of 3" << std::endl;
        }
    }
    std::cout << "Too many attempts" << std::endl;
    return false;
}

// for login only
bool Cli::checkIfAccountExists(std::string enteredUsername, std::string enteredPassword){
    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    bankcli::Customers customer = proto->read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		currentAccount = customer.account(i);

		if(enteredUsername == currentAccount.username() && enteredPassword == currentAccount.password()){

            currentUser->setAccountNum(currentAccount.accountnum());
            currentUser->setUsername(currentAccount.username());
            currentUser->setPassword(currentAccount.password());
            currentUser->setFName(currentAccount.fname());
            currentUser->setLName(currentAccount.lname());
            currentUser->setSSN(currentAccount.ssn());
            currentUser->setBalance(currentAccount.balance());
            currentUser->setDateOpened(std::stoi(currentAccount.dateopened()));
            currentUser->setAccountType(currentAccount.accounttype());
            currentUser->setAdmin(currentAccount.admin());

            delete proto;
            return true;
        }
	}
    delete proto;
    return false;
}

bool Cli::checkIfAccountExists(int accountNum){
    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    bankcli::Customers customer = proto->read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

		if(accountNum == account.accountnum()){
            delete proto;
            return true;
        }
	}
    delete proto;
    return false;
}

bool Cli::showMenu(){
    // options if user is an admin
    if(currentUser->getAdmin() == 1){
        int option;

        std::cout << std::endl << "Welcome " << currentUser->getFName() << " to the bank CLI!" << std::endl;
        std::cout << "Currently logged in with Admin privileges" << std::endl << std::endl;

        std::cout << "1. Display all acounts" << std::endl;    
        std::cout << "2. Search account by account number" << std::endl;
        std::cout << "3. Search account by name" << std::endl;
        std::cout << "4. Create new account" << std::endl;
        std::cout << "5. Close an account" << std::endl;
        std::cout << "6. Make a transaction" << std::endl;
        std::cout << "0. Close program" << std::endl << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;

        while (!std::cin.good()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid user input, please try again" << std::endl;

            return showMenu();
        }

        ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);

        switch(option){
            case 0:     // ends program if select 0
                std::cout << "Goodbye" << std::endl;
                return false;
            case 1:
                std::cout << "Show all accounts selected " << std::endl << std::endl;
                proto->show_all_accounts();
                break;
            case 2:
                std::cout << "Search account by account number selected " << std::endl << std::endl;
                searchAccountNum();
                break;
            case 3:
                std::cout << "Search account by name selected " << std::endl << std::endl;
                searchAccountName();
                break;
            case 4:
                std::cout << "Create new account selected " << std::endl << std::endl;
                newAccount();
                break;
            case 5:
                std::cout << "Close account selected " << std::endl << std::endl;
                closeAccount();
                break;
            case 6:{
                std::cout << "Make a transaction selected" << std::endl << std::endl;
                Transaction transaction(*currentUser, currentAccount);
                break;
            }
                
            default:
                std::cout << "No option selected, please try again" << std::endl;

                return showMenu();
        }
    }

    // options if user is !admin
    else if(currentUser->getAdmin() != 1){
        int option;

        std::cout << std::endl << "Welcome " << currentUser->getFName() << " to the bank CLI!" << std::endl;
        std::cout << "Currently logged in with standard User privileges" << std::endl << std::endl;

        std::cout << "0. Close program" << std::endl << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;

        while (!std::cin.good()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid user input, please try again" << std::endl;

            return showMenu();
        }

        switch(option){
            case 0:
                std::cout << "Goodbye" << std::endl;
                return false;
            default:
                std::cout << "No option selected, please try again" << std::endl;

                return showMenu();
        }

        // PLACEHOLDER
        // add user options here
    }
    return true;
}

void Cli::searchAccountNum(){
    int accountNum;
    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);

    std::cout << "Enter account number to search for: ";
    std::cin >> accountNum;

    while (!std::cin.good()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(checkIfAccountExists(accountNum) == true){
        proto->show_account(accountNum);     // displays the account if matching account number found
    }
    else{
        std::cout << "No matching account found with account number " << accountNum << std::endl << std::endl;
        searchAccountNum();             // retries method if not matching account number found
    }
    
}

void Cli::searchAccountName(){
    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    std::string tmpFName, tmpLName;

    std::cout << "Enter first name for search:";
    std::cin >> tmpFName;
    std::cout << "Enter last name for search:";
    std::cin >> tmpLName;
    std::cout << std::endl;

    proto->show_account(tmpFName, tmpLName);
    //displayAccount(tmpFName, tmpLName);
}

void Cli::newAccount(){    
    std::string username, password;
    std::string fname, lname;
    int ssn;
    double balance = 0.00;
    std::string tmpDate;
    int dateOpened;
    char accountType; // checking 'c' or savings 's'
    int admin;
    int accountNum;

    std::cout << "Enter new account number: ";
    std::cin >> accountNum;

    // checks if accountNum alread exists
    if(checkIfAccountExists(accountNum) == true){
        std::cout << "Account already exists" << std::endl;
    }
    else{
        std::cout << "Enter new username: ";
        std::cin >> username;
        std::cout << "Enter new password: ";
        std::cin >> password;

        // checks minimim username and password length
        if(username.length() < 5){
            std::cout << "Username is too short (minimum 5 characters)" << std::endl;
            
            newAccount();
            return;
        }
        else if(password.length() < 5){
            std::cout << "password is too short (minimum 5 characters)" << std::endl;
            newAccount();
            return;
        }
        else if(username == password){
            std::cout << "Username and password cannot be the same" << std::endl;
            newAccount();
            return;
        }

        std::cout << "Enter new first name: ";
        std::cin >> fname;
        std::cout << "Enter new last name: ";
        std::cin >> lname;
        std::cout << "Enter new SSN (9 digits): ";
        std::cin >> ssn;
        std::cout << "Enter new date opened yyyy-mm-dd: ";
        std::cin >> tmpDate;
        std::cout << "Enter new account type (S or C): ";
        std::cin >> accountType;
        std::cout << "Enter new admin elevation (0 for user, 1 for admin: ";
        std::cin >> admin;

        // remove '-' from date string
        tmpDate.erase(std::remove(tmpDate.begin(), tmpDate.end(), '-'), tmpDate.end());
        dateOpened = std::stoi(tmpDate);

        AccountData *accountdata = new AccountData();

        accountdata->setAccountNum(accountNum);        
        accountdata->setUsername(username);
        accountdata->setPassword(password);
        accountdata->setFName(fname);
        accountdata->setLName(lname);
        accountdata->setSSN(ssn);
        accountdata->setBalance(balance);
        accountdata->setDateOpened(dateOpened);
        accountdata->setAccountType(accountType);
        accountdata->setAdmin(admin);

        ProtoReadWrite *prw = new ProtoReadWrite(*accountdata);
        prw->write_proto();

        if(checkIfAccountExists(accountNum) == true){
            std::cout << "Account successfully created!" << std::endl;
        }
    }
}

void Cli::closeAccount(){

    int localAccountNum1, localAccountNum2;

    std::cout << "Enter account number of associated account: ";
    std::cin >> localAccountNum1;
    std::cout << "Repeated associated account number for security ";
    std::cin >> localAccountNum2;

    if(localAccountNum1 == localAccountNum2 && checkIfAccountExists(localAccountNum1) == true){

        AccountData *localUser = new AccountData();
        ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
        bankcli::Customers customer = proto->read_proto();

        for(int i = 0; i < customer.account_size(); i++){
            const bankcli::Account account = customer.account(i);

            if(localAccountNum1 == account.accountnum()){
                // code goes here
            }
        }
    }
}
