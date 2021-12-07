#include <iostream>
#include <string>

int main(){
	std::string str = "Hello, world!?";
	
	for(int i = 0; i < str.length(); i++){
		std::cout << str[i];
	}
	std::cout << std::endl;

	return 0;
}
