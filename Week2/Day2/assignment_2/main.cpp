#include <iostream>
#include <cassert>
#include <cmath>

long fib(long num){
    double phi = (1 + sqrt(5)) / 2;

    double psi = (1 - phi);

    return (pow(phi, num) - pow(psi, num)) / (phi - psi);
}

long fib_inv(long num){
    double phi = (1 + sqrt(5)) / 2;

    return std::floor(log(num * sqrt(5) + 0.5) / log(phi)); // returns inverted binet's formula
}

int main(){
    long largest_fib = fib_inv(INT32_MAX);

    std::cout << "Largest index before overflow of int32: " << largest_fib << std::endl;

    assert(fib_inv(INT32_MAX) == 46);
    assert(fib_inv(INT64_MAX) == 92);
}