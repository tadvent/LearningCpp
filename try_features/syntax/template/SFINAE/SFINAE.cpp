#include <vector>
#include <iostream>

template<class Iter>
typename Iter::value_type mean(Iter first, Iter last){
    typename Iter::value_type s = 0;
    int n = 0;
    while(first != last){
        s += *first;
        ++first;
        ++n;
    }
    return s/n;
}

template<class T>
T mean(T *beg, T* end){
    T s = 0;
    int n = 0;
    while(beg != end){
        s += *beg;
        ++beg;
        ++n;
    }
    return s/n;
}

int main(){
    int p[] = {2, 4, 6, 8, 10, 24};
    int n = 6;
    std::vector<int> v(p, p+n);

    auto x = mean(v.begin(), v.end());
    auto y = mean(p, p+n);

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    return 0;
}


