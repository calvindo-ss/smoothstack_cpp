#include <iostream>
#include <vector>
#include <cassert>

int main(){
	float test_array[] = {1.1, 1.2, 1.3};
	std::vector<float> test_vector;
	int sizeof_array = sizeof(test_array)/sizeof(float); 

	// inserts test_array into test_vector
	// instert() requires vector position, first element of arr, last element of arr
	test_vector.insert(test_vector.begin(), std::begin(test_array), std::end(test_array));

	std::cout << "Print out vector elements:" << std::endl;
	for(int i=0; i<test_vector.size(); i++){
		std::cout << test_array[i] << " ";
	}
	std::cout << std::endl;

	// verify values in array and vector
	for(int j=0; j<sizeof_array; j++){
		assert(test_array[j]==test_vector[j]);
	}
}
