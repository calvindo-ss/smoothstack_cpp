#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Converting ints and floats into strings allows both data types to be stored in a single array/vector.
// The issue with this hack is that it is much more difficult to identify the types of each element (int or float)
// In order to identify types, I use '.' as an identifier for floats and assume everything else is an int.
// However, this assumes all numbers with '.' is a float, ignoring double types.

int main(void){
    // initialize arrays of ints, floats
    constexpr int int_arr[] = {1, 2, 3, 4};
    constexpr float float_arr[] = {1.1, 2.2, 3.3, 4.4};

    std::vector<std::string> string_arr; 

    // pushes ints and floats into vector as strings
    for(int i=0; i<4; i++){
        string_arr.push_back(std::to_string(int_arr[i]));
        string_arr.push_back(std::to_string(float_arr[i]));
    }

    // print out array/string containing ints and floats
    std::cout << "This is a mixed array of ints and floats: " << std::endl;
    for(int k=0; k<string_arr.size(); k++){
        std::cout << string_arr[k] << " ";
    }
    std::cout << std::endl << std::endl;


    char ch = '.'; // identifier for floats

     // prints each element of the vector
    for(int j=0; j<string_arr.size(); j++){
        std::string st = string_arr[j];

        // checks if the string containts '.'
        if(st.find(ch) != std::string::npos){
            float num_float = std::stof(st);
            std::cout << num_float << " is a float!" << std::endl;

            // assert that the mixed float value == the original float
            if(j%2==1){
                assert(float_arr[j/2]==num_float);
            }
        }

        // if no '.' found, converts string to int
        else{
            int num_int = std::stoi(st);
            std::cout << num_int << " is an int!" << std::endl;

            // assert that the mixed float value == the original float
            if(j%2==0){
                assert(int_arr[j/2]==num_int);
            }
        }
    }
}