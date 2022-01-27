#include <vector>
#include <thread>
#include <numeric>
#include <iostream>
#include <future>
#include <cassert>

template<typename Iterator,typename T> 
struct accumulate_block {
        void operator()(Iterator first, Iterator last, std::promise<T>& p) {
            //result = std::accumulate(first,last,result);
            T result = std::accumulate(first, last, 0);     // set result to 0
            p.set_value(result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
    unsigned long const length=std::distance(first, last);
    if (!length){
        return init;
    }
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();
    unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    std::cout << "num_threads: " << num_threads << std::endl;

    unsigned long const block_size = length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);
    Iterator block_start = first;

    // create promise and future vector for threads
    std::vector<std::promise<T>> p(num_threads);
    std::vector<std::future<T>> f(num_threads);

    // f = p.get_future(); for each thread
    for(int i = 0; i < num_threads; i++){
        f[i] = p[i].get_future();
    }

    for (unsigned long i = 0; i < (num_threads-1); ++i) {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        threads[i] = std::thread(accumulate_block<Iterator,T>(), block_start, block_end, std::ref(p[i]));   // set 3rd parameter to ref(p)
        block_start = block_end;
    }
    accumulate_block<Iterator,T>() (block_start, last, p[num_threads-1]);

    // iterate through futures to get() results
    for(int j = 0; j < num_threads; j++){
        results[j] = f[j].get();
    }

    for (auto& entry: threads){
        entry.join();
    }

    return std::accumulate(results.begin(), results.end(), init);
}

int main(void) {
    constexpr long LEN = 20000;
    std::vector<long> myvec;
    for (long ii = 0; ii < LEN; ii++) {
        myvec.push_back(ii);
    }
    long sum = parallel_accumulate(myvec.begin(), myvec.end(), long(0));
    std::cout << "sum: " << sum << std::endl;
    assert(sum == 199990000);
}