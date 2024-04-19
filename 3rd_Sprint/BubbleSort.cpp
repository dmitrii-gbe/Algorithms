#include <iostream>
#include <vector>


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> v){
    bool is_first = true;
    for (const auto& item : v){

        if (is_first){
            out << item;
            is_first = false;
        }
        else {
            out << " " << item;
        }
    }
    out << '\n';
    return out;
}

template <typename T>
void BubbleSort(std::vector<T>& v){
    int counter = 0;
    int counter_internal = 0;
    for (size_t i = 1; i < v.size(); ++i){
        for (size_t j = 1; j < v.size(); ++j){
            if (v[j] < v[j - 1]){
                std::swap(v[j], v[j - 1]);
                ++counter;
                ++counter_internal;
            }
        }
        if (counter == 0){ 
            break;
        }
        else {
            std::cout << v;
            counter = 0;
        }
    }
    if (counter_internal == 0){
        std::cout << v;
    }
}

int main(){

    int size = 0;
    std::cin >> size;
    std::vector<int> storage(size);

    for (int i = 0; i < size; ++i){
        std::cin >> storage[i];
    }

    BubbleSort(storage);

    return 0;
}