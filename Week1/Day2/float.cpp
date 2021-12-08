#include <iostream>
#include <cassert>
#include <iomanip>

void function(float success, float fail){
	assert(success == 3); // assert should pass
	assert(fail != 3.1);
	std::cout << fail << std::endl;
}

int main(){
	double pi = 3.14159;
	std::cout << "pi = " << pi << std::endl;

	std::cout << "pi with a precision of 0: " << std::fixed << std::setprecision(0) << pi << std::endl;
	std::cout << "pi with a precision of 1: " << std::fixed << std::setprecision(1) << pi << std::endl;
	std::cout << "pi with a precision of 2: " << std::fixed << std::setprecision(2) << pi << std::endl;
	std::cout << "pi with a precision of 3: " << std::fixed << std::setprecision(3) << pi << std::endl;
	std::cout << "pi with a precision of 4: " << std::fixed << std::setprecision(4) << pi << std::endl;
	std::cout << "pi with a precision of 5: " << std::fixed << std::setprecision(5) << pi << std::endl;
	std::cout << "pi with a precision of 6: " << std::fixed << std::setprecision(6) << pi << std::endl;
	std::cout << "pi with a precision of 7: " << std::fixed << std::setprecision(7) << pi << std::endl;

}
