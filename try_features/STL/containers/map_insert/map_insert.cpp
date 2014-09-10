/*
 * if the key is already in the map,
 * insertion will keep the old value.
 */

#include<map>
#include<iostream>
#include<string>
using namespace std;

int main(){
    map<int, string> m{
        {1, "orig str 1"},
        {2, "orig str 2"},
        {3, "orig str 3"}
    };

    m.insert({
        {3, "new str 3"},
        {4, "new str 4"},
        {5, "new str 5"}
    });

    for(const auto &x : m){
        cout << "(" << x.first << ", " << x.second << ")\n";
    }

    return 0;
}

