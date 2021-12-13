#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#include "Cli.h"
#include "User.h"

// TODO:
// input sanitization of incorrect types
// make search by account name case insensitive
// input sanitization in newAccount() function
// password encryption / not plain text

User *currentUser;

Cli::Cli(){
    
}

void Cli::run(){
    currentUser = new User();

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

bool Cli::checkIfAccountExists(std::string enteredUsername, std::string enteredPassword){
    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("users.txt");                     // username, password, fname, lname, ssn, balance, date, account type, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;      // username, password, fname, lname, ssn, balance, date, account type, admin, accountnum

        while(getline(ss, tmp, delimiter)){     // reads line and separates by delimiter; 
            userData.push_back(tmp);            // pushes separate strings into userData
        }

        if(userData[0].compare(enteredUsername) == 0){          // compares if entered username matches username on file
            if(userData[1].compare(enteredPassword) == 0){      // compares if entered password matches password on file
                currentUser->setUserData(userData);                    // sets all data for user obj
                
                file.close();
                return true;
            }
        }   
    }

    file.close();
    return false;
}

bool Cli::checkIfAccountExists(int accountNum){
    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("users.txt");                     // username, password, fname, lname, ssn, balance, date, account type, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;

        User *localUser = new User();

        while(getline(ss, tmp, delimiter)){     // reads a single line and pushes to userData
            userData.push_back(tmp); 
        }
            
        // copies userData to User obj
        localUser->setUserData(userData);       // sets userData to localUser obj

        if(localUser->getAccountNum() == accountNum){       // if localUser->getAccountNum()==accountNum
        file.close();                                       // then the account exists, return true
            return true;
        }
        
    }
              
    file.close();
    return false;   // if no matching accountNum found, user does not exits, return false
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
    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("users.txt");                     // username, password, fname, lname, ssn, balance, date, accounttype, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;
        User *localUser = new User();

        while(getline(ss, tmp, delimiter)){     // reads a single line and pushes to userData
            userData.push_back(tmp); 
        }

        // copies userData to User obj
        localUser->setUserData(userData);

        // display account data
        std::cout << "##################################" << std::endl << std::endl;
        std::cout << "Account_Number: " << localUser->getAccountNum() << std::endl;
        std::cout << "Name: " << localUser->getFName() << " " << localUser->getLName() << std::endl;
        std::cout << "Date_Opened: " << localUser->getDateOpened() << std::endl << std::endl;

    }

    file.close();
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
    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("users.txt");                     // username, password, fname, lname, ssn, balance, date, accounttype, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;
        User *localUser = new User();

        while(getline(ss, tmp, delimiter)){     // reads a single line and pushes to userData
            userData.push_back(tmp); 
        }

        // copies userData to User obj
        localUser->setUserData(userData);
        
        if(localUser->getAccountNum() == accountNum){
            std::string tmpSSN = std::to_string(localUser->getSSN()); // converts SSN int to SSN string
            tmpSSN = tmpSSN.substr(5,8); // removes all chars except for last 4

            std::cout << std::endl << "Customer Name: " << localUser->getFName() << " " << localUser->getLName() << std::endl;
            std::cout << "Last 4 SSN: " << tmpSSN << std::endl;
            std::cout << "Date Opened: " << localUser->getDateOpened() << std::endl;
        }
    }
    file.close();
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
    std::vector<int> userAccounts;
    std::vector<std::string> userAccountNames;

    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("users.txt");                     // username, password, fname, lname, ssn, balance, date, accounttype, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;
        User *localUser = new User();

        while(getline(ss, tmp, delimiter)){     // reads a single line and pushes to userData
            userData.push_back(tmp); 
        }

        // copies userData to User obj
        localUser->setUserData(userData);

        // if both fname&&lname==0, push to front of vector
        if(localUser->getFName().compare(localFName) == 0 && localUser->getLName().compare(localLName) == 0){ 
            userAccounts.insert(userAccounts.begin(), localUser->getAccountNum());

            std::string fullName = localUser->getFName() + " " + localUser->getLName(); // concatenates fname and lname

            userAccountNames.insert(userAccountNames.begin(), fullName);
        }
        // if fname||lname==0 push back
        else if (localUser->getFName().compare(localFName) == 0 || localUser->getLName().compare(localLName) == 0){ 
            userAccounts.push_back(localUser->getAccountNum());

            std::string fullName = localUser->getFName() + " " + localUser->getLName(); // concatenates fname and lname

            userAccountNames.push_back(fullName);
        }
    }

    if(userAccountNames.size() != 0){
        for(int i=0; i<userAccountNames.size(); i++){
        std::cout << i+1 << ". " << userAccountNames[i] << std::endl;
        }

        std::cout << "0. Cancel search" << std::endl << std::endl;
        int option;
        std::cout << "Select which user to view: ";
        std::cin >> option;

        // selects customer based on user input
        for(int j = 0; j < userAccountNames.size(); j++){
            if(option == 0){
                break;
            }
            if(j+1 == option){ // if option==1
                displayAccount(userAccounts[j]);
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
        newAccount();
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

        // open and write to file
        std::fstream file;

        // username, password, fname, lname, ssn, balance, date, account type, admin, accountnum
        file.open("users.txt", std::ios::app); 
        file << username << ',' << password << ',' << fname << ',' << lname << ',' << ssn << ',' << balance << ',' << dateOpened << ',' 
            << accountType << ',' << admin << ',' << accountNum << std::endl;
        file.close();

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

    if(localAccountNum1 == localAccountNum2){
        if(checkIfAccountExists(localAccountNum1) == true){
            std::string line;

            std::fstream file;
            std::ofstream temp;
    
            file.open("users.txt");
            temp.open("temp.tmp");

            std::string targetLine = std::to_string(localAccountNum1);

            while(getline(file, line)){
                if(line.find(targetLine) == std::string::npos){
                    temp << line << std::endl;
                }
            }

            temp.close();
            file.close();
            remove("users.txt");
            rename("temp.tmp", "users.txt");

            std::cout << "Account successfully deleted!" << std::endl;
        }
    }
}
