#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

const std::vector<std::string> v = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

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
    return out;
}

std::vector<std::string> ModifyStrings(const std::vector<std::string>& vec, int i){
    std::vector<std::string> result;
    if (std::all_of(vec.begin(), vec.end(), [](const std::string s){ return s.empty(); })){
        for (char c : v[i]){
            result.push_back(std::string{c});
        }
    }
    else {
        for (std::string s : vec){
            for (char c : v[i]){
                result.push_back(s + c);
            }
        }
    }
    return result;
}

std::vector<std::string> GenerateCombination(const std::vector<int>& vec){
    if (vec.size() == 1){
        return ModifyStrings(std::vector<std::string>{v[vec[0]].size(), ""}, vec[0]);
    }
    else {
        return ModifyStrings(GenerateCombination({vec.begin(), std::prev(vec.end())}), *std::prev(vec.end()));
    }
}



int main(){

std::string query;
std::getline(std::cin, query);
std::vector<int> query_v;
for (size_t i = 0; i < query.size(); ++i){
    query_v.push_back(query[i] - '0');
}

std::vector<std::string> result = GenerateCombination(query_v);
std::sort(result.begin(), result.end());
std::cout << result;


    return 0;
}