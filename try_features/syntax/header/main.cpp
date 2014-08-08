
#include <cstdlib>
#include "CA.h"

extern A b;

int main(){
    A o;
    o.set(3, 5);
    o.print();

    b.set(4, 6);
    b.print();

    system("pause");
}

