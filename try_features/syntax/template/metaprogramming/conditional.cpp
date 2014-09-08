
#include <iostream>
#include <type_traits>

/*******************************
 * f(x) = x         (x < 1)
 * f(x) = 2x - 1    (1 <= x < 10)
 * f(x) = 3x - 11   (x >= 10)
********************************/

template <int X>
struct Func1{
    static const int value = X;
};
template <int X>
struct Func2{
    static const int value = 2*X - 1;
};
template <int X>
struct Func3{
    static const int value = 3*X - 11;
};

template <int X>
struct Func{
    using FT =
        typename std::conditional<
            (X < 1),
            Func1<X>,
            typename std::conditional<
                (X < 10),
                Func2<X>,
                Func3<X>
            >::type
        >::type;
    static const int value = FT::value;
};

#define OUT(x) std::cout << "f(" << (x) << ") = " << \
    Func<(x)>::value << std::endl

int main(){
    OUT(-1);
    OUT(0);
    OUT(1);
    OUT(5);
    OUT(10);
    OUT(20);

    return 0;
}


