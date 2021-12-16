#include <iostream>
#include <cassert>

// recursive fibonacci
long int rec_fib(int i){
    if(i < 2){
        return i;
    }
    else{
        return rec_fib(i-1) + rec_fib(i-2);
    }
}

// non-recursive fibonacci
void fib(){
    long int x = 0, y = 1, output = 0;

    for(int i = 0; i < 50; i++){
        if(i < 2){
            std::cout << i << ": " << i << std::endl;
        }
        else{
            output = x + y;
            x = y;
            y = output;

            std::cout << i << ": " << output << std::endl;
        }
    }   
}

int main(){
    // commented out because recursive function wanted
    //fib()

    for(int i = 0; i < 50; i++){
        std::cout << i << ": " << rec_fib(i) << std::endl;
    }

    assert(rec_fib(8) == 21);
    assert(rec_fib(20) == 6765);
}