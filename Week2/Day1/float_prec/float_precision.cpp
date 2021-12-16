#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include <cassert>
#include <iomanip>

double calculate_float(int &den){
    for(long int n = 0; n < 1000; n++){

        long int lower = pow(2, 51);
        long int upper = pow(2, 53);
        long int num = (pow(2, n)/den);

        if(num >= lower && num < upper){
           return n;
        }
    }
    return 0;
}

// calculates greatest common denominator
int grcd(int a, int b){
    if(a == 0){
        return b;
    }
    else if(b == 0){
        return a;
    }

    if(a < b){
        return grcd(a, b % a);
    }
    else{
        return grcd(b, a % b);
    }

}

int dTof(double num){
    double integral = std::floor(num); //calculates integral of the decimal

    double fractional = num - integral; //calculates fractional of the decimal

    long precision = 1000000000;

    long long greatest_common_denominator = grcd(fractional * precision, precision);

    long long denominator = precision/greatest_common_denominator;

    return denominator;
}



int main(){
    double fraction;

    std::cout << "Enter a fraction in decimal form: ";
    std::cin >> fraction;

    long int j = 0, n;

    int den = dTof(fraction);

    n = calculate_float(den);
    j = pow(2, n)/den;

    double f = j/pow(2, n);
    //std::cout << den << std::endl;
    std::cout << std::fixed << std::setprecision(55) << "J = " << j << ", N = " << n << " " << f << std::endl;
}