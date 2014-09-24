
#include<chrono>
#include<iostream>
using namespace std;
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    int n = 0;
    while(start == high_resolution_clock::now()) ++n;
    auto end = high_resolution_clock::now();

    auto d = duration_cast<microseconds>(end - start);

    cout << "Time epsilon: " << d.count() << " us.\n";
    cout << "cycle count: " << n << '\n';

    return 0;
}

