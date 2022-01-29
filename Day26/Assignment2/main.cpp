#include <atomic>
#include <future>
#include <vector>
#include <iterator>
#include <cassert>

template<typename Iterator,typename MatchType>
bool parallel_find_impl(Iterator first, Iterator last, MatchType match, std::atomic<bool>& done) {
    try {
        unsigned long const length = std::distance(first, last);
        unsigned long const min_per_thread =25;
        if (length < (2*min_per_thread)) {
            for (;(first != last) && !done.load(); ++first) {
                if (*first == match) {
                    done = true;
                    return false;
                }
            }
            return true;
        } else {
            Iterator const mid_point = first+(length/2);
            std::future<bool> async_result = std::async(&parallel_find_impl<Iterator,MatchType>, 
                mid_point, last, match,std::ref(done));
            bool const direct_result = parallel_find_impl(first, mid_point, match, done);
            return direct_result?async_result.get():direct_result;
        }
    }
    catch(...) { done = true; throw; }
}

template<typename Iterator,typename MatchType>
bool parallel_none_of(Iterator first, Iterator last, MatchType match) {
    std::atomic<bool> done(false);
    return parallel_find_impl(first, last, match, done);
}

int main(void) {
    std::vector<std::string> myvec;
    for (int ii = 0; ii < 10000; ii++) {
        myvec.push_back("hello");
    }
    std::vector<std::string>::iterator iter = myvec.begin();
    iter += 5000;
    myvec.insert(iter, "world");
    
    auto found = parallel_none_of(myvec.begin(), myvec.end(), "world");
    assert(!found);

    found = parallel_none_of(myvec.begin(), myvec.end(), "foobar");
    assert(found);
}