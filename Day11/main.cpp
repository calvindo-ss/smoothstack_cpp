#include <iostream>
#include <vector>

#include "sentence.h"

int main(void){
    char sent1[] = "\"Quick brown fox jumps over the lazy fox\"";
    int size1 = sizeof(sent1)/ sizeof(sent1[0]);

    Sentence s(sent1, size1); // calls default constructor

    std::cout << s.data() << std::endl;    // calls copy constructor
    std::cout << "The number of words in the string is: " << s.num_words() << std::endl;
    std::cout << "The 3rd word in the string is: " << s.get_word(3) << std::endl << std::endl;

    char sent2[] = "\"Hello, World! This is a test\"";
    int size2 = sizeof(sent1)/ sizeof(sent1[0]);

    s.replace(sent2, size2);

    std::cout << s.data() << std::endl;
    std::cout << "The number of words in the string is: " << s.num_words() << std::endl;
    std::cout << "The 2nd word in the string is: " << s.get_word(2) << std::endl << std::endl;

    char sent3[] = "\"Foo bar Camel case\"";
    int size3 = sizeof(sent3)/ sizeof(sent3[0]);
    Sentence s1(sent3, size3); // calls default constructor

    s = s1; // calls copy assignment operator
    std::cout << s.data() << std::endl;
    std::cout << "The number of words in the string is: " << s.num_words() << std::endl;
    std::cout << "The 3rd word in the string is: " << s.get_word(3) << std::endl << std::endl;

    std::vector<Sentence> vec;
    char sent4[] = "\"My name is calvin\"";
    vec.push_back(Sentence(sent4, 17)); // calls move constructor
    std::cout << std::endl;

    char sent5[] = "\"C++ is a great language!\"";
    s = Sentence(sent5,24);
    std::cout<< s.data() << std::endl;


}