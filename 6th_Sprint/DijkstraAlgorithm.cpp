#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <deque>
#include <limits>
#include <utility>
#include <queue>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& v){
    bool is_first = true;
    for (const auto& item : v){

        if (is_first){
            out << ((item == std::numeric_limits<int>::max()) ? -1 : item);
            is_first = false;
        }
        else {
            out << " " << ((item == std::numeric_limits<int>::max()) ? -1 : item);
        }
    }
    out << '\n';
    return out;
}

struct Edge {
    int vertex_ = 0;
    int weight_ = 0;

    Edge() = default;
    Edge(int v, int w) : vertex_(v), weight_(w){}
};

std::vector<std::vector<Edge>> GetAdjacencyList(){
    int vertexes, edges = 0;

    std::cin >> vertexes >> edges;


    std::vector<std::vector<Edge>> list(vertexes);

    for (int i = 0; i < edges; ++i){
        int from, to, weight = 0;
        std::cin >> from >> to >> weight;
        list[from - 1].emplace_back(to - 1, weight);
        list[to - 1].emplace_back(from - 1, weight);
    }

    return list;
}

template <typename T>
int GetNextVertex(T& queue, std::vector<bool>& visited){
    int current_vertex = -1;
    while (!queue.empty()){
        if (!visited[queue.top().first]){
            current_vertex = queue.top().first;
            queue.pop();
            visited[current_vertex] = true;
            break;
        }
        else {
            queue.pop();
        }
    }
    return current_vertex;
}


void Dijkstra(int start_vertex, std::vector<std::vector<Edge>>& list){
    std::vector<bool> visited(list.size(), false);

    std::vector<int> distances(list.size(), std::numeric_limits<int>::max());
    distances[start_vertex] = 0;

    std::vector<int> previous(list.size(), -1);

    auto comparator = [](const auto& lhs, const auto& rhs){ return lhs.second > rhs.second; };

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comparator)> queue;

    queue.push({start_vertex, 0});

    while (!queue.empty()){

        int current_vertex = GetNextVertex(queue, visited);

        if (current_vertex == -1){
            continue;
        }

        for (const Edge& edge : list[current_vertex]){
            int new_distance = distances[current_vertex] + edge.weight_;
            distances[edge.vertex_] = std::min(distances[edge.vertex_], new_distance);
            previous[edge.vertex_] = (new_distance > distances[edge.vertex_]) ? previous[edge.vertex_] : current_vertex;
            queue.push({edge.vertex_, distances[edge.vertex_]});
        }
    }

    std::cout << distances; 

}

void MainDijkstra(std::vector<std::vector<Edge>>& list){
    for (size_t start_vertex = 0; start_vertex < list.size(); ++start_vertex){
        Dijkstra(start_vertex, list);
    }
}

int main(){

    auto graph = GetAdjacencyList();

    MainDijkstra(graph);

    return 0;
}
