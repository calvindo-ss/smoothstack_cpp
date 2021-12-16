#include <iostream>

struct Foo{
    void myfunc(float f){
        std::cout << "I am non constant" << std::endl;
    }; 

    void myfunc(float f) const{
        std::cout << "I am constant" << std::endl;
    };
};

int main(){
    float num = 10.0;

    Foo bar;
    bar.myfunc(num);

    const Foo bar1;
    bar1.myfunc(num);
}