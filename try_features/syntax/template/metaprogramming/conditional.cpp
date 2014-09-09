
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

template <bool B, class T, class F>
using Cond = typename std::conditional<B,T,F>::type;

template <int X>
struct Func{
    /*
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
    */
    using FT = Cond<(X<1), Func1<X>,
          Cond<(X<10), Func2<X>, Func3<X>>>;
    static const int value = FT::value;
};

template<int X>
struct Out{
    void operator()() const {
        std::cout << "f(" << X << ") = " << \
            Func<X>::value << std::endl;
    }
};

int main(){
    Out<-1>{}();
    Out<0>{}();
    Out<1>{}();
    Out<5>{}();
    Out<10>{}();
    Out<20>{}();

    return 0;
}


