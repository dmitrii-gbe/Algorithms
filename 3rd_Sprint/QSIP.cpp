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
        result[i] = rand() % 1000;
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
    bool left_eq_pivot = false;
    bool right_eq_pivot = false;

    //auto start = left;
    //auto end = right;

    while (right > left){
            //PrintRange(start, end);
            left_less_pivot = comparator(*left, pivot);
            right_less_pivot = comparator(*right, pivot);
            left_eq_pivot = (*left == pivot);
            right_eq_pivot = (*right == pivot);

            if (!left_less_pivot && !left_eq_pivot && (right_less_pivot || right_eq_pivot)){ 
                std::swap(*left++, *right--);
                continue;
            }

            left += (left_less_pivot || left_eq_pivot);
            right -= (!right_less_pivot && !right_eq_pivot);
    }

    return comparator(*left, pivot) ? left + 1 : left;
}

template <typename It, typename Comparator>
void QuickSortInPlace(It first, It last, Comparator comparator){
    if (last - first < 2){
        return;
    }
    else {
        //typename std::iterator_traits<It>::value_type pivot = *(first + std::rand() % (last - first));
        typename std::iterator_traits<It>::value_type pivot = (*first + *(last - 1) + *(first + (last - first) / 2) ) / 3;
        It left = first;
        It right = last - 1;
        It border_right = GetBorder(left, right, pivot, comparator);
        It border_left = GetBorder(left, right, pivot - 1, comparator);
        QuickSortInPlace(first, border_left, comparator);
        QuickSortInPlace(border_right, last, comparator);
    }
}

/*


// template <typename It, typename Comparator>
// It GetBorder(It first, It last, Comparator comparator){
//     //PrintRange(first, last);
//     auto pivot = (*first + *(last - 1)) / 2;
//     // auto start = first;
//     // auto end = last;

//     // --last;

//     // while (first < last){
//     //     if (!comparator(*first, pivot) && comparator(*last, pivot)){
//     //         std::swap(*first++, *last--);
//     //         continue;
//     //     }
//     //     if (comparator(*first, pivot)){
//     //         ++first;
//     //     }
//     //     if (comparator(pivot, *last) || pivot == *last){
//     //         --last;
//     //     }
//     // }
//     // auto border = std::find_if(start, end, [&pivot](auto item){ return item > pivot; });
//     // return (border == end) ? end - 1 : border;


//     first = std::find_if_not(first, last, [pivot, comparator](auto item){ return comparator(item, pivot); });
//     if (first == last)
//         return first;
 
//     for (auto i = std::next(first); i != last; ++i)
//         if (comparator(*i, pivot)) {
//             std::iter_swap(i, first);
//             ++first;
//         }
 
//     return first;

// }

// template <typename It, typename Comparator>
// void QuickSortInPlace(It first, It last, Comparator comparator){
//     if (last - first < 2){
//         return;
//     }
//     else {
//         It border = GetBorder(first, last, comparator);
//         QuickSortInPlace(first, border, comparator);
//         QuickSortInPlace(border + 1, last, comparator);
//     }
// }
*/

int main(){

    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> input_data = GetRandomVector(10000000);
    std::shuffle(input_data.begin(), input_data.end(), g);
    std::vector<int> input_data1 = input_data;
    //std::vector<int> input_data = {5,4,2,7,9};
    //std::string input_data = "xfdkjbhzdilkfhjlzidkjh`vli`osualjdqIUEOKWFHJGAEH984UTHAGEIZNUNBJNNVJKZNJdzkjhnlkdfjxlghkfglmnb"s;
    //std::sort(input_data.begin(), input_data.end(), std::less<int>());
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
    return 0;
}