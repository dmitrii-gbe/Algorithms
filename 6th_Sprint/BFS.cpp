#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <deque>

enum class Colors {
    White,
    Grey,
    Black
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



void BFS(int start_vertex, const std::vector<std::vector<int>>& list){
    std::vector<Colors> colors(list.size(), Colors::White);
    std::deque<int> d;
    d.push_back(start_vertex);
    colors[start_vertex] = Colors::Grey;

    while (!d.empty()){

        for (int vertex : list[d.front()]){
            if (colors[vertex] == Colors::White){
                d.push_back(vertex);
                colors[vertex] = Colors::Grey;
            }
        }

        colors[d.front()] = Colors::Black;
        std::cout << d.front() + 1 << " ";
        d.pop_front();
    }

    colors[start_vertex] = Colors::Black;
}

int main(){

    auto graph = GetAdjacencyList();

    int start_vertex = 0;

    std::cin >> start_vertex;

    BFS(start_vertex - 1, graph);

    return 0;
}