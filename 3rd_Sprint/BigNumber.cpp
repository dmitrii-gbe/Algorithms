#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


std::vector<int> GetVector(){
    int size = 0;
    std::cin >> size;
    std::vector<int> result(size);

    for (int i = 0; i < size; ++i){
        std::cin >> result[i];
    }

    return result;
}

std::vector<std::string> ConvertVectorIntToVectorStr(const std::vector<int>& v){
    std::vector<std::string> result(v.size());
    for (size_t i = 0; i < v.size(); ++i){
        result[i] = std::to_string(v[i]);
    }
    return result;
}

void SortByFirstInt(std::vector<std::string>& v){
    std::sort(v.begin(), v.end(), [](const std::string& l, const std::string& r){ return std::stoi(l + r) > std::stoi(r + l); });
}

std::string StickStrings(const std::vector<std::string> v){
    std::string result;
    for (const std::string& s : v){
        result += s;
    }
    return result;
}

int main(){

    std::vector<std::string> v = ConvertVectorIntToVectorStr(GetVector());
    SortByFirstInt(v);

    std::cout << StickStrings(v);

    return 0;
}