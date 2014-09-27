
#include<regex>
#include<iostream>
#include<string>

using namespace std;

int main(){
    regex pat("[[:w:]]+");

    cmatch ms;
    if(regex_search("abc_def_gho", ms, pat)){
        cout << ms[0];
    }

    return 0;
}

