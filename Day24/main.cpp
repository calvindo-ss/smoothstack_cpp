#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <iostream>

template<typename T>
class threadsafe_queue {
    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
    public:
    threadsafe_queue() {}

    threadsafe_queue(threadsafe_queue const& other) {
        std::lock_guard<std::mutex> lk(other.mut);
        data_queue = other.data_queue;
    }

    void push(T new_value, int id) {
        std::lock_guard<std::mutex> lk(mut);
        std::cout << "id: " << id << " pushing: " << new_value << std::endl;
        data_queue.push(new_value);
        data_cond.notify_one();
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] {return !data_queue.empty();});
        value = data_queue.front();
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] {return !data_queue.empty();});
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value, int id) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()){
            return false;
        }
        value = data_queue.front();
        std::cout << "id: " << id << " popping: " << value << std::endl;
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop(int id) {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty()){
           return std::shared_ptr<T>();
        }
        std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
        std::cout << "id: " << id << " popping: " << *res << std::endl;
        data_queue.pop();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};

void do_something(threadsafe_queue<int>& tsq, const int& id){
    tsq.push(0, id);
    tsq.push(1, id);

    int test;

    tsq.try_pop(test, id);

    std::shared_ptr<int> res = tsq.try_pop(id);
}

int main(void){
    threadsafe_queue<int> tsq;

    std::thread t1(do_something, std::ref(tsq), 0);
    std::thread t2(do_something, std::ref(tsq), 1);

    t1.join();
    t2.join();
}