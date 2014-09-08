
#include <iostream>
#include <type_traits>

template <int N>
struct Rev{
    static const int last = N % 10;
    static const int forp = N / 10;
    static const int value = last * Rev<forp>::pow + Rev<forp>::value;
    static const int pow = 10 * Rev<forp>::pow;
};
template <>
struct Rev<0>{
    static const int pow = 1;
    static const int value = 0;
};

int main(){
    std::cout << Rev<12345>::value << std::endl;
    return 0;
}

