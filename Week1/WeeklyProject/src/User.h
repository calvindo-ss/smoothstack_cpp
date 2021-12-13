#include <iostream>
#include <ctime>
#include <vector>

class User{
    public:
        User();

        // setter
        void setUserData(std::vector<std::string> userData);
        
        // getter
        std::string getUsername();        
        std::string getPassword();
        std::string getFName();
        std::string getLName();
        int getSSN();
        double getBalance();
        std::string getDateOpened(); // change to std::time_t when possible
        char getAccountType();
        int getAdmin();
        int getAccountNum();

    private:
        std::string username, password;
        std::string fname, lname;
        int ssn;
        double balance;
        int dateOpened;
        char accountType; // checking 'c' or savings 's'
        int admin;
        int accountNum;

        void setUsername(std::string);
        void setPassword(std::string);
        void setFName(std::string);
        void setLName(std::string);
        void setSSN(int);
        void setBalance(double);
        void setDateOpened(int);
        void setAccountType(char);
        void setAdmin(int);
        void setAccountNum(int);
};

class Customer: public User{

};

class Admin: public User{
    public:
    
};