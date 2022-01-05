#include <iostream>
#include <cassert>
#include <string>

class Person { 
    private: 
        int index;

    public:
        Person(std::string lname){
            this->name = lname;

            Person* p = getPerson(name);

            // if object has nullptr, set object as this
            if(p == nullptr) {
                for(int i = 0; i < 10; i++) {
                    if(_persons[i] == nullptr) {
                        _persons[i] = this;
                        index = i;
                        break;
                    }
                }
            } 
            
            // if matching object is found, increment count, set index to last matching index, overwrite old pointer with new one
            else {
                count += p->count;
                index = p->index;
                _persons[index] = this;
                delete p;
            }
        };

        std::string name;
        int count = 1;
        static inline Person* _persons[10] {nullptr};

        static Person* getPerson(std::string lname){
            for(int j = 0; j < 10; j++) {
                if(_persons[j] == nullptr)
                    break;
                    
                if(_persons[j]->name == lname) // returns first object if matching name found
                    return _persons[j];
            }

            return nullptr;
        }
};

int main(void) {
    std::string names[10] = {"bob", "james", "janet", "bob", "stella", "bob", "bob", "james"};

    Person *person;

    // create objects
    for(int i = 0; i < 10 ; i++){
        person = new Person(names[i]);
    }

    // displays data
    for (int ii = 0; ii < 10; ii++) {
        if(Person::_persons[ii] == nullptr || Person::_persons[ii]->name == ""){
            break;
        }

        std::cout <<Person:: _persons[ii]->name << ": " << Person::_persons[ii]->count << ", ";
    }

    std::cout << std::endl;


    assert(Person:: _persons[0]->name == "bob");
    assert(Person:: _persons[0]->count == 4);
    assert(Person:: _persons[1]->name == "james");
    assert(Person:: _persons[1]->count == 2);
    assert(Person:: _persons[2]->name == "janet");
    assert(Person:: _persons[2]->count == 1);
}