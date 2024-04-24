#include <iostream>


int main(){
    int max_count = 0;
    std::cin >> max_count;
    std::cout << max_count << '\n';
    bool is_first = true;
    for (int i = 1; i <= max_count; ++i){
        if (is_first){
            std::cout << i;
            is_first = false;
        }
        else {
            std::cout << " " << i;
        }
    }

    std::cout << '\n' << (max_count * max_count - max_count) / 2;


    return 0;
}