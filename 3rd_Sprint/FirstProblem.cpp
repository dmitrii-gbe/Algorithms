#include <iostream>
#include <string>
#include <string_view>


bool CheckName(std::string_view name){

    size_t size = name.size();
    if (size < 8){
        return false;
    }

    bool number = false;
    bool upper = false;
    bool lower = false;

    for (char c : name){
        if (c > 47 && c < 58){
            number = true;
        }
        if (c > 64 && c < 91){
            upper = true;
        }
        if (c > 96 && c < 123){
            lower = true;
        }
    }
    return number && upper && lower;
}

int main(){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string query;
    std::cin >> query;
    if (query.empty()){
        std::cout << "NO";
    }

    if (CheckName(query)){
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}