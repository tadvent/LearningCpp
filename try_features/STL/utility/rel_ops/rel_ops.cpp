// test std::rel_ops

#include<cstdlib>
#include<utility>
#include<iostream>
class tempclass{
    int i;
public:
    tempclass(int ii=0):i(ii){}
    int get(){return i;}
    bool operator<(const tempclass &x)const{return i<x.i;}
    bool operator==(const tempclass &x)const{return i==x.i;}
};

int main(){
    using namespace std::rel_ops;
    tempclass a(2),b(2);
    if(a>b)std::cout<<"a>b"<<std::endl;
    if(a>=b)std::cout<<"a>=b"<<std::endl;
    system("pause");
    return EXIT_SUCCESS;
}

