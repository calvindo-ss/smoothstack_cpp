#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <cassert>
#include <math.h>
#include <cstdlib>

enum Currency {USD, GBP};
enum Choice {BUY, SELL};

struct Request{
    double exchangeRate;
    double amount;
    Currency currency;
    Choice choice;
};

class Country{
    private:
        double dollars;
        double pounds;
        std::mutex m;

        bool c_request(Country& other, const Request& request){
            std::lock_guard<std::mutex> lock(m);

            // Cancel this request if insufficient funds
            if(request.choice == BUY && request.currency == USD && pounds < request.amount / request.exchangeRate ||
            request.choice == BUY && request.currency == GBP && dollars < request.amount / request.exchangeRate ||
            request.choice == SELL && request.currency == USD && dollars < request.amount ||
            request.choice == SELL && request.currency == GBP && pounds < request.amount){
                return false;
            }

            // Cancel other request if insufficient funds
            else if(request.choice == BUY && request.currency == USD && other.dollars < request.amount||
            request.choice == BUY && request.currency == GBP && other.pounds < request.amount||
            request.choice == SELL && request.currency == USD && other.pounds < request.amount / request.exchangeRate ||
            request.choice == SELL && request.currency == GBP && other.dollars < request.amount / request.exchangeRate){
                return false;
            }
            
            else{
                return true;
            }
        }

    public:
        Country(): dollars(1000000), pounds(1000000){}

        void trade(Country& other, const Request& request){
            std::lock_guard<std::mutex> lock(m);

            if(c_request(other, request)){
                if(request.choice == BUY){
                    // buy USD for GBP; Add USD, subtract GBP to this. Vice versa to other
                    if(request.currency == USD){
                        dollars += request.amount;
                        pounds -= request.amount / request.exchangeRate;

                        other.dollars -= request.amount;
                        other.pounds += request.amount / request.exchangeRate;
                    }
                    // buy GBP for USD; Add GBP, subtract USD to this. Vice versa to other
                    else if(request.currency == GBP){
                        pounds += request.amount;
                        dollars -= request.amount / request.exchangeRate;

                        other.pounds -= request.amount;
                        other.dollars += request.amount / request.exchangeRate;
                    }
                }
                // SELL requested currency (subtract requested currency) to this, add to other
                else if(request.choice == SELL){
                    // sell USD for GBP; Subtract USD, add GBP to this. Vice versa to other
                    if(request.currency == USD){
                        dollars -= request.amount;
                        pounds += request.amount / request.exchangeRate;

                        other.dollars += request.amount;
                        other.pounds -= request.amount / request.exchangeRate;
                    }
                    // sell GBP for USD; Subtract GBP, add USD to this. Vice versa to other
                    else if(request.currency == GBP){
                        pounds -= request.amount;
                        dollars += request.amount / request.exchangeRate;

                        other.pounds += request.amount;
                        other.dollars -= request.amount / request.exchangeRate;
                    }
                }
            }

        }

        void print(){
            std::cout << "USD: " << std::setw(10) << std::fixed << dollars << std::endl;
            std::cout << "GBP: " << std::setw(10) << std::fixed << pounds << std::endl;
        }

        double get_dollars(){
            return dollars;
        }

        double get_pounds(){
            return pounds;
        }
};

void tests(){
    Request r1{1.36, 100000, USD, BUY};
    Request r2{1.36, 100000, USD, SELL};
    Request r3{0.74, 100000, GBP, BUY};
    Request r4{0.74, 100000, GBP, SELL};    

    Country c1;
    Country c2;

    c1.trade(c2, r1);
    assert(c1.get_dollars() == 1100000.000000);
    assert(c2.get_dollars() == 900000.000000);

    c1.trade(c2, r2);
    assert(c1.get_dollars() == 1000000.000000);
    assert(c2.get_dollars() == 1000000.000000);

    c1.trade(c2, r3);
    assert(c1.get_pounds() == 1100000.000000);
    assert(round(c2.get_pounds()) == 900000.000000); // have to round to do double comparison

    c1.trade(c2, r4);
    assert(c1.get_pounds() == 1000000.000000);
    assert(round(c2.get_pounds()) == 1000000.000000);
}

void c_trades(std::chrono::steady_clock::time_point begin, Country& c1, Country& c2, Request r1, Request r2, Request r3, Request r4){
    double time;
    while(time < 10){
        int c = (std::rand() % 4);
        switch(c){
            case 0:
                c1.trade(c2, r1);
                break;
            case 1:
                c1.trade(c2, r2);
                break;
            case 2:
                c1.trade(c2, r3);
                break;
            case 3:
                c1.trade(c2, r4);
                break;
        }

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double> (end - begin).count();
    }
}

int main(void){
    tests();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    
    Country c1;
    Country c2;

    Request r1{1.36, 100000, USD, BUY};
    Request r2{1.36, 100000, USD, SELL};
    Request r3{0.74, 100000, GBP, BUY};
    Request r4{0.74, 100000, GBP, SELL};    

    std::thread t1(c_trades, begin,std::ref(c1), std::ref(c2), r1, r2, r3, r4);
    std::thread t2(c_trades, begin, std::ref(c2), std::ref(c1), r1, r2, r3, r4);

    t1.join();
    t2.join();

    std::cout << "c1:" << std::endl;
    c1.print();

    std::cout << "c2:" << std::endl;
    c2.print();
}