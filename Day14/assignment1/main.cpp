#include <string>
#include <type_traits>
#include <cassert>

struct A {
    std::string str[2]; // member has a non-trivial throwable copy ctor
};

struct B {
    int n;
    B(const B&) = default; // trivial and non-throwing
};

class C {
    C(const C&) = delete;
};

class D {
    D(D&&) = default;
};

class E {
    E(E&&) = delete;
};

int main() {
    assert(std::is_copy_assignable<A>::value);
    assert(std::is_copy_assignable<B>::value);
    assert(std::is_copy_assignable<C>::value);
    assert(!std::is_copy_assignable<D>::value);
    assert(!std::is_copy_assignable<E>::value);
}