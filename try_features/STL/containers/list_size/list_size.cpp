/*
 * It is still linear complexity with list::size() in gcc 4.8.1
 */

#include <vector>
#include <list>
#include <ctime>
#include <string>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <iostream>
using namespace std;

template<class Func>
double timeit(Func &&f, int n){
    clock_t start = clock();
    while(n--){
        f();
    }
    return static_cast<double>(clock() - start)/CLOCKS_PER_SEC;
}

template<class Func>
void timeit(const string &s, Func &&f, int n = 1){
    cout << s << timeit(f, n) << " secs\n";
}

int main(){
    srand(time(NULL));
    list<int> l;
    vector<int> v;
    for(int i = 0; i < 100000; ++i){
        l.push_back(i);
        v.push_back(i);
    }

    timeit("list.size(): ", [&l](){
        int n = 0;
        for(int i = 0; i < 10000; ++i){
            n += l.size();
        }
        cout << "\nn = " << n << '\n';
    }, 1);
    
    timeit("vector.size(): ", [&v](){
        int n = 0;
        for(int i = 0; i < 10000; ++i){
            n += v.size();
        }
        cout << "\nn = " << n << '\n';
    }, 1);

    return 0;
}

