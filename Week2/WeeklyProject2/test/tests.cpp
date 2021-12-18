#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include "Cli.h"
#include "AccountData.h"

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(user_class, get_user_data_accountNum){
    int accountNum = 123456;

    AccountData *localUser = new AccountData();

    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("../src/users.txt");              // username, password, fname, lname, ssn, balance, date, account type, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;

        while(getline(ss, tmp, delimiter)){     // reads a single line and pushes to userData
            userData.push_back(tmp); 
        }
            
        localUser->setUserData(userData);       // sets userData to localUser obj

        if(localUser->getAccountNum() == accountNum){
            break;
        }
    }
    file.close();

    ASSERT_EQ(localUser->getUsername(), "hello");
    ASSERT_EQ(localUser->getPassword(), "world");
    ASSERT_EQ(localUser->getFName(), "Calvin");
    ASSERT_EQ(localUser->getLName(), "Do");
    ASSERT_EQ(localUser->getSSN(), 123456789);
    ASSERT_EQ(localUser->getBalance(), 123.23);
    ASSERT_EQ(localUser->getDateOpened(), "2021-12-11");
    ASSERT_EQ(localUser->getAccountType(), 'C');
    ASSERT_EQ(localUser->getAdmin(), 1);
    ASSERT_EQ(localUser->getAccountNum(), 123456);

    delete localUser;
}

TEST(user_class, get_user_data_accountNum1){
    int accountNum = 431256;

    AccountData *localUser = new AccountData();

    // create file obj and opens users.txt
    std::fstream file;
    std::string tmp, line;
    char delimiter = ',';

    file.open("../src/users.txt");              // username, password, fname, lname, ssn, balance, date, account type, admin, accountnum

    while(getline(file, line)){                 // reads each line in file
        std::stringstream ss(line);
        std::vector<std::string> userData;

        while(getline(ss, tmp, delimiter)){     // reads a single line and pushes to userData
            userData.push_back(tmp); 
        }
            
        localUser->setUserData(userData);       // sets userData to localUser obj

        if(localUser->getAccountNum() == accountNum){
            break;
        }
    }
    file.close();

    ASSERT_EQ(localUser->getUsername(), "thinmints");
    ASSERT_EQ(localUser->getPassword(), "girlscouts");
    ASSERT_EQ(localUser->getFName(), "Grace");
    ASSERT_EQ(localUser->getLName(), "Lee");
    ASSERT_EQ(localUser->getSSN(), 345672216);
    ASSERT_EQ(localUser->getBalance(), 850.26);
    ASSERT_EQ(localUser->getDateOpened(), "2020-03-22");
    ASSERT_EQ(localUser->getAccountType(), 'C');
    ASSERT_EQ(localUser->getAdmin(), 0);
    ASSERT_EQ(localUser->getAccountNum(), 431256);

    delete localUser;
}

TEST(user_class, set_arbitrary_user_data){
    AccountData *localUser = new AccountData();

    std::vector<std::string> userData = {"foo", "bar", "Camel", "Case", "101010101", "10.01", "20211212", "C", "0", "321123"};

    localUser->setUserData(userData);

    ASSERT_EQ(localUser->getUsername(), "foo");
    ASSERT_EQ(localUser->getPassword(), "bar");
    ASSERT_EQ(localUser->getFName(), "Camel");
    ASSERT_EQ(localUser->getLName(), "Case");
    ASSERT_EQ(localUser->getSSN(), 101010101);
    ASSERT_EQ(localUser->getBalance(), 10.01);
    ASSERT_EQ(localUser->getDateOpened(), "2021-12-12");
    ASSERT_EQ(localUser->getAccountType(), 'C');
    ASSERT_EQ(localUser->getAdmin(), 0);
    ASSERT_EQ(localUser->getAccountNum(), 321123);

    delete localUser;
}

// limitation of this test is that it requires User object to run
/*
TEST(cli_class, checkIfAccountExists_user_pass){
    Cli cli;

    ASSERT_TRUE(cli.checkIfAccountExists("foo", "bar"));
    ASSERT_TRUE(cli.checkIfAccountExists("camel", "case"));
    ASSERT_TRUE(cli.checkIfAccountExists("foo", "bar"));
    ASSERT_TRUE(cli.checkIfAccountExists("lampshade", "lamplamp"));
    ASSERT_TRUE(cli.checkIfAccountExists("disk", "drive"));

    ASSERT_FALSE(cli.checkIfAccountExists("hello", "world!"));
    ASSERT_FALSE(cli.checkIfAccountExists("thiss", "isssss"));
    ASSERT_FALSE(cli.checkIfAccountExists("aaaaaa", "testt"));
}
*/

TEST(cli_class, checkIfAccountExists_accountnum){
    Cli cli;

    ASSERT_TRUE(cli.checkIfAccountExists(123456));
    ASSERT_TRUE(cli.checkIfAccountExists(431256));
    ASSERT_TRUE(cli.checkIfAccountExists(654321));
    ASSERT_TRUE(cli.checkIfAccountExists(753159));
    ASSERT_TRUE(cli.checkIfAccountExists(123321));

    ASSERT_FALSE(cli.checkIfAccountExists(000000));
}