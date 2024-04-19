#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <array>

// #include <utility>
// #include <chrono>
// #include "log_duration"
// #include <unordered_map>
// #include <unordered_set>
// #include <map>
// #include <set>
// #include <algorithm>


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> v){
    bool is_first = true;
    out << "[ ";
    for (const auto& item : v){

        if (is_first){
            out << item;
            is_first = false;
        }
        else {
            out << " " << item;
        }
    }
    out << " ]" << '\n';
    return out;
}

template <typename T>
std::vector<T> GetVector(){
    int size = 0;
    std::cin >> size;
    std::vector<T> result(size);

    for (int i = 0; i < size; ++i){
        std::cin >> result[i];
    }

    return result;
}

int main(){

int max_size = 10;

for (int i = 0; i < max_size; ++i){
    std::cout << i << " " << ((i - 1) + max_size) % max_size << '\n';
}


    return 0;
}