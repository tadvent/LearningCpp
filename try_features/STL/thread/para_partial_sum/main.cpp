#include <future>
#include <thread>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

class Thread_Joiner{
    vector<thread> &_ths;
public:
    Thread_Joiner(vector<thread> &ths) : _ths(ths){}
    ~Thread_Joiner(){
        for (auto &t : _ths)
            t.join();
    }
};

template<class IterT>
void para_partial_sum(IterT beg, IterT end){
    auto len = distance(beg, end);
    if (len == 0) return;

    using ValT = typename iterator_traits<IterT>::value_type;
    auto sum_task = [](future<ValT> &init, IterT b, IterT e, promise<ValT> &s){
        std::partial_sum(b, e, b);
        ValT prev_sum = init.get();
        s.set_value(prev_sum + *(prev(e, 1)));
        for_each(b, e, [&](ValT &v){
            v += prev_sum;
        });
    };
    const int elem_per_task = max<int>(25, len / thread::hardware_concurrency());
    const int nTask = len / elem_per_task;

    vector<thread> threads;
    Thread_Joiner tj(threads);
    vector<promise<ValT> > pros(nTask + 1);
    vector<future<ValT> > futs;
    for (auto &p : pros){
        futs.emplace_back(p.get_future());
    }

    pros[0].set_value(ValT{});
    IterT taskBeg = beg;
    for (int i = 0; i < nTask; ++i){
        IterT taskEnd = next(taskBeg, elem_per_task);
        threads.emplace_back(sum_task, ref(futs[i]), taskBeg, taskEnd, ref(pros[i+1]));
        taskBeg = taskEnd;
    }
    
    ValT prev_sum = futs.back().get();
    for (IterT it = taskBeg; it != end; ++it){
        *it += prev_sum;
        prev_sum = *it;
    }
}

void testcase(int len){
    vector<int> input(len);
    default_random_engine e;
    uniform_int_distribution<int> intrand(0, 10);
    generate(input.begin(), input.end(), bind(intrand, e));

    vector<int> stdans(len);
    auto start = chrono::steady_clock::now();
    partial_sum(input.begin(), input.end(), stdans.begin());
    auto stdused = chrono::steady_clock::now() - start;

    start = chrono::steady_clock::now();
    para_partial_sum(input.begin(), input.end());
    auto paraused = chrono::steady_clock::now() - start;

    if (equal(input.begin(), input.end(), stdans.begin())){
        cout << "Test pass.\n";
        cout << "STL time used: " << chrono::duration_cast<chrono::milliseconds>(stdused).count() << " msecs\n";
        cout << "para time used: " << chrono::duration_cast<chrono::milliseconds>(paraused).count() << " msecs\n";
    }
    else{
        cerr << "Test ERROR!\n";
    }
}

int main(){
    testcase(100000000);
}

