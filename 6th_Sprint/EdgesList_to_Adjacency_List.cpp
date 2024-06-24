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



int main(){

    int vertexes, edges = 0;

    std::cin >> vertexes >> edges;

    std::vector<std::vector<int>> list(vertexes);

    for (int i = 0; i < edges; ++i){
        int from, to = 0;
        std::cin >> from >> to;
        list[from - 1].push_back(to);
    }

    for (auto& vertexes : list){
        std::sort(vertexes.begin(), vertexes.end());
        std::cout << vertexes.size() << " " << vertexes;
    }

   return 0;
}