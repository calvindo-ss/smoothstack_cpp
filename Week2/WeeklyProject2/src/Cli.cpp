#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Cli.h"
#include "AccountData.h"
#include <ProtoReadWrite.h>

// TODO:
// input validation of incorrect types
// make search by account name case insensitive
// input validation in newAccount() function
// password encryption / not plain text

// Helper function
unsigned levenshtein_distance(const std::string s1, std::string s2) {

	const std::size_t len1 = s1.size(), len2 = s2.size();
	std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

	d[0][0] = 0;
	for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
	for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

	for(unsigned int i = 1; i <= len1; ++i)
		for(unsigned int j = 1; j <= len2; ++j) {
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
        }

	return d[len1][len2];
}

AccountData *currentUser;

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
    std::string username, password;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if(checkIfAccountExists(username, password)){
        std::cout << std::endl << "Login successful!" << std::endl;
        return true;
    }
    else{
        std::cout << "Login failed" << std::endl;
        login();
        return true;
    }
    return false;
}

// for login only
bool Cli::checkIfAccountExists(std::string enteredUsername, std::string enteredPassword){
    
    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    bankcli::Customers customer = proto->read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

		if(enteredUsername == account.username() && enteredPassword == account.password()){

            currentUser->setAccountNum(account.accountnum());
            currentUser->setUsername(account.username());
            currentUser->setPassword(account.password());
            currentUser->setFName(account.fname());
            currentUser->setLName(account.lname());
            currentUser->setSSN(account.ssn());
            currentUser->setBalance(account.balance());
            currentUser->setDateOpened(std::stoi(account.dateopened()));
            currentUser->setAccountType(account.accounttype());
            currentUser->setAdmin(account.admin());

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
            case 0:     // ends program if select 0
                std::cout << "Goodbye" << std::endl;
                return false;
            case 1:
                std::cout << "Show all accounts selected " << std::endl << std::endl;
                showAllAccounts();
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

void Cli::showAllAccounts(){

    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    bankcli::Customers customer = proto->read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

        std::cout << "################################" << std::endl;
		std::cout << "Account number: " << account.accountnum() << std::endl;
		std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
		std::cout << "Date opened: " << account.dateopened() << std::endl;
	}
}

void Cli::searchAccountNum(){
    int accountNum;
    std::cout << "Enter account number to search for: ";
    std::cin >> accountNum;

    while (!std::cin.good()){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if(checkIfAccountExists(accountNum) == true){
        displayAccount(accountNum);     // displays the account if matching account number found
    }
    else{
        std::cout << "No matching account found with account number " << accountNum << std::endl << std::endl;
        searchAccountNum();             // retries method if not matching account number found
    }
    
}

void Cli::displayAccount(int accountNum){

    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    bankcli::Customers customer = proto->read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

		if(accountNum == account.accountnum()){
            std::cout << std::endl << "################################" << std::endl;
            std::cout << "Customer name: " << account.fname() << " " << account.lname() << std::endl;
            std::cout << "SSN: " << account.ssn() << std::endl;
            std::cout << "Date opened: " << account.dateopened() << std::endl;
            std::cout << "################################" << std::endl;
        }
	}
}

void Cli::searchAccountName(){
    std::string tmpFName, tmpLName;

    std::cout << "Enter first name for search:";
    std::cin >> tmpFName;
    std::cout << "Enter last name for search:";
    std::cin >> tmpLName;
    std::cout << std::endl;

    displayAccount(tmpFName, tmpLName);
}

void Cli::displayAccount(std::string localFName, std::string localLName){
    std::vector<int> searchResults_accountnums;
    std::vector<std::string> searchResults;

    ProtoReadWrite *proto = new ProtoReadWrite(*currentUser);
    bankcli::Customers customer = proto->read_proto();

    for(int i = 0; i < customer.account_size(); i++){
		const bankcli::Account account = customer.account(i);

		if(levenshtein_distance(localFName, account.fname()) < 4 && levenshtein_distance(localLName, account.lname()) < 4){
            if(localFName.compare(account.fname()) == 0 && localLName.compare(account.lname()) == 0){

                searchResults.insert(searchResults.begin(), account.fname()+" "+account.lname());
                searchResults_accountnums.insert(searchResults_accountnums.begin(), account.accountnum());
            }
            else{
                searchResults.push_back(account.fname()+" "+account.lname());
                searchResults_accountnums.push_back(account.accountnum());

            }
        }
	}

    if(searchResults.size() != 0){
        for(int i=0; i<searchResults.size(); i++){
        std::cout << i+1 << ". " << searchResults[i] << std::endl;
        }

        std::cout << "0. Cancel search" << std::endl << std::endl;
        int option;
        std::cout << "Select which user to view: ";
        std::cin >> option;

        // selects customer based on user input
        for(int j = 0; j < searchResults.size(); j++){
            if(option == 0){
                return;
            }
            if(j+1 == option){ // if option==1
                displayAccount(searchResults_accountnums[j]);
                return;
            }
        }
    }
    
    std::cout << "No matching account found for " << localFName << " " << localLName << std::endl;
    searchAccountName();
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
        ProtoReadWrite *proto = new ProtoReadWrite(*localUser);
        bankcli::Customers customer = proto->read_proto();

        for(int i = 0; i < customer.account_size(); i++){
            const bankcli::Account account = customer.account(i);

            if(localAccountNum1 == account.accountnum()){
                // code goes here
            }
        }
    }
}
