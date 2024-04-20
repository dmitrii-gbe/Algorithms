#include <iostream>
#include <vector>
#include <algorithm>


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
std::vector<T> GetVector(){
    int size = 0;
    std::cin >> size;
    std::vector<T> result(size);

    for (int i = 0; i < size; ++i){
        std::cin >> result[i];
    }

    return result;
}

template <typename It>
void CountingSort(It begin, It end){
    if (begin == end){
        return;
    }
    int max = *std::max_element(begin, end);
    std::vector<typename std::iterator_traits<It>::value_type> tmp(max + 1);

    It it = begin;
    for (; it != end; ++it){
        ++tmp[*it];
    }

    std::vector<typename std::iterator_traits<It>::value_type> result;
    result.reserve(end - begin);
    for (size_t i = 0; i < tmp.size(); ++i){
        for (int j = 0; j < tmp[i]; ++j){
            result.push_back(i);
        }
    }

    std::copy(result.begin(), result.end(), begin);
}

int main(){

    std::vector<int> input = GetVector<int>();

    CountingSort(input.begin(), input.end());

    std::cout << input;

    return 0;
}