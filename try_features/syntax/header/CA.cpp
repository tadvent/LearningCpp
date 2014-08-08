#include "CA.h"

void A::set(int a, int b){
    _a = a;
    _b = b;
}

void A::print() const {
    std::cout << _a << ' ' << _b << std::endl;
}

