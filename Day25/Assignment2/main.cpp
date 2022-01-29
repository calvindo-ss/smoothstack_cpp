#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>
#include <cassert>
  
template <typename RandomIt>
void parallel_sum(RandomIt beg, RandomIt end, std::promise<int> p) {
    auto len = end - beg;
    
    // if less than 1000, don't split
    if (len < 1000){
        p.set_value(std::accumulate(beg, end, 0));
        return;
    }
 
    RandomIt mid = beg + len/2;
    
    // get first half of vector
    std::promise<int> first_half_p;
    std::future<int> first_half_f = first_half_p.get_future();
    parallel_sum(beg, mid, std::move(first_half_p));

    // get second half of vector and create another thread
    std::promise<int> second_half_p;
    std::future<int> second_half_f = second_half_p.get_future();
    std::thread t(parallel_sum<RandomIt>, mid, end, std::move(second_half_p));

    // set p with f.get() from first and second half
    p.set_value(first_half_f.get() + second_half_f.get());
    
    t.join();
}
 
int main() {
    std::vector<int> v(10000, 1);

    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t(parallel_sum<std::vector<int>::iterator>, v.begin(), v.end(), std::move(p));
    assert(f.get() == 10000);
    t.join();
}