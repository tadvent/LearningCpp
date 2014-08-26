#include <cstdlib>
#include <iostream>
using namespace std;

class B{
private:
    void fa() const {
        cout << "Base private function." << endl;
    }
protected:
    void fb() const {
        cout << "Base protected function." << endl;
    }
public:
    void fc() const {
        cout << "Base public function." << endl;
    }
};

class D1: public B {
public:
    using B::fb;    // making B::fb public
};

class D2: private B {
public:
    using B::fb;    // making B::fb public
    using B::fc;    // making B::fc public
};

int main(){
    D1 d1;
    d1.fb();

    D2 d2;
    d2.fb();
    d2.fc();

    system("pause");
}

