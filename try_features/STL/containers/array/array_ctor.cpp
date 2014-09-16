
#include <array>
#include <iostream>
using namespace std;

struct A{
    A(){
        cout << "A default ctor.\n";
    }
    ~A(){
        cout << "A default dtor.\n";
    }
};

int main(){
    cout << "No arguments:\n";
    array<A, 3> a;

    cout << "Initializer_list:\n";
    array<A, 3> b{};
}

