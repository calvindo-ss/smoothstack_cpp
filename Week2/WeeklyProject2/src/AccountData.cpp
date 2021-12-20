#include "AccountData.h"
#include <Account.pb.h>

#include <vector>
#include <fstream>

AccountData::AccountData(){

}

// setters
void AccountData::setUsername(std::string username){
    this->username = username;
}

void AccountData::setPassword(std::string password){
    this->password = password;
}

void AccountData::setFName(std::string fname){
    this->fname = fname;
}

void AccountData::setLName(std::string lname){
    this->lname = lname;
}

void AccountData::setSSN(int ssn){
    this->ssn = ssn;
}

void AccountData::setBalance(double balance){
    this->balance = balance;
}

void AccountData::setDateOpened(int dateOpened){
    this->dateOpened = dateOpened;
}

void AccountData::setAccountType(char accountType){
    this->accountType = accountType;
}

void AccountData::setAdmin(int admin){
    this->admin = admin;
}

void AccountData::setAccountNum(int accountNum){
    this->accountNum = accountNum;
}

// getters
std::string AccountData::getUsername(){
    return this->username;
}

std::string AccountData::getPassword(){
    return this->password;
}

std::string AccountData::getFName(){
    return this->fname;
}

std::string AccountData::getLName(){
    return this->lname;
}

int AccountData::getSSN(){
    return this->ssn;
}

double AccountData::getBalance(){
    return this->balance;
}

std::string AccountData::getDateOpened(){
    std::string formattedDate = std::to_string(this->dateOpened);
    formattedDate.insert(4, 1, '-');
    formattedDate.insert(7, 1, '-');

    return formattedDate;
}

char AccountData::getAccountType(){
    return this->accountType;
}

int AccountData::getAdmin(){
    return this->admin;
}

int AccountData::getAccountNum(){
    return this->accountNum;
}