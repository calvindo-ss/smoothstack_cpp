#include "User.h"
#include <vector>

User::User(){

}

// setters
void User::setUserData(std::vector<std::string> &userData){
    this->setUsername(userData[0]);
    this->setPassword(userData[1]);
    this->setFName(userData[2]);
    this->setLName(userData[3]);
    this->setSSN(std::stoi(userData[4]));
    this->setBalance(std::stod(userData[5]));
    this->setDateOpened(std::stoi(userData[6]));
    this->setAccountType(userData[7][0]);
    this->setAdmin(std::stoi(userData[8]));
    this->setAccountNum(std::stoi(userData[9]));
}

void User::setUsername(std::string username){
    this->username = username;
}

void User::setPassword(std::string password){
    this->password = password;
}

void User::setFName(std::string fname){
    this->fname = fname;
}

void User::setLName(std::string lname){
    this->lname = lname;
}

void User::setSSN(int ssn){
    this->ssn = ssn;
}

void User::setBalance(double balance){
    this->balance = balance;
}

void User::setDateOpened(int dateOpened){
    this->dateOpened = dateOpened;
}

void User::setAccountType(char accountType){
    this->accountType = accountType;
}

void User::setAdmin(int admin){
    this->admin = admin;
}

void User::setAccountNum(int accountNum){
    this->accountNum = accountNum;
}

// getters
std::string User::getUsername(){
    return this->username;
}

std::string User::getPassword(){
    return this->password;
}

std::string User::getFName(){
    return this->fname;
}

std::string User::getLName(){
    return this->lname;
}

int User::getSSN(){
    return this->ssn;
}

double User::getBalance(){
    return this->balance;
}

std::string User::getDateOpened(){
    std::string formattedDate = std::to_string(this->dateOpened);
    formattedDate.insert(4, 1, '-');
    formattedDate.insert(7, 1, '-');

    return formattedDate;
}

char User::getAccountType(){
    return this->accountType;
}

int User::getAdmin(){
    return this->admin;
}

int User::getAccountNum(){
    return this->accountNum;
}