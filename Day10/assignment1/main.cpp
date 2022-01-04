#include <iostream>
#include <cassert>
#include <string>

// I cannot figure out how to delete the old Person pointer and return a new Person pointer
// Instead I remove the name of the previous instance of a repeated name
// Therefore I am not technically deleting the repeated pointer, but rather hiding it

class Person { 
    private: 
        static int _index;
        
        Person(std::string lname){
            name = lname;

            for(int i = 0; i < _index; i++){
                if(_persons[i]->name == lname && i != _index){
                    count++;
                    
                    _persons[i]->name = ""; // this sets the repeated name to an empty string
                }
            }
        }

    public:
        std::string name;
        int count = 1;
        static Person* _persons[5];

        static Person* getPerson(std::string lname){    

            _persons[_index] = (Person*) new Person(lname);
            _index++;

            return (Person*)(_persons[_index - 1]);
        }
};

int Person::_index = 0;
Person *Person::_persons[] = {nullptr, nullptr, nullptr, nullptr, nullptr};

int main(void) {

    std::string names[] = {"bob", "james", "janet", "bob", "stella"};
    Person *persons[5];

    for(int i = 0; i < 5 ; i++){
        persons[i] = Person::getPerson(names[i]);
    }

    for (int ii = 0; ii < 5; ii++) {
        // checks for an empty string
        if(persons[ii]->name != ""){
            std::cout << persons[ii]->name << ": " << persons[ii]->count << std::endl;
        }
    }   
}