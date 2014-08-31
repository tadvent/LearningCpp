
#include <iostream>
#include <memory>
using namespace std;

class VB{
protected:
    int i;
public:
    VB(int ii): i(ii){
        cout << "VB init to " << ii << endl;
    }
    virtual ~VB(){
        cout << "Delete in VB." << endl;
    }
    virtual void f() = 0;
};

class D1: virtual public VB{
public:
    D1(int ii): VB(ii){
        cout << "D1 init to " << ii << endl;
    }
    void f() override{
        cout << "In class D1: i is " << i << endl;
    }
    ~D1(){
        cout << "Delete in D1." << endl;
    }
};

class D2: virtual public VB{
public:
    D2(int ii): VB(ii){
        cout << "D2 init to " << ii << endl;
    }
    void f() override{
        cout << "In class D2: i is " << i << endl;
    }
    ~D2(){
        cout << "Delete in D2." << endl;
    }
};

class D: public D1, public D2{
public:
    // VB should be init in D's ctor,
    // or there would be a compile error:
    D(int ii): D1(11), D2(12), VB(ii){
        cout << "D init to " << ii << endl;
    }
    void f() override{
        cout << "In class D: i is " << i << endl;
    }
    ~D(){
        cout << "Delete in D." << endl;
    }
};

void f(VB *pb){
    pb->f();
}

int main(){
    unique_ptr<VB> pd1(new D1(1));
    f(pd1.get());

    unique_ptr<VB> pd2(new D2(2));
    f(pd2.get());

    unique_ptr<VB> pd(new D(3));
    f(pd.get());

    cout.put('\n');

    return 0;
}


