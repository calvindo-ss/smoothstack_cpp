#include <iostream>
#include <cassert>
#include <string>

// I cannot figure out how to delete the old Person pointer and return a new Person pointer
// I am trying to overwrite the old pointer with a new pointer, but it does not work for me
// My current workaround is to set the repeated object's name to "" and filter those out

class Person { 
    private: 
        static int _index;
        
        Person(std::string lname): name(lname){
            for(int i = 0; i < _index; i++){
                if(_persons[i] != nullptr){
                    if(lname == _persons[i]->name){
                    count += _persons[i]->count;
                    _persons[i]->name = "";
                    }
                }
                
            }   
        }

        Person(){   // set object to nullptr if no name is provided
            _persons[_index] = nullptr;
        }

    public:
        std::string name;
        int count = 1;
        static Person* _persons[10];

        static Person* getPerson(std::string lname){
            if(lname != ""){
                _persons[_index] = (Person*) new Person(lname);
                _index++;
            }
            else{                
            _persons[_index] = (Person*) new Person();
            }
            
            return (Person*)(_persons[_index]);
        }
};

int Person::_index = 0;
Person *Person::_persons[] = {nullptr};

int main(void) {

    std::string names[10] = {"bob", "james", "janet", "bob", "stella", "bob", "bob"};
    Person *person;

    for(int i = 0; i < 10 ; i++){
        person = Person::getPerson(names[i]);
    }

    for (int ii = 0; ii < 10; ii++) {
        if(Person::_persons[ii] != nullptr && Person::_persons[ii]->name != ""){
            std::cout <<Person:: _persons[ii]->name << ": " << Person::_persons[ii]->count << ", ";
        }
    }   
    std::cout << std::endl;
}