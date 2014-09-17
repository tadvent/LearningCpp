
#include<utility>
#include<tuple>
#include<iostream>
using namespace std;

class A{
    int n;
public:
    A(): n(0){
        cout << "A default ctor: " << n << '\n';
    }
    A(int N): n(N){
        cout << "A argument ctor: " << n << '\n';
    }
    A(const A& a): n(a.n + 1){
        cout << "A copy ctor: " << n << '\n';
    }
    A(A&& a): n(a.n){
        cout << "A move ctor: " << n
            << ". [" << a.n << " --> 0]\n";
        a.n = 0;
    }
    A& operator=(const A& a){
        cout << "A operator=: " << n;
        n = a.n + 1;
        cout << " --> " << n << '\n';
        return *this;
    }
    A& operator=(A&& a){
        cout << "A move =: " << n;
        n = a.n;
        cout << " --> " << n
           << ". [" << a.n << " --> 0]\n";
        a.n = 0;
        return *this;
    }
    ~A(){
        cout << "A dtor: " << n << '\n';
        n = 0;
    }
};

tuple<A, A, A> tupleA(){
    A a(20), b(21), c(22);
    return tuple<A, A, A>(move(a), move(b), move(c));
}

tuple<A, A, A> makeA(){
    A a, b(1), c(3);
    return make_tuple(move(a), move(b), move(c));
}

tuple<A, A, A> forwardA(){
    A a(5), b(6), c(7);
    return forward_as_tuple(move(a), move(b), move(c));
}

tuple<A, A, A> tieA(){
    A a(10), b(11), c(12);
    return tie(a, b, c);
}

int main(){
    tuple<A, A, A> t;

    cout << "\ntuple:\n";
    t = tupleA();

    cout << "\nmake_tuple:\n";
    t = makeA();

    cout << "\nforward_tuple:\n";
    t = forwardA();

    cout << "\ntie_tuple:\n";
    t = tieA();

    cout << "\nOver:\n";
    return 0;
}

