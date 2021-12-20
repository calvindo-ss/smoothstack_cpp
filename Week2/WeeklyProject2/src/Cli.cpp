#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Cli.h"
#include "AccountData.h"
#include <Transaction.h>
#include <Logging.h>

// TODO:
// input validation of incorrect types

AccountData *currentUser;

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
    Logger logger;
    for(int i = 0; i < 3; i++){
        std::string username, password;

        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        if(prw.check_account_exists(username, password) == true){
            *currentUser = prw.get_account(username, password);

            logger.log("Login successful");
            std::cout << std::endl << "Login successful!" << std::endl;
            return true;
        }
        else{
            std::cout << "Incorrect username or password. Attempt " << i+1 << " of 3" << std::endl;
        }
    }
    logger.log("Too many login attempts");
    std::cout << "Too many attempts" << std::endl;
    return false;
}

bool Cli::showMenu(){
    // options if user is an admin
    
    int option;

    std::cout << std::endl << "Welcome to the bank CLI!" << std::endl;
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

    switch(option){
        case 0:     // ends program if select 0
            std::cout << "Goodbye" << std::endl;
            return false;
        case 1:
            std::cout << "Show all accounts selected " << std::endl << std::endl;
            //proto->show_all_accounts();
            prw.show_all_accounts();
            break;
        case 2:
            std::cout << "Search account by account number selected " << std::endl << std::endl;
            //searchAccountNum();
            prw.show_account_num();
            break;
        case 3:
            std::cout << "Search account by name selected " << std::endl << std::endl;
            prw.show_account_name();
            break;
        case 4:
            std::cout << "Create new account selected " << std::endl << std::endl;
            prw.new_account();
            break;
        case 5:
            std::cout << "Close account selected " << std::endl << std::endl;
            prw.close_account();
            break;
        case 6:{
            std::cout << "Make a transaction selected" << std::endl << std::endl;
            Transaction transaction(prw, currentUser->getBalance(), *currentUser);
            transaction.run();
            break;
        }
            
        default:
            std::cout << "No option selected, please try again" << std::endl;

            return showMenu();
    }
    return true;
}