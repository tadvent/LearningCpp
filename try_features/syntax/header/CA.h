#pragma once
#include <iostream>

namespace{
class A{
    int _a, _b;
public:
    void print() const {
        std::cout << _a << ' ' << _b << std::endl;
    }
    void set(int a, int b){
        _a = a;
        _b = b;
    }
};
}

