#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <iomanip>

std::mutex m;

void hailstone(std::vector<int>& nums, int th){
    while(true){
        m.lock();
        // simulates algorithm for an index of 20
        if(nums.size() > 19){
            m.unlock();
            break;
        }
        int last = nums.back();
        if(last % 2 == 0){
            nums.push_back(last/2);
        }
        else if(last % 2 == 1){
            nums.push_back((last*3)+1);
        }

        m.unlock();
    }
}

int main(void){
    // runs the hailstone algorithm 5 times
    for(int i = 0; i < 5; i++){
        int num = 11;
        std::vector<int> nums;
        nums.push_back(num);

        // sets 4 parallel threads
        int numThreads = 4;
        std::vector<std::thread> threads;

        for(int i = 0; i < numThreads; i++){
            std::thread t(hailstone, std::ref(nums), i);
            threads.push_back(std::move(t));
        }

        for(auto& t:threads){
                t.join();
        }
        threads.clear();

        std::cout << "Index:  ";
        for(int j = 0; j < nums.size(); j++){
            std::cout << std::setw(2) << j << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Value:  ";
        for(int k = 0; k < nums.size(); k++){
            std::cout << std::setw(2) << nums.at(k) << " ";
        }
        std::cout << std::endl << std::endl;
    }
}