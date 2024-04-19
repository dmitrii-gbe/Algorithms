#include <iostream> 
#include <vector> 
#include <algorithm>
#include <unordered_set>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> v){
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

std::vector<std::string> GetModifiedStrings(const std::string& s){
    using namespace std;
    std::vector<std::string> result;
    result.reserve(s.size() * 2);
    for (size_t i = 0; i < s.size(); ++i){
            std::string item = s;
            item.insert(i, "()"s);
            result.push_back(item);        
    }
    result.push_back(s + "()"s);
    std::unordered_set<std::string> result_set(result.begin(), result.end());
    return {result_set.begin(), result_set.end()};    
}

std::vector<std::string> ModifyVector(const std::vector<std::string> v){ 
    std::vector<std::string> result; 
    result.reserve(v.size() * 3); 

    for (const std::string& item : v){
        std::vector<std::string> tmp = GetModifiedStrings(item);
        result.insert(result.end(), tmp.begin(), tmp.end());
        result.push_back("(" + item + ")"); 
    }
    std::unordered_set<std::string> result_set(result.begin(), result.end());
    return {result_set.begin(), result_set.end()};  
} 

std::vector<std::string> GetParenteesesCombinations(int n){ 
    if (n == 0){ 
        return {}; 
    } 
    else if (n == 1){ 
        return std::vector<std::string> {"()"}; 
    } 
    else { 
        return ModifyVector(GetParenteesesCombinations(n - 1)); 
    }     
} 
 
int main(){ 
    int count = 0; 
   
    std::cin >> count; 
    std::vector<std::string> v = GetParenteesesCombinations(count); 
    std::sort(v.begin(), v.end()); 
     
    std::cout << v;
     
    return 0; 
}