// 数组引用作为参数

#include<cstdlib>
#include<iostream>
using namespace std;

template<class T, int N>
void fun(T (&r)[N]){
    for(int i = 0; i < N; ++i){
        cout << r[i] << ' ';
    }
}


int main(){
    char s[] = "(abc)";
    int a[] = {3, 3, 6, 4};
    fun(a);
    fun(s);

    system("pause");
}

