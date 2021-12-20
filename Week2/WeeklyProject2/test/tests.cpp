#include <iostream>
#include <fstream>

#include <gtest/gtest.h>

#include "AccountData.h"
#include <ProtoReadWrite.h>
#include <Transaction.h>

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(AccountData, AccountData_set_and_get){
    AccountData *localUser = new AccountData();

    localUser->setAccountNum(123456);
    localUser->setUsername("hello");
    localUser->setPassword("world");
    localUser->setFName("Calvin");
    localUser->setLName("Do");
    localUser->setSSN(123456789);
    localUser->setBalance(123.23);
    localUser->setDateOpened(20211211);
    localUser->setAccountType('C');
    localUser->setAdmin(1);    

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

TEST(ProtoReadWrite, ProtoReadWrite_check_account_exists_u_p){
    std::string protofile = "Account.data";
    // init protobuf
    auto accounts = pb::Accounts();

    ProtoReadWrite prw(protofile, accounts);
    std::string u1 = "admin", p1 = "password";
    std::string u2 = "tacobell", p2 = "fastfood";

    ASSERT_TRUE(prw.check_account_exists(u1, p1));
    ASSERT_FALSE(prw.check_account_exists(u2, p2));
}

TEST(ProtoReadWrite, ProtoReadWrite_check_account_exists_num){
    std::string protofile = "Account.data";
    // init protobuf
    auto accounts = pb::Accounts();

    ProtoReadWrite prw(protofile, accounts);

    int a = 123456, b = 111111, c = 222222;
    int d = 654123, e = 852147, f = 963456;

    ASSERT_TRUE(prw.check_account_exists(a));
    ASSERT_TRUE(prw.check_account_exists(b));
    ASSERT_TRUE(prw.check_account_exists(c));


    ASSERT_FALSE(prw.check_account_exists(d));
    ASSERT_FALSE(prw.check_account_exists(e));
    ASSERT_FALSE(prw.check_account_exists(f));
}

TEST(Transaction, Transaction_check_balance){
    std::string protofile = "Account.data";
    // init protobuf
    auto accounts = pb::Accounts();

    ProtoReadWrite prw(protofile, accounts);
    AccountData accountdata;

    Transaction transaction(prw, 125.25, accountdata);

    double a = 100.00, b = 10.00, c = 50.00;
    double d = 125.25, e = 150.23, f = 125.26;

    ASSERT_TRUE(transaction.check_balance(a));
    ASSERT_TRUE(transaction.check_balance(b));
    ASSERT_TRUE(transaction.check_balance(c));

    ASSERT_FALSE(transaction.check_balance(d));
    ASSERT_FALSE(transaction.check_balance(e));
    ASSERT_FALSE(transaction.check_balance(f));
    

}