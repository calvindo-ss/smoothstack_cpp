#include <iostream>
#include <cassert>

int add(int a, int b){
    return a + b;
}

int subtract(int a, int b){
    return a - b;
}

int multiply(int a, int b){
    return a * b;
}

int divide(int a, int b){       // a 4th function will not work with checking a 4th bit
    return a / b;
}

int (*funcptrs[3])(int, int) = {&add,    // 0000 0001
                           &subtract,    // 0000 0010
                           &multiply};   // 0000 0100

int compute(int arg1, int arg2, unsigned char funcmask){

    return funcptrs[funcmask >> 1](arg1, arg2);     // need to right shift to make 1,2,4 to 0,1,2
}

int main(){
    int a = 10, b = 25;

    // loops throught the 3 bits
    for(int i = 0; i < 3; i++){     // if I add a 4th bit, it will segfault because it'll index to 4

        char funcbit = 1 << i;

        std::cout << compute(a, b, funcbit) << std::endl;
    }

    // tests
    int bit = 1;

    assert(compute(a, b, bit << 0) == 35);
    assert(compute(a, b, bit << 1) == -15);
    assert(compute(a, b, bit << 2) == 250);
    
    assert(funcptrs[0](a, b) == 35);
    assert(funcptrs[1](a, b) == -15);
    assert(funcptrs[2](a, b) == 250);
}

