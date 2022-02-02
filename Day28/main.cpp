#include <iostream>
#include <coroutine>
#include <memory>
#include <ctime>
#include <sstream>
#include <random>
#include <string>
#include <chrono>

enum myenum {credit, debit};

unsigned int random_char() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return dis(gen);
}

std::string generate_hex(const unsigned int len) {
    std::stringstream ss;
    for (auto i = 0; i < len; i++) {
        const auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << rc;
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
}

struct transaction{
   long post_date; // post date of transaction
   std::string src_accountId;  // use UUIDs
   std::string dest_accountId;  // use UUIDs
   myenum tranType; // transaction type enum can be credit or debit
   double amount; // in dollars ranging [1..1000000]

   transaction(){
        //post_date = std::time(nullptr);       // seconds are not precise enough
        // chrono allows precision in milliseconds
        post_date = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        src_accountId = generate_hex(4);
        dest_accountId = generate_hex(4);
        tranType = std::rand() % 2 == 0 ? myenum::credit : myenum::debit;
        amount = rand() % 1000001;
    }

    void print_data(){
        std::cout << "post_date: " << post_date;
        std:: cout << " src_accountId: " << src_accountId;
        std:: cout << " dest_accountId: " << dest_accountId;
        std:: cout << " tranType: " << tranType;        
        std::cout << " amount: " << amount << std::endl;
    }
};

template<typename T>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    Generator(handle_type h): coro(h) {
    }

    handle_type coro;
    
    ~Generator() {
        if ( coro ) coro.destroy();
    }

    Generator(const Generator&) = delete;
    
    Generator& operator = (const Generator&) = delete;
    
    Generator(Generator&& oth): coro(oth.coro) {
        oth.coro = nullptr;
    }
    
    Generator& operator = (Generator&& oth) {
        coro = oth.coro;
        oth.coro = nullptr;
        return *this;
    }
    
    transaction getNextValue() {
        coro.resume();
        return coro.promise().current_value;
    }
    
    struct promise_type {
        promise_type() {
        }                              
        
        ~promise_type() {
        }
        
        std::suspend_always initial_suspend() {  
            return {};
        }
        
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        
        auto get_return_object() {      
            return Generator{handle_type::from_promise(*this)};
        }
        
        // int value => transaction value
        std::suspend_always yield_value(transaction value) {    
            current_value = value;
            return {};
        }
        
        void return_void() {}
        
        void unhandled_exception() {
            std::exit(1);
        }
        
        T current_value;
    };
};

Generator<transaction> getNext() {
    auto value = transaction();
    while (true) {
        co_yield value;
        value = transaction();
    }
}

int main(void){
    auto gen = getNext();
    for (int i = 0; i <= 20; ++i) {
        auto val = gen.getNextValue();
        val.print_data();
    }
}