// infinite loop ?

#include <cstdio>

int main(){
    int i, b[12];
    printf("Address of i: %X\n", &i);
    printf("Address of b: %X\n", b);
    for(i = 0; i <= 12; ++i){
        // printf("%d\n", i);
        b[i] = 0;
    }
    return 0;
}

