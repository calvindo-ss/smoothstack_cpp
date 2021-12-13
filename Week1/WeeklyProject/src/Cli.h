#include <iostream>

class Cli{
    public:
        Cli();
        void run();
        bool login();
        bool checkIfAccountExists(std::string username, std::string password);
        bool checkIfAccountExists(int accountNum);
        bool showMenu();

        void showAllAccounts(); // shows all accounts
        void searchAccountNum(); //show account based on account number
        void searchAccountName(); // show account based on name
        void newAccount();
        void closeAccount();

    private:
        void displayAccount(int accountNumber); // show account based on
        void displayAccount(std::string fname, std::string lname);
};