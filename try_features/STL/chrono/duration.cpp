
#include<cstdlib>
#include<chrono>
#include<iostream>
#include<vector>
#include<iterator>
#include<functional>
#include<algorithm>
using namespace std;
using namespace std::chrono;

int main(){
    seconds s(5);
    microseconds us;
    us = s;
    cout << s.count() << " seconds\n";
    cout << us.count() << " microseconds\n";

    us = microseconds(123150);

    milliseconds ms;
    ms = duration_cast<milliseconds>(us);
    cout << ms.count() << " milliseconds\n";

    duration<double, milli> dms;
    dms = us;
    cout << dms.count() << " milliseconds\n";


    vector<int> v;
    auto start = steady_clock::now();
    generate_n(back_inserter(v), 100, rand);
    sort(v.begin(), v.end());
    for(int i=0; i<10000; ++i){
        generate(v.begin(), v.end(), rand);
        sort(v.begin(), v.end());
    }
    auto timeused = steady_clock::now() - start;
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));

    cout << "\nTime used: "
        << duration_cast<microseconds>(timeused).count()
        << " us.\n";

    return 0;
}

