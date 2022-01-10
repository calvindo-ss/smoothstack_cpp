#include <iostream>
#include <cstring>

#include "mystring.h"

MyString::MyString(){};

// constructor
MyString::MyString(char* c): mystring(c){
    //std::cout << "Constructor has been called" << std::endl;
};

// copy constructor
MyString::MyString(const MyString& ms){
    std::cout << "Copy constructor has been called" << std::endl;
    
    //char* tempchar = new char;
    //for(int i = 0; ms.mystring[i] != 0; i++){
    //    *(tempchar+i) = *(ms.mystring+i);
    //}
    //mystring = tempchar;

    mystring = new char[strlen(ms.mystring) + 1];
    mystring[strlen(ms.mystring)] = '\0';
    mystring = ms.mystring;
}

// move constructor
MyString::MyString(MyString&& ms){
    std::cout << "Move constructor has been called" << std::endl;
    mystring = ms.mystring;

    ms.mystring = nullptr;
}

// copy assignment operator
MyString &MyString::operator = (const MyString &ms){ 
    std::cout << "Copy assignment operator has been called" << std::endl;
    
    mystring = new char[strlen(ms.mystring) + 1];
    strcpy(mystring, ms.mystring);
    mystring[strlen(ms.mystring)] = '\0';

    return *this;
}

// move assignment operator
MyString& MyString::operator = (MyString &&ms){ 
    std::cout << "Move assignment operator has been called" << std::endl;
    mystring = ms.mystring;
    ms.mystring = nullptr;

    return *this;
}

// + operator overload
MyString& MyString::operator + (const MyString& ms){    // I don't like how this overload was implemented
    std::cout << "+ operator overload has been called" << std::endl;
    
    int len = strlen(mystring) + strlen(ms.mystring);
    char* lhs = mystring;
    char* rhs = ms.mystring;
    mystring = new char[len + 1];

    strcpy(mystring, lhs);
    strcat(mystring, rhs);
    mystring[len] = '\0';

    return *this;
} 
// * operator overload
MyString& MyString::operator * (const int& num){
    std::cout << "* operator overload has been called" << std::endl;

    int len = strlen(mystring)*num;
    char* temp = mystring;
    mystring = new char[len + 1];
    mystring[len] = '\0';


    strcpy(mystring, temp); // copy first element
    for(int i = 0; i < num-1; i++){  // concatenate the rest of the elements
        strcat(mystring, temp);
    }
    return *this;
}

// [] operator overload
char& MyString::operator [] (const int& num){
    std::cout << "[] operator overload has been called" << std::endl;

    int len = strlen(mystring);
    if(num < 0 && num > len){
        return this->mystring[0];
    }

    return this->mystring[num];
}

char* MyString::get_string(){
    return mystring;
}

MyString::~MyString(){
    mystring = nullptr;

    delete mystring;
}