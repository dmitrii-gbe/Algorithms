#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

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
        list[to - 1].push_back(from - 1);
    }

    for (auto& vertexes : list){
        std::sort(vertexes.begin(), vertexes.end());
    }

    return list;
}

void RecursiveDFS(const int current_vertex, const std::vector<std::vector<int>>& list, std::vector<Color>& color){
    std::cout << current_vertex + 1 << " ";
    color[current_vertex] = Color::GREY;
    for (int v : list[current_vertex]) {
        if (color[v] == Color::WHITE){
            RecursiveDFS(v, list, color);
        }
    }
    color[current_vertex] = Color::BLACK;
}

void MainDfs(const std::vector<std::vector<int>>& list, int vertex){
    std::vector<Color> color(list.size(), Color::WHITE);
    RecursiveDFS(vertex, list, color);
}

int main(){

    auto graph = GetAdjacencyList();

    int vertex = 0;

    std::cin >> vertex;

    MainDfs(graph, vertex - 1);

    return 0;
}