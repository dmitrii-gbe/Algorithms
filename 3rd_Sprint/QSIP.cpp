#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include "log_duration.h"
#include <cstdlib>
#include <random>
#include <cassert>
#include <iterator>

using namespace std::string_literals;

inline size_t GetRandomIndex(size_t upper_limit){
    return std::rand() % (upper_limit + 1);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    bool is_first = true;
    for (const auto& item : v){
        if (is_first){
            out << item;
            is_first = false;
        }
        else {
            out << '\n' << item;
        }
    }
    return out;
}

std::vector<int> GetRandomVector(size_t size){
    std::vector<int> result(size);
    for (size_t i = 0; i < size; ++i){
        result[i] = rand() % 10;
    }
    return result;
}

template <typename It>
void PrintRange(It start, It end){
    std::cout << "{ ";
    while (start <= end){
        std::cout << *start++ << ' ';
    }
    std::cout << "}" << std::endl;
}


template <typename It, typename Comparator>
inline It GetBorder(It left, It right, typename std::iterator_traits<It>::value_type pivot, Comparator comparator){

    bool left_less_pivot = false;
    bool right_less_pivot = false;
    --right;
    // auto start = left;
    // auto end = right;
    //PrintRange(start, end);
    while (right > left){
        
        left_less_pivot = comparator(*left, pivot);
        right_less_pivot = comparator(*right, pivot);

        if (!left_less_pivot && right_less_pivot){ 
            std::iter_swap(left++, right--);
        }
        else {
            left += (left_less_pivot);
            right -= (!right_less_pivot);
        }
    }
    //PrintRange(start, end);
    return comparator(*left, pivot) ? left + 1 : left;
}

template <typename It, typename Comparator>
void QuickSortInPlace(It first, It last, Comparator comparator){
    if (last - first < 2){
        return;
    }
    else {
        typename std::iterator_traits<It>::value_type pivot = (*first + *(last - 1)) / 2;
        It border_left = GetBorder(first, last, pivot, comparator);
        It border_right = GetBorder(border_left, last, pivot, [comparator](const auto& lhs, const auto& rhs){ return !comparator(rhs, lhs); });
        QuickSortInPlace(first, border_left, comparator);
        QuickSortInPlace(border_right, last, comparator);
    }
}

int main(int argc, char** argv){
    if (argc > 1){
        std::random_device rd;
        std::mt19937 g(rd());
        std::vector<int> input_data = GetRandomVector(std::atoi(argv[1]));
        std::shuffle(input_data.begin(), input_data.end(), g);
        std::vector<int> input_data1 = input_data;

        {
            LOG_DURATION_STREAM("Mine", std::cout);
            QuickSortInPlace(input_data.begin(), input_data.end(), std::less<int>());
        }

        {
            LOG_DURATION_STREAM("STL", std::cout);
            std::sort(input_data1.begin(), input_data1.end(), std::less<int>());
        }

        assert(input_data == input_data1);
        //std::cout << input_data << std::endl;

    } 
    else {
       std::cout << "At least one parameter should be specified"s << std::endl;
   }
    return 0;
}