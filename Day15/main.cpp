#include <stdexcept>
#include <string>
#include <cassert>

std::string err = "Both floats are not representable as integers.";

bool is_equal(float a, float b){
    int a1 = a;
    int b1 = b;

    float temp1 = a - a1; 
    float temp2 = b - b1;

    if(temp1 > 0 || temp2 > 0){
        throw std::invalid_argument(err);
    }
    else if(a1 == b1){
        return true;
    }
    else{
        return false;
    }
}

int main() {
    assert(is_equal(6.0, 6.0) == true);
    assert(is_equal(6.0, 5.0) == false);

    // the following 2 lines will cause the program to throw an exception and terminate when uncommented
    //assert(is_equal(6.1, 6.1) == true);
    //assert(is_equal(6.1, 6.0) == false);
}