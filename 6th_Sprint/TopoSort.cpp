#include <iostream>
#include <vector>
#include <string>
#include <utility>
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

enum class Color {
    WHITE,
    GREY,
    BLACK
};

std::vector<std::vector<int>> GetAdjacencyList(){
    int vertexes, edges = 0;

    std::cin >> vertexes >> edges;

    std::vector<std::vector<int>> list(vertexes);

    for (int i = 0; i < edges; ++i){
        int from, to = 0;
        std::cin >> from >> to;
        list[from - 1].push_back(to - 1);
    }

    for (auto& vertexes : list){
        std::sort(vertexes.begin(), vertexes.end());
    }

    return list;
}

void RecursiveDFS(const int current_vertex, const std::vector<std::vector<int>>& list, std::vector<Color>& color, std::vector<int>& topo_order){
    color[current_vertex] = Color::GREY;
    for (int v : list[current_vertex]) {
        if (color[v] == Color::WHITE){
            RecursiveDFS(v, list, color, topo_order);
        }
    }
    topo_order.push_back(current_vertex + 1);
    color[current_vertex] = Color::BLACK;
}

std::vector<int> MainDfs(const std::vector<std::vector<int>>& list){
    std::vector<Color> color(list.size(), Color::WHITE);
    std::vector<int> topo_order;
    topo_order.reserve(list.size());
    for (size_t vertex = 0; vertex < list.size(); ++vertex){
        if (color[vertex] == Color::WHITE){
            RecursiveDFS(vertex, list, color, topo_order);
        }
    }

    return topo_order;
}

int main(){

    auto graph = GetAdjacencyList();

    auto topo_order = MainDfs(graph);

    std::cout << std::vector<int>{topo_order.rbegin(), topo_order.rend()};


    return 0;
}