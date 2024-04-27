//https://contest.yandex.ru/contest/23815/run-report/113024345/
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <tuple>
#include <random>
#include <cassert>

size_t GetRandomIndex(size_t upper_limit){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, upper_limit);
    return distrib(gen);
}

std::vector<int> GenerateRandomVector(int count){
    std::vector<int> result(count);

    int max_value = count;

    while (count >= 0){
        result[count] = static_cast<int>(GetRandomIndex(max_value));
        --count;
    }

    return result;
}

struct Participant {
    Participant(const std::string& login, const int64_t points, const int64_t penalty) : login_(login)
                                                                           , points_(points)  
                                                                           , penalty_(penalty)
                                                                             {}
    
    std::string login_;
    int64_t points_ = 0;
    int64_t penalty_ = 0;

    bool operator==(const Participant& other) const {
        return login_ == other.login_ && points_ == other.points_ && penalty_ == other.penalty_;
    }
    bool operator!=(const Participant& other) const {
        return !(*this == other);
    }
};

std::ostream& operator<<(std::ostream& out, const Participant& item){
    out << item.login_;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    out << "[ ";
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
    out << "]" << '\n';
    return out;
}

std::vector<Participant> GetInputData(){ 
    size_t count = 0;
    std::cin >> count;
    std::vector<Participant> result;
    result.reserve(count);

    while (count > 0){
        std::string login;
        int64_t points, penalty;
        std::cin >> login >> points >> penalty;
        Participant item = {login, points, penalty};
        result.push_back(item);
        --count;
    }

    return result;
}

template <typename It>
void PrintRange(It first, It last){
    std::cout << "[ ";
    bool is_first = true;
    for (auto it = first; it != last + 1; ++it){
        if (is_first){
            std::cout << *it;
            is_first = false;
        }
        else {
            std::cout << " " << *it;
        }
    }
    std::cout << " ]" << '\n';
}

template <typename It>
void PrintRange1(It first, It last){
    std::cout << "[ ";
    bool is_first = true;
    for (auto it = first; it != last; ++it){
        if (is_first){
            std::cout << *it;
            is_first = false;
        }
        else {
            std::cout << " " << *it;
        }
    }
    std::cout << " ]" << '\n';
}

template <typename It>
void QuickSortInPlace(It first, It last){
   // std::cout << "Invoke: " << '\n';
   // PrintRange1(first, last);
    if (last - first < 2){
        //std::cout << "Small range:" << '\n';
       // PrintRange(first, last);
        return;
    }
    else {
       // std::cout << "Large range:" << '\n';
        typename std::iterator_traits<It>::value_type pivot = *(first + GetRandomIndex(last - first - 1));
        It left = first;
        It right = std::prev(last);
       // PrintRange(left, right);
        while (right > left){
           // std::cout << "Left: " << *left << " Pivot: " << pivot << " Right: " << *right << '\n';
            if (*left > pivot && *right <= pivot){
                std::swap(*left, *right);
                ++left;
                --right;
                continue;
            }
            if (*left <= pivot){
                ++left;
            }
            if (*right > pivot){
                --right;
            }
        }
        //PrintRange(first, last);
        //auto border = std::min(left, right);
        QuickSortInPlace(first, (*right < pivot) ? right + 1 : right);
        QuickSortInPlace(right, last);
    }
}

int main(){

    size_t max_count = 187768;

    auto input_data = GenerateRandomVector(max_count);
   // std::cout << input_data;

    auto copy = input_data;

    QuickSortInPlace(input_data.begin(), input_data.end());
    std::sort(copy.begin(), copy.end());

    assert(copy == input_data);

    //std::cout << input_data;
    return 0;
}