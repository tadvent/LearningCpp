#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <windows.h>

using namespace std;

class X{
    int phase;
    mutex m;
public:
    X(): phase(0){
        cout << "X init phase 1:" << endl;
        ::Sleep(1000);
        phase = 1;
        cout << "X init phase 2:" << endl;
        ::Sleep(3000);
        phase = 2;
        cout << "X init phase 3:" << endl;
        ::Sleep(100);
        phase = 3;
        cout << "X init finished." << endl;
        phase = 10;
    }
    ~X(){
        cout << "X deleted." << endl;
    }
    void print(int i, int mTimes){
        while (mTimes--){
            ::Sleep(rand() % 10);
            lock_guard<mutex> lk(m);
            cout << "phase: " << phase << " from thread " << i << endl;
        }
    }
};

X* getX(){
    static X x;
    return &x;
}

int main(){
    vector<thread> ths;
    for (int i = 0; i < 5; ++i){
        ths.emplace_back(&X::print, getX(), i, 5);
    }
    for (auto &t : ths){
        t.join();
    }
}

