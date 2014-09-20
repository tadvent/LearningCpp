
#include<regex>
#include<iostream>
#include<string>

using namespace std;

int main(){
    regex pat("[[:w:]]+");

    smatch ms;
    if(regex_search(string("abc_def_gho"), ms, pat)){
        cout << ms[0];
    }

    return 0;
}

