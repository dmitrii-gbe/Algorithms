#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <array>
#include <utility>
#include <chrono>
//#include "log_duration"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <ctime>


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

int main(){



    return 0;
}