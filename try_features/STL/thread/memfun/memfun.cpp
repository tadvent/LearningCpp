
#include <iterator>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <windows.h>

using namespace std;

struct TMark{
    int mark[100];
    int nextIdx;
    mutex nextMtx;
    TMark(){
        memset(mark, 0, sizeof(mark));
    }
    void f(int i){
        ::Sleep(1000);
        ++mark[i];
    }
    void tTask(){
        for (;;){
            int i;
            {
                lock_guard<mutex> guard(nextMtx);
                i = nextIdx;
                if (i >= 100) break;
                ++nextIdx;
            }
            f(i);
        }
    }
    void concurrentDo(int nThread){
        nextIdx = 0;
        vector<thread> ths;
        for (int i = 0; i < nThread; ++i){
            ths.emplace_back(&TMark::tTask, this);
        }
        for (thread &t : ths){
            t.join();
        }
    }
    void print(){
        for (const auto i : mark){
            cout << i;
        }
        cout << endl;
    }
};

int main(){
    TMark tm;
    using namespace std::chrono;
    using dsecs = duration < double, ratio<1,1> > ;
    
    cout.setf(ios::fixed);
    cout.precision(3);

    tm.print();
    auto tp = steady_clock::now();
    tm.concurrentDo(20);
    dsecs du = steady_clock::now() - tp;
    cout << "Time used: " << du.count() << " secs." << endl;
    tm.print();

    tp = steady_clock::now();
    tm.concurrentDo(5);
    du = steady_clock::now() - tp;
    cout << "Time used: " << du.count() << " secs." << endl;
    tm.print();
}

