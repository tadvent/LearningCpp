// Global new

#include <iostream>
#include <cstdlib>
using namespace std;

class A{
public:
    A(){
        cout << "Normal Constructor." << endl;
    }
};

int main(){
    cout << "Global new" << endl;
    A* pa = (A*)::operator new(sizeof(A));
    cout << "Global new nothrow" << endl;
    A* pb = (A*)::operator new(sizeof(A), nothrow);
    cout << "Global placement new" << endl;
    pa = (A*)::operator new(sizeof(A), pa);
    cout << "normal placement new" << endl;
    pa = new(pa)A();
    system("pause");
}

