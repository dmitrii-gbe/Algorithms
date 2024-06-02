#include <iostream>


size_t CalculateBSTNumber(int n){
    if (n == 0 || n == 1){
        return 1;
    }

    if (n == 2){
        return 2;
    }

    size_t result = 0;

    for (int i = 0; i < n; ++i){
        result += CalculateBSTNumber(i) * CalculateBSTNumber(n - i - 1);
    }

    return result;

}




int main(){

    // int i = 0;

    // std::cin >> i;

    for (int i = 0; i < 101; ++i){
        std::cout << "Node count: " << i << " BST count: " << CalculateBSTNumber(i) << std::endl;
    }

    //std::cout << CalculateBSTNumber(i);


    return 0;
}
