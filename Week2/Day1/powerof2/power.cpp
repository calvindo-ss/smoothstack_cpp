#include <iostream>

bool isPower(int a){
    // bitwise & operator returns 1 only if both bits are 1
    // in this operation, returning all 0 bits would mean the number is a power of 2
    // subtracting 1 from a power of 2, would set all bits to 1
    // the first operand would consist of 100...000, the second operator would be 0111...111
    // applying the & operator would set all the bits to 0000...000, meaning the number is a power of 2
    if((a & (a - 1)) == 0){
        return true;
    }
    return false;
}

int main(){
    int num;

    std::cout << "Enter a number to determine if it is a power of 2:";
    std::cin >> num;

    if(isPower(num) == true){
        std::cout << num << " is a power of 2" << std::endl;
    }
    else{
        std::cout << num << " is not a power of 2" << std::endl;
    }
}