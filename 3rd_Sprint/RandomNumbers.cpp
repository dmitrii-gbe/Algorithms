#include <iostream>

int main(){

    int counter = 50;
    while (counter != 0) {
            std::cout << rand() % (10 + 1) << " ";
            --counter;
    }

}