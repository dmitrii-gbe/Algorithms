#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <deque>
#include <limits>
#include <list>

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

int GetNextVertex(const std::vector<int>& distances, const std::vector<bool>& visited){

	std::vector<std::pair<size_t, int>> v;
	v.reserve(distances.size());

	for (size_t i = 0; i < distances.size(); ++i){
		v.push_back({i, distances[i]});
	}

	std::sort(v.begin(), v.end(), [](const auto& lhs, const auto& rhs){return lhs.second < rhs.second; });

	for (const auto& vertex : v){
		if (!visited[vertex.first] && distances[vertex.first] != std::numeric_limits<int>::max()){
			return vertex.first;
		}
	}

    return -1;
}


void Dijkstra(int start_vertex, std::vector<std::vector<Edge>>& list){
    std::vector<bool> visited(list.size(), false);
	visited[start_vertex] = true;

    std::vector<int> distances(list.size(), std::numeric_limits<int>::max());
    distances[start_vertex] = 0;

    std::vector<int> previous(list.size(), -1);

    std::list<int> queue;
    queue.push_back(start_vertex);

    while (!queue.empty()){
        
        for (const Edge& edge : list[queue.front()]){
            int new_distance = distances[queue.front()] + edge.weight_;
            distances[edge.vertex_] = std::min(distances[edge.vertex_], new_distance);
            previous[edge.vertex_] = (new_distance > distances[edge.vertex_]) ? previous[edge.vertex_] : queue.front();
        }
        
        visited[queue.front()] = true;
    	queue.pop_front();
        int v = GetNextVertex(distances, visited);
        if (v != -1){
            queue.push_back(v);
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