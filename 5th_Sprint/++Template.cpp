#include <iostream>
#include <cmath>
#include <vector>



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

int Rand7(){
    return rand() % 7 + 1;
}

size_t Rand10(){
    size_t multyplier1 = 1e9 + 7;
    size_t multyplier2 = 87178291198;
    return ((Rand7() * multyplier1 % 10) % 10 + (Rand7() * multyplier2 % 10) % 10) % 10 + 1;
}

int main(){


std::vector<int> count(11);

int counter = 100000000;

while (counter != 0){
    ++count[Rand7()];
    --counter;
    //std::cout << Rand10() << std::endl;
}

std::cout << count;

    return 0;
}