#include <iostream> 
#include <vector> 
#include <algorithm> 
#include "log_duration.h"
 
 
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
 
    std::string tmp1; 
    std::getline(std::cin, tmp1); 
    int size = std::stoi(tmp1); 
    std::vector<T> result; 
    result.reserve(size); 
 
    std::string query; 
    std::getline(std::cin, query); 
 
    std::string tmp; 
 
    for (char c : query){ 
        if (c != ' '){ 
            tmp += c; 
            continue; 
        } 
        if (c == ' ' && !tmp.empty()){ 
            result.push_back(std::stoi(tmp)); 
            tmp.clear(); 
        } 
    } 
    result.push_back(std::stoi(tmp)); 
 
    return result; 
} 
 
size_t GetNumberForGivenDif(const std::vector<int>& v, int dif){ 
    size_t result = 0;

    for (auto it = v.begin(); it != v.end(); ++it){ 
        int value = *it + dif; 
        auto start = it + 1; 
        auto l = std::upper_bound(start, v.end(), value); 
        result += l - start;
    } 
    
    return result; 
}
 
int GetKDif(const std::vector<int>& v, size_t index){ 

    int max_dif = v.back() - v.front();
  
    std::vector<int> differences;
    differences.reserve(max_dif + 1);

    for (int i = 0; i <= max_dif; ++i){ 
        differences.push_back(i);  
    }

    return *std::lower_bound(differences.begin(), differences.end(), index, [&v](int i, size_t j){ return GetNumberForGivenDif(v, i) < j; }); 
}
 
 
int main(){ 
 
    std::vector<int> v = GetVector<int>();
    std::sort(v.begin(), v.end());

    size_t index = 0; 
    std::cin >> index;

    std::cout << GetKDif(v, index) << '\n';
 
    return 0; 
}