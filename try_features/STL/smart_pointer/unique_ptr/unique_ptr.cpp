// unique_ptr

#include <cstdlib>
#include <memory>
#include <iostream>
#include <vector>
#include <new>
using namespace std;

class A{
public:
    A(){
        cout << "A default ctor." << endl;
    }
    ~A(){
        cout << "A destroyed." << endl;
    }
};

#ifdef TEST1
void test(){
    unique_ptr<A> pa(new A());
    unique_ptr<A[]> pas(new A[3]);
    unique_ptr<int[]> p(new int[5]);
    p[0] = p[4] = 100;
    cout << p[0] << endl;
    //auto pa = new int[5];
    throw 1;
}
#endif

#ifdef TEST2
void test2(){
    void *buf = ::operator new(sizeof(A) * 5);
    A *p = new (buf) A[5];
    cout << buf << ' ' << p << endl;
    ::operator delete(buf);

    new (std::nothrow) A;
}
#endif

int main() try {
#ifdef TEST1
    test();
#endif
#ifdef TEST2
    test2();
#endif
    system("pause");
} catch (...) {
    cerr << "Catch error...\n";
    system("pause");
}

