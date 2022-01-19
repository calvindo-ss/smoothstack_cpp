#include <iostream>
#include <cassert>

class USD{
    public:
        double amount;
        USD(): amount(0){}
        USD(double amount): amount(amount){}
};

class EUR{
    public:
        double amount;
        EUR(): amount(0){}
        EUR(double amount): amount(amount){}
};

class CAD{
    public:
        double amount;
        CAD(): amount(0){}
        CAD(double amount): amount(amount){}
};

class YEN{
    public:
        double amount;
        YEN(): amount(0){}
        YEN(double amount): amount(amount){}
};

//  Convert only converts from EUR, CAD, and YEN to USD only!!
//  I probably need to add conversions to other currencies
class Convert{
    public:
        // converts to USD
        USD operator () (USD usd){
            return usd.amount;
        }
        USD operator () (EUR eur){
            return eur.amount * 1.15;
        }
        USD operator () (CAD cad){
            return cad.amount * 0.8;
        }
        USD operator () (YEN yen){
            return yen.amount * 0.0088;
        }

};

template <class T, class C>
class Account{
    private:
        T amt;
    public:
        Account() : amt(0){}
        Account(T amt) : amt(amt) {}

        // copy constructor
        Account(const Account &other){
            amt = other.amt;
        }
        
        // move constructor
        Account(Account&& other){
            amt = other.amt;
            other.amt = 0;
        }

        // copy assignment operator
        Account& operator=(const Account& other){
            if(this == &other){
                return *this;
            }

            amt = other.amt;

            return *this;
        }

        // move assignment operator
        Account& operator=(Account&& other){
            if(this == &other){
                return *this;
            }

            amt = other.amt;
            other.amt = 0;

            return *this;
        }

        template <typename X>
        bool is_same(T, X) const{
            if(typeid(T) == typeid(X)){
                return true;
            }
            else{
                return false;
            }
        }

        template <typename X>
        bool operator==(const Account<X, C> other) const{
            C c;
            if(is_same(amt, other.get_balance())){
                if(amt.amount == other.get_balance().amount){
                    return true;
                }
                else{
                    return false;
                }
            }
            // convert other currency to base currency
            else{
                if(amt.amount == c(other.get_balance()).amount){
                    return true;
                }
                else{
                    return false;
                }
            }
        }

        template <typename X>
        bool operator!=(const Account<X, C> other) const{
            C c;
            if(is_same(amt, other.get_balance())){
                if(amt.amount == other.get_balance().amount){
                    return false;
                }
                else{
                    return true;
                }
            }
            // convert other currency to base currency
            else{
                if(amt.amount == c(other.get_balance()).amount){
                    return false;
                }
                else{
                    return true;
                }
            }
        }

        template <typename X>
        bool operator<(const Account<X, C> other) const{
            C c;

            if(is_same(amt, other.get_balance())){
                return amt.amount < other.get_balance().amount;
            }
            else{
                return amt.amount < c(other.get_balance()).amount;
            }
        }

        template <typename X>
        bool operator>(const Account<X, C> other) const{
            C c;

            if(is_same(amt, other.get_balance())){
                return amt.amount > other.get_balance().amount;
            }
            else{
                return amt.amount > c(other.get_balance()).amount;
            }
        }

        template <typename X>
        T operator+(const X x){
            T t(amt.amount + x);
            return t;
        }

        template <typename X>
        T operator+=(const X x){
            T t(amt.amount += x);
            return t;
        }

        template <typename X>
        T operator-(const X x){
            T t(amt.amount - x);
            return t;
        }

        template <typename X>
        T operator-=(const X x){
            T t(amt.amount -= x);
            return t;
        }

        template <typename Q>
        T deposit(const Q q){
            C c;

            // add amt if same currency type
            if(typeid(q) == typeid(amt)){
                amt.amount += q.amount;
            }
            // convert currency type
            else{
                amt.amount += c(q).amount;
            }

            return amt;
        }

        template <typename Q>
        T withdraw(const Q q){
            C c;

            // subract amt if same currency type
            if(typeid(q) == typeid(amt)){
                amt.amount -= q.amount;
            }
            //convert currency type
            else{
                amt.amount -= c(q).amount;
            }
            
            return amt;
        }

        T get_balance() const{
            return amt;
        }

        template <typename Q>
        operator Account<Q, Convert>() const{
            C c;
            
            //if(is_same(Q, T)){        // this does not work, throws error saying Q does not refer to a value
            if(typeid(Q) == typeid(T)){
                Account<Q, Convert> account(amt.amount);
                return account;
            }
            else{
                Q q(c(amt));
                Account<Q, Convert> account(q);
                return account;
            }
        }

        template <typename R>
        Account <R, Convert>* currency(R r){
            if(typeid(R) == typeid(T)){
                R r(amt.amount);
                Account<R, Convert>* account = new Account<R, Convert>(r);
                return account;
            }
            else{
                C c;
                R r(c(r).amount);
                Account<R, Convert>* account = new Account<R, Convert>(r);
                return account;
            }
        }

};

int main(void){
    Account<USD, Convert> account(1);
    Account<EUR, Convert> account1(EUR(50.50));
    Account<CAD, Convert> account2;

    assert(account.get_balance().amount == 1);
    assert(account1.get_balance().amount == 50.50);
    assert(account2.get_balance().amount == 0);

    // test deposit
    account.deposit(USD(99));
    assert(account.get_balance().amount == 100);

    account.deposit(EUR(5));
    assert(account.get_balance().amount == 105.75);

    // test withdraw
    account.withdraw(EUR(5));
    assert(account.get_balance().amount == 100);
    
    account.withdraw(USD(99.50));
    assert(account.get_balance().amount == 0.50);

    // test operator==
    Account<USD, Convert> a(10);
    Account<USD, Convert> b(10);
    assert(a == b);

    Account<USD, Convert> c(USD(1));
    Account<CAD, Convert> d(CAD(1.25));
    assert(c == d);

    // test operator !=
    assert(a != c);
    assert(a != d);

    // test operator < and >
    assert(c < a);
    assert(b > d);

    // test operator +=
    a += 5;
    d += 10;
    assert(a.get_balance().amount == 15);
    assert(d.get_balance().amount == 11.25);

    // test cast operator
    Account<USD, Convert> e = d;
    assert(e == d);

    // test currency method
    Account<USD, Convert>* f = a.currency(USD());
    assert(*f == a);
}