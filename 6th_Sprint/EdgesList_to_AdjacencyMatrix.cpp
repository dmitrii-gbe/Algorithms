#include <iostream>
#include <vector>
#include <algorithm>


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
    out << '\n';
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>> v){
    for (const auto& item : v){
        out << item;
    }
    return out;
}

int main(){

    int vertexes, edges = 0;

    std::cin >> vertexes >> edges;
    std::vector<int> row(vertexes, 0);
    std::vector<std::vector<int>> matrix(vertexes, row);

    for (int i = 0; i < edges; ++i){
        int from, to = 0;
        std::cin >> from >> to;
        ++matrix[from - 1][to - 1];
    }

    std::cout << matrix;

   return 0;
}