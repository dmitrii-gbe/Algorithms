#include <iostream>
#include <vector>
#include <algorithm>


int Fibbonnacchi(int n){

    if (n < 2){
        return 1;
    }

    int base = 1e9 + 7;

    int first = 1;
    int second = 1;

    while (n - 1 > 0){
        int buf = second;
        second = (first + second) % base;
        first = buf;
        --n;
    }

    return second;
}

int main(){

    int n = 0;

    std::cin >> n;

    std::cout << Fibbonnacchi(n);

    return 0;
}