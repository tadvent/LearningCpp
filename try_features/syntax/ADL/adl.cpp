#include <vector>
#include <iostream>
#include <algorithm>

int main(){
    std::vector<int> v{5, 2, 8, 6, 9, 4};
    sort(v.begin(), v.end(), [](int x, int y) -> bool{
        return x > y;
    });
    for(const auto &x: v){
        std::cout << x << ' ';
    }
    std::cout << std::endl;
}

