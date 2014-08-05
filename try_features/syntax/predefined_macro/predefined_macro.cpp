//* exception auto report

#include<cstdlib>
#include<iostream>
using namespace std;

class ExceptReport{
public:
    ExceptReport(const char filename[], int linenum){
        cerr << "ExceptOccur:\n\tFile: " << filename;
        cerr << "\n\tLine: " << linenum << '\n';
    }
};

#define ERROR() ExceptReport(__FILE__, __LINE__)

int main() try {
    throw ERROR();
}
catch(...){
    system("pause");
}



