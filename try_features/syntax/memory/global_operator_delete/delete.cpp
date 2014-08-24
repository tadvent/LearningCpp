#include <cstddef>
#include <iostream>
#include <cstdlib>
using namespace std;

inline void* operator new(size_t sz){
    void *p = malloc(sz);
    cout << "Alloc " << sz << " bytes at " << p << endl;
    return p;
}

inline void* operator new[](size_t sz){
    void *p = malloc(sz);
    cout << "Alloc " << sz << " bytes at " << p << endl;
    return p;
}

/* c++11 doesn't support size_t parameter in operator delete
void operator delete(void *p, size_t sz){
    free(p);
    cout << "Free " << sz << "bytes at " << p << endl;
}

void operator delete[](void *p, size_t sz){
    free(p);
    cout << "Free " << sz << "bytes at " << p << endl;
}
*/

void operator delete(void *p){
    free(p);
    cout << "Free at " << p << endl;
}

void operator delete[](void *p){
    free(p);
    cout << "Free at " << p << endl;
}

struct X{
    int a;
    char b[10];
};

int main(){
    X *pa = new X{};
    X *pb = new X[5];
    delete pa;
    delete [] pb;
}

