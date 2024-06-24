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
    }

    for (auto& vertexes : list){
        std::sort(vertexes.begin(), vertexes.end());
    }

    return list;
}

void RecursiveDFS(const int current_vertex, const std::vector<std::vector<int>>& list, std::vector<Color>& color, std::vector<std::pair<int, int>>& entry_leave, int& time){
    ++time;
    entry_leave[current_vertex].first = time;
    color[current_vertex] = Color::GREY;
    for (int v : list[current_vertex]) {
        if (color[v] == Color::WHITE){
            RecursiveDFS(v, list, color, entry_leave, time);
        }
    }
    ++time;
    entry_leave[current_vertex].second = time;
    color[current_vertex] = Color::BLACK;
}

std::vector<std::pair<int, int>> MainDfs(const std::vector<std::vector<int>>& list, int vertex){
    std::vector<Color> color(list.size(), Color::WHITE);
    std::vector<std::pair<int, int>> entry_leave(list.size());
    int time = -1;
    RecursiveDFS(vertex, list, color, entry_leave, time);
    return entry_leave;
}

int main(){

    auto graph = GetAdjacencyList();

    int vertex = 1;

    auto entry_leave = MainDfs(graph, vertex - 1);

    for (const auto& pair : entry_leave){
        std::cout << pair.first << " " << pair.second << '\n';
    }

    return 0;
}