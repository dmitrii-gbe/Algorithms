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

std::vector<std::vector<int>> GetAdjacencyList(){
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
    }

    return std::move(list);
}

void RecursiveDFS(const int current_vertex, const std::vector<int>& vertexes, std::vector<int>& colors){
    colors[current_vertex] = 1; // Вершина посещена, но ещё не обработана.
    for (int w : vertexes) { // Получите список исходящих ребер в зависимости от способа хранения графа
        if (color[w] == "white") // Если вершина не посещена, то
            DFS(w); // запустим обход от найденной смежной вершины.
    }
    color[v] = "black"; // Теперь вершина обработана.
}

void MainDfs(const std::vector<std::vector<int>>& list){
    std::vector<int> colors(list.size());

    for (int vertex = 0; vertex < list.size(); ++vertex){
        if (colors[vertex] == 0){
            RecursiveDFS(vertex, list[vertex], colors[vertex]);
        }
    }
}

int main(){



   return 0;
}