#include<cstdlib>
#include<iostream>
#include<vector>
#include<initializer_list>
#include<functional>

using namespace std;

int main(){
    auto summor = [](int init)mutable -> function<int(int)>{
        return [&init](int delta)->int{
            return init += delta;
        };
    };

    auto accu1 = summor(100);
    auto accu2 = summor(1000);

    cout << accu1(1) << ' ' << accu1(2) << ' ' << accu1(4) << endl;
    cout << accu2(1) << ' ' << accu2(2) << ' ' << accu2(4) << endl;
    system("pause");
}

