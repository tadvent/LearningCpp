#include <vector>
#include <iostream>
#include <algorithm>

int main(){
    std::vector<int> v{5, 2, 8, 6, 9, 4};
    sort(v.begin(), v.end());   // OK !
    for(const auto x: v){
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    int a[] = {5, 3, 7, 9, 2};
    // sort(a, a+sizeof(a)/sizeof(a[0]));   // Error !
    for(const auto x: a){
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    return 0;
}

