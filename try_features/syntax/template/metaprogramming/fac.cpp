#include <iostream>
#include <type_traits>

template <int N>
struct FacPlus{
    const static int value = N * FacPlus<N-1>::value;
};
template <>
struct FacPlus<0>{
    const static int value = 1;
};

template <int N>
struct FacMinus{
    const static int value = N * FacMinus<N+1>::value;
};
template <>
struct FacMinus<0>{
    const static int value = 1;
};

template <int N>
struct Fac{
    using FacType =
        typename std::conditional<(N>=0), FacPlus<N>, FacMinus<N>>::type;
    const static int value = FacType::value;
};

int main(){
    std::cout << (Fac<8>::value) << std::endl;
    std::cout << (Fac<-5>::value) << std::endl;
}

