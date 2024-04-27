#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <tuple>


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

std::vector<std::pair<int, int>> GetMaxUniv(const std::vector<int>& v){
    std::vector<std::pair<int, int>> tmp(*std::max_element(v.begin(), v.end()) + 1);
    for (auto it = v.begin(); it != v.end(); ++it){
        tmp[*it].first = *it;
        ++tmp[*it].second; 
    }

    std::sort(tmp.begin(), tmp.end(), [](std::pair<int, int> l, std::pair<int, int> r){ return std::tuple(-l.second, l.first) < std::tuple(-r.second, r.first); });
    auto it = std::find(tmp.begin(), tmp.end(), std::pair<int, int> {0, 0});
    tmp.erase(it, tmp.end());

    return tmp;
}

int main(){

    std::vector<int> v = GetVector<int>();

    int k = 0;

    std::cin >> k;

    auto vec = GetMaxUniv(v);

    bool is_first = true;
    for (auto it = vec.begin(); it < std::min(vec.begin() + k, vec.end()); ++it){
        if (is_first){
            std::cout << it->first;
            is_first = false;
        }
        else {
            std::cout << " " << it->first;
        }
    }

    return 0;
}