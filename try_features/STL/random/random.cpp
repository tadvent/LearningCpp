#include <cstdlib>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
using namespace std;


int main(){
    std::default_random_engine e;
    cout << "Default seed: " << e.default_seed << '\n';
    cout << "min and max: " << e.min() << ' ' << e.max() << '\n';
    generate_n(ostream_iterator<std::default_random_engine::result_type>(cout, "\n"),
        5, [&]()->decltype(e()){
            return e();
    });

    std::random_device rd("");
    cout << "\nrandom_device.entropy(): " << rd.entropy() << '\n';
    cout << "min and max: " << rd.min() << ' ' << rd.max() << '\n';
    generate_n(ostream_iterator<std::default_random_engine::result_type>(cout, "\n"),
        5, [&]()->decltype(rd()){
            return rd();
    });

    cout << "\ndistribution:\n";
    typedef std::uniform_int_distribution<int> dist;
    dist d;
    for(int i=0; i<5; ++i){
        cout << d(rd, dist::param_type(10, 15)) << '\n';
    }
}

