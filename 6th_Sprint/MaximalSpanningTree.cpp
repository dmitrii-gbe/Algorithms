//https://contest.yandex.ru/contest/25070/run-report/115487911/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает входные данные с помощью функции GetAdjacencyList(), которая возвращает список смежности графа.
Условие задачи предполагает, что, если в дереве несколько компонент связности, то максимальное остовное дерево искать не нужно.
Поэтому сначала решение подсчитывает компоненты связности с помощью функции CheckForConnectivity. Если компонента связности одна,
суммарный вес максимального остовного дерева вычисляется с помощью функции GetMaxSpanningTreeWeight(). Она реализует алгоритм
Прима на очереди с приоритетом с тем отличием, что на каждой итерации выбирается ребро, исходящее из множества уже добавленных
вершин и обладающее максимальным весом.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Рассмотрим момент времени, когда алгоритм построил поддерево, являющееся частью максимального остовного дерева данного графа, и среди всех исходящих
ребер есть ребро x->y максимального веса. Допустим, что искомое максимальное дерево его не включает. Но тогда получается, что в рассматриваемый 
момент времени ребро, соединившее множество добавленных в дерево вершин со множеством недобавленных имеет вес, меньший веса ребра x->y. Значит, это
альтернативное ребро можно удалить и добавить x->y. При этом получившееся дерево останется остовным деревом, а вес его увеличится. Значит выбор
ребра x->y был верным.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
В лучшем случае, если граф содержит несколько компонент связности, сложность алгоритма соответствует сложности DFS и составляет O(V + E),
где V - число вершин, а E - число ребер в графе. В худшем, если компонента связности одна и придется строить дерево, сложность соостветствует сложности алгоритма Прима
на очереди с приоритетом - O(Elog(V)).


-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Алгоритм требует O(E) памяти для хранения списка смежности плюс O(E) для хранения очереди плюс O(V) для хранения двух хеш-таблиц с добавленными и недобавленными вершинами.
Итого, пространственная сложность - O(E + V), где E - число ребер, а V - число вершин в графе.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

struct Edge {
    Edge() = default;
    Edge(int from, int to, int weight) : from_(from), to_(to), weight_(weight){}

    int from_ = 0;
    int to_ = 0;
    int weight_ = 0;
};

std::vector<std::vector<Edge>> GetAdjacencyList(){
    int vertexes, edges = 0;
    std::cin >> vertexes >> edges;
    std::vector<std::vector<Edge>> list(vertexes);
    
    for (int i = 0; i < edges; ++i){
        int from, to, weight;
        std::cin >> from >> to >> weight;
        list[from - 1].push_back({from - 1, to - 1, weight});
        list[to - 1].push_back({to - 1, from - 1, weight});
    }

    return list;
}

template <typename T>
void PushRangeToQueue(std::priority_queue<Edge, std::vector<Edge>, T>& queue, const std::vector<Edge> v, std::unordered_set<int>& visited){
    for (const Edge& edge : v){
        if (!visited.count(edge.to_)){
            queue.push(edge); 
        }
    }
}

template <typename T>
Edge ExtractMaxEdge(std::priority_queue<Edge, std::vector<Edge>, T>& queue,std::unordered_set<int>& visited){
    Edge edge = queue.top();
    queue.pop();
    while(true){
        if (!visited.count(edge.to_)){
            break;
        }
        else {
            edge = queue.top();
            queue.pop();
        }
    }
    return edge;
}

long long int GetMaxSpanningTreeWeight(const std::vector<std::vector<Edge>>& list){
    size_t sum_of_weights = 0;

    auto comparator = [](const Edge& lhs, const Edge& rhs){ return lhs.weight_ < rhs.weight_; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(comparator)> queue;

    std::unordered_set<int> unvisited;
    std::unordered_set<int> visited;

    for (size_t i = 0; i < list.size(); ++i){
        unvisited.insert(i);
    }

    PushRangeToQueue(queue, list[0], visited);
    visited.insert(0);
    unvisited.erase(0);

    while (!queue.empty() && !unvisited.empty()){
        Edge edge = ExtractMaxEdge(queue, visited);
        sum_of_weights += edge.weight_;
        PushRangeToQueue(queue, list[edge.to_], visited);
        visited.insert(edge.to_);
        unvisited.erase(edge.to_);
    }

    return sum_of_weights;
}


void RecursiveDFS(const int current_vertex, const std::vector<std::vector<Edge>>& list, std::vector<int>& colors, int color){
    colors[current_vertex] = color;
    for (const Edge& edge : list[current_vertex]) {
        if (colors[edge.to_] == -1)
            RecursiveDFS(edge.to_, list, colors, color);
    }
}

bool CheckForConnectivity(const std::vector<std::vector<Edge>>& list){
    std::vector<int> colors(list.size(), -1);
    int color = 1;
    for (size_t vertex = 0; vertex < list.size(); ++vertex){
        if (colors[vertex] == -1 && vertex == 0){
            RecursiveDFS(vertex, list, colors, color);
            ++color;
        }
        else if (vertex != 0 && colors[vertex] == -1){
            return false;
        }
        else {
            continue;
        }
    }
    return true;
}

int main(){

    auto graph = GetAdjacencyList();

    if (!CheckForConnectivity(graph)){
        std::cout << "Oops! I did it again" << '\n';
        return 0;
    }

    auto sum = GetMaxSpanningTreeWeight(graph);
    std::cout << sum;

    return 0;
}