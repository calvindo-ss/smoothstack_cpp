#include <iostream>
#include <string.h>

#include "sentence.h"

Sentence::Sentence(char* sent, int size): sentence(sent), size(size){
    //std::cout << "Default constructor has been called" << std::endl;
    vsentence.push_back(0);     // pushes index 0 of char array assuming no leading space

    for(int i = 0; i < size; i++){
        if(sentence[i] == ' '){
            vsentence.push_back(i+1);
        }
    }
}

Sentence::Sentence(const Sentence &copy){   // copy constructor
    std::cout << "Copy constructor has been called" << std::endl;

    sentence = new char[strlen(copy.sentence) + 1];
    strcpy(sentence, copy.sentence);             
}

Sentence &Sentence::operator = (const Sentence &copy){  // copy assignment operator
    std::cout << "Copy assignment operator has been called" << std::endl;
    
    sentence = new char[strlen(copy.sentence) + 1]; // deep copy
    strcpy(sentence, copy.sentence);
    
    size = copy.size;   // copy size

    vsentence.clear();
    vsentence.push_back(0); // pushes index 0 of char array assuming no leading space
    for(int i = 0; i < size; i++){  // finds word offsets
        if(sentence[i] == ' '){
            vsentence.push_back(i+1);
        }
    }

    return *this;
}

char *Sentence::data(){    
    return sentence;
}

int Sentence::num_words() const{
    return vsentence.size();
}

std::string Sentence::get_word(int n){
    int pos1 = vsentence.at(n-1);
    int len = vsentence.at(n) - pos1;

    // convert char* to string
    std::string word(sentence);

    return word.substr(pos1, len);
}

void Sentence::replace(char* sent, int lsize){
    sentence = sent;
    size = lsize;

    vsentence.clear();
    vsentence.push_back(0);

    for(int i = 0; i < size; i++){
        if(sentence[i] == ' '){
            vsentence.push_back(i+1);
        }
    }
}

Sentence::Sentence(Sentence &&move){
    std::cout << "Move constructor has been called" << std::endl;

    sentence = move.sentence;
    size = move.size;
    vsentence = move.vsentence;
    
    move.sentence = nullptr;
    move.size = 0;
    vsentence.clear();
}

Sentence &Sentence::operator = (Sentence &&move){
    std::cout << "Move assignment operator has been called" << std::endl;
    if(this == &move){
        return *this;
    }

    delete [] sentence;
    sentence = move.sentence;
    size = move.size;
    vsentence = move.vsentence;
    
    move.sentence = nullptr;
    move.size = 0;
    vsentence.clear();

    return *this;
}

Sentence::~Sentence(){
    std::cout << "Destructor has been called" << std::endl;

    sentence = nullptr;
    size = 0;
    vsentence.clear();
    
    delete sentence;
}