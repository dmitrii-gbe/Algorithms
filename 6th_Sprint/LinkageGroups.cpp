#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
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
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v){
    for (const auto& item : v){
        out << item;
    }
    return out;
}

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

void RecursiveDFS(const int current_vertex, const std::vector<std::vector<int>>& list, std::vector<int>& colors, int color){
    colors[current_vertex] = color; // Вершина посещена, но ещё не обработана.
    for (int v : list[current_vertex]) { // Получите список исходящих ребер в зависимости от способа хранения графа
        if (colors[v] == -1) // Если вершина не посещена, то
            RecursiveDFS(v, list, colors, color); // запустим обход от найденной смежной вершины.
    }
}

std::vector<int> MainDfs(const std::vector<std::vector<int>>& list){
    std::vector<int> colors(list.size(), -1);
    int color = 1;
    for (size_t vertex = 0; vertex < list.size(); ++vertex){
        if (colors[vertex] == -1){
            RecursiveDFS(vertex, list, colors, color);
            ++color;
        }

    }

    return colors;
}

int main(){

    auto graph = GetAdjacencyList();

    auto colors = MainDfs(graph);
    int x = *std::max_element(colors.begin(), colors.end());
    std::cout << x << '\n';
    std::vector<std::vector<int>> linkage_groups(x);

    for (size_t i = 0; i < colors.size(); ++i){
        linkage_groups[colors[i] - 1].push_back(i + 1);
    }

    std::cout << linkage_groups;

    return 0;
}