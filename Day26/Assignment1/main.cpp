#include <future>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>

struct join_threads { 
    std::vector<std::thread>& myvec;
    join_threads(std::vector<std::thread>& vec) : myvec(vec) {}
    ~join_threads() {
        for (auto& ele : myvec) {
            ele.join();
        }
    }
};

template<typename Iterator, typename MatchType>
bool parallel_any_of(Iterator first, Iterator last, MatchType match) {
    struct find_element {
        void operator()(Iterator begin, Iterator end, MatchType match,
                        std::promise<bool>* result,     // change <iterator> to <bool>
                        std::atomic<bool>* done_flag) {
            try {
                for(;(begin != end) && !done_flag->load(); ++begin) {
                    if (*begin == match) {
                        result->set_value(true);    // if match is found, set result to true
                        done_flag->store(true);
                        return;
                    }
                }
            } catch(...) {
                try {
                    result->set_exception(std::current_exception());
                    done_flag->store(true);
                } catch(...) {}
            }
        }
    };

    unsigned long const length = std::distance(first, last);

    if(!length)
        return false;

    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size = length/num_threads;

    std::promise<bool> result;      // set <iterator> to <bool>
    std::atomic<bool> done_flag(false);
    std::vector<std::thread> threads(num_threads-1); 
    {
        join_threads joiner(threads);

        Iterator block_start=first;
        for (unsigned long i=0; i < (num_threads-1); ++i) {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            threads[i] = std::thread(find_element(), block_start, block_end, match, &result, &done_flag);
            block_start = block_end;
        }
        find_element()(block_start, last,match, &result, &done_flag);
    }
    if(!done_flag.load()) {
        return false; // return false if not found
    }
    return result.get_future().get();
}

int main(void) {
    std::vector<std::string> myvec;
    for (int ii = 0; ii < 10000; ii++) {
        myvec.push_back("hello");
    }
    std::vector<std::string>::iterator iter = myvec.begin();
    iter += 5000;

    myvec.insert(iter, "world");
    bool found1 = parallel_any_of(myvec.begin(), myvec.end(), "world");
    assert(found1 == true);

    bool found2 = parallel_any_of(myvec.begin(), myvec.end(), "foobar");
    assert(found2 == false);
}
