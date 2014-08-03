// when initialized with an array
// what is the element order in the stack?
// answer: 1, 2, 3 --> (bottom) 1, 2, 3 (top)
// output below: 6 5 4 3 2 1


#include <cstdlib>
#include <deque>
#include <stack>
#include <iostream>

using namespace std;

int main(){
    stack<int> s{deque<int>{1, 2, 3, 4, 5, 6}};
    while(!s.empty()){
        cout << s.top() << '\n';
        s.pop();
    }

    system("pause");
    return 0;
}

