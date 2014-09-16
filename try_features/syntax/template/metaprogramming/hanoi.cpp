
#include <iostream>
using namespace std;

template<int N, char from, char mid, char to>
struct Hanoi{
    static void move(){
        Hanoi<N-1, from, to, mid>::move();
        cout << from << " --> " << to << '\n';
        Hanoi<N-1, mid, from, to>::move();
    }
};

template<char from, char mid, char to>
struct Hanoi<0, from, mid, to>{
    static void move(){}
};

int main(){
    Hanoi<4, 'A', 'B', 'C'>::move();
    return 0;
}

