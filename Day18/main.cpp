#include <iostream>
#include <cassert>

#include "myvector.h"

int main(void){
    MyVector<int> mv;               // test initialization
    assert(mv.size() == 0);        
    assert(mv.capacity() == 0);

    mv.push_back(1);                // test push_back()
    assert(mv.size() == 1);         // test increase is mSize
    assert(mv.capacity() == 1);     // test increase in capacity
    assert(mv[0] == 1);             // test operator[]
    assert(mv.at(0) == 1);          // test at()

    mv.push_back(5);
    assert(mv.size() == 2);
    assert(mv.capacity() == 2);
    assert(mv[1] == 5);
    assert(mv.at(1) == 5);
    
    mv.push_back(10);
    assert(mv.size() == 3);
    assert(mv.capacity() == 4);
    assert(mv[2] == 10);
    assert(mv.at(2) == 10);

    mv.push_back(15);
    assert(mv.size() == 4);
    assert(mv.capacity() == 4);
    assert(mv[3] == 15);
    assert(mv.at(3) == 15);

    mv.push_back(20);
    assert(mv.size() == 5);
    assert(mv.capacity() == 8);
    assert(mv[4] == 20);
    assert(mv.at(4) == 20);

    mv.pop_back();                  // test pop_back()
    assert(mv.size() == 4);
    assert(mv.capacity() == 8);
    assert(mv[4] != 20);
    assert(mv.at(4) != 20);

    // test copy constructor
    MyVector<int> mv1(mv);
    assert(mv.size() == 4);
    assert(mv.capacity() == 8);
    assert(mv[3] == 15);
    assert(mv.at(3) == 15);

    // test clear()
    mv.clear();                     
    assert(mv.size() == 0);
    assert(mv.capacity() == 0);

    // test copy assignment operator
    mv = mv1;
    assert(mv.size() == 4);
    assert(mv.capacity() == 8);
    assert(mv[3] == 15);
    assert(mv.at(3) == 15);

    // test move constructor
    MyVector<int> mv2 = std::move(mv1);
    assert(mv2.size() == 4);    
    assert(mv2.capacity() == 8);
    assert(mv2[0] == 1);             
    assert(mv2.at(0) == 1);

    assert(mv1.size() == 0);    
    assert(mv1.capacity() == 0);

    mv.clear();

    // test move assignment operator
    mv = std::move(mv2);
    assert(mv.size() == 4);
    assert(mv.capacity() == 8);
    assert(mv[0] == 1);             
    assert(mv.at(0) == 1);
}