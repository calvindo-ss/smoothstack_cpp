#include <iostream>
#include <string>

class MyString{
    private:
    public:
        char *mystring;
        
        MyString();

        MyString(char* c);

        MyString(const MyString& ms); // copy constructor

        MyString(MyString&& ms); // move constructor

        MyString& operator = (const MyString& ms); // copy assignment operator

        MyString& operator = (MyString &&ms); // move assignment operator

        MyString& operator + (const MyString& ms); // + operator

        MyString& operator * (const int& num); // * operator

        char& operator [] (const int& num); // * operator
    
        char* get_string();

        ~MyString();
};