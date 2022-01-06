#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <vector>

#include "mystring.h"

int main(void){
    char a_string[] = "Quick brown fox jumps over the lazy fox";

    // constructor
    MyString ms(a_string);
    std::cout << ms.get_string() << std::endl << std::endl;

    assert(ms.get_string() == a_string);

    // copy constructor example
    MyString ms1 = ms;
    std::cout << ms1.get_string() << std::endl << std::endl;

    assert(ms1.mystring == ms.mystring);

    // move constructor example
    MyString ms2 = std::move(ms1);
    std::cout << ms2.get_string() << std::endl << std::endl;

    assert(ms1.mystring == nullptr);
    assert(ms2.mystring == ms.mystring);

    // copy assignment operator example
    char b_string[] = "Hello, world!";
    MyString ms3(b_string);
    ms = ms3;
    std::cout << ms.get_string() << std::endl << std::endl;

    //assert(ms.get_string() == ms3.get_string());

    // move assignment operator example
    char c_string[] = "foo bar";
    MyString ms4(c_string);
    ms = std::move(ms4);
    std::cout << ms.get_string() << std::endl << std::endl;

    assert(ms4.mystring == nullptr);
    assert(ms.mystring == c_string);

    // + operator overload
    std::cout << (ms+ms).get_string() << std::endl << std::endl;

    assert((ms+ms).mystring = "foo barfoo bar");

    // + operator overload
    ms.mystring = c_string;
    std::cout << (ms*5).get_string() << std::endl << std::endl;
    
    assert((ms*5).mystring = "foo barfoo barfoo barfoo barfoo bar");

    // [] operator overload
    std::cout << ms3[10] << std::endl << std::endl;

    assert(ms3[10] == 'l');
}  