#include <iostream>
#include <limits>

int main(){
    while(1){
        int choice;

        std::cout << "1. Get the size of an int: " << std::endl;
        std::cout << "2. Get the size of an double: " << std::endl;
        std::cout << "3. Get the size of an char: " << std::endl;
        std::cout << "4. Exit: " << std::endl;
        std::cout << "Select an entry: ";
        std::cin >> choice;

        switch(choice){
            case 1:{
                int input;

                std::cout << "Enter an integer: ";
                std::cin >> input;

                if(std::cin.good()){
                    std::cout << "The size of int " << input << " is: " << sizeof(input) << std::endl << std::endl;
                }
                else{
                    std::cout << "Invalid input" << std::endl;
                    std::cin.clear(); 
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                break;
            }
            case 2:{
                double input;

                std::cout << "Enter an double: ";
                std::cin >> input;
                std::cout << "The size of double " << input << " is: " << sizeof(input) << std::endl << std::endl;

                break;
            }
            case 3:{
                char input;

                std::cout << "Enter an char: ";
                std::cin >> input;
                std::cout << "The size of char " << input << " is: " << sizeof(input) << std::endl << std::endl;

                break; 
            }       
            case 4:
                return 0;
            default:
                break;
        }

        // clears std::cin if bad input
        while(!std::cin){
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}