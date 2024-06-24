//https://contest.yandex.ru/contest/25070/run-report/115458837/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает входные данные с помощью функции GetEdgeMatrix(), которая возвращает матрицу смежности, содержащей объекты
enum class WayType в качестве типа ребра между вершинами. Помимо данных ребер, GetEdgeMatrix() добавляет ребра из вершин с большими
номерами в вершины с меньшими типа, противоположного типу прямого ребра.
Идея решения заключается в том, что при наличии между двумя вершинами путей разного типа (все составные пути - одного
типа и отличаются по типу от прямого ребра между вершинами) в полученном с помощью GetEdgeMatrix() графе появится цикл.
Цикл ищется с помощью DFS. Все вершины, по которым проходит поиск в глубину, раскрашиваются в три цвета: исходно они белые,
при их посещении во время прямого хода рекурсии они перекрашиваются в серый, а во время обратного (когда все исходящие ребра посещены) - в черный.
Вывод о наличии цикла делается, если поиск встречает серую вершину, то есть такую, которую он уже проходил во время текущего запуска функции.
Функция DFS вызывается в функции CheckGraphOfDefinedType, которая проверяет подграф одного из типов, B или R. DFS возвращает true, если в текущей
компоненте связности цикл не был найден. CheckGraphOfDefinedType возвращает true, если ни в одной компоненте связности нет цикла. CheckGraphOfDefinedType
вызывается два раза в функции CheckIfMapIsOptimal для подграфов типа R и B и возвращает true, если оба не содержат циклов.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Алгоритм строится на том, что при наличии между двумя вершинами путей разного типа в графе появится цикл, если для каждой пары вершин x и y, где 
x > y, добавить ребро y->x, противоположное по типу ребру x->y. Действительно, между парой вершин x и y всегда есть прямое ребро x->y, например, типа R. Тогда,
при соблюдении указанного условия, все составные пути будут иметь тип B. Поскольку мы исходно добавили ребро y->x типа B, составные пути x->y образуют с этим ребром
цикл x->y->x. В случае, если и прямое ребро и составные пути будут иметь один тип, дополнительное ребро y->x будет противоположного типа и цикл не появится.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Временная сложность алгоритма равна сложности DFS - O(E), где E - число ребер в графе, равное V^2, где V - число вершин.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Алгоритм требует O(E) памяти для хранения матрицы смежности и O(V) - для хранения массива цветов вершин в функции CheckGraphOfDefinedType. Итого, 
пространственная сложность алгоритма - O(E + V).
*/
#include <iostream>
#include <vector>

enum class WayType {
    NONE,
    R,
    B
};

enum class Color {
    WHITE,
    GREY,
    BLACK
};

std::vector<std::vector<WayType>> GetEdgeMatrix(){
    int cities = 0;
    std::cin >> cities;
    std::vector<std::vector<WayType>> matrix(cities, std::vector<WayType>(cities, WayType::NONE));
    
    for (int i = 0; i < cities - 1; ++i){
        std::string s;
        std::cin >> s;
        for (int j = i + 1; j < cities; ++j){
            matrix.at(i).at(j) = (s.at(j - i - 1) == 'B') ? WayType::B : WayType::R;
            matrix.at(j).at(i) = (s.at(j - i - 1) == 'B') ? WayType::R : WayType::B;
        }
    }
    return matrix;
}

bool DFS(const std::vector<std::vector<WayType>>& map,
        size_t current_vertex,
        std::vector<Color>& color,
        WayType edge_type,
        bool is_entry_vertex){

    color[current_vertex] = Color::GREY;

    for (size_t i = (is_entry_vertex) ? current_vertex + 1 : 0; i < map.size(); ++i){
        WayType current_type = map.at(current_vertex).at(i);

        if (current_type == edge_type && color[i] == Color::GREY){
            return false;
        }

        if (color[i] == Color::WHITE
            && i > current_vertex
            && (current_type == edge_type
            || (edge_type == WayType::NONE && i != current_vertex))){

            if (!DFS(map, i, color, edge_type, false)){
                return false;
            }
        }
    }

    color[current_vertex] = Color::BLACK;

    return true;
}

bool CheckGraphOfDefinedType(const std::vector<std::vector<WayType>>& map, WayType edge_type){
    std::vector<Color> color(map.size(), Color::WHITE);
    for (size_t i = 0; i < map.size(); ++i){
        if (color[i] == Color::WHITE && !DFS(map, i, color, edge_type, true)){
            return false;
        }
    }
    return true;
}

bool CheckIfMapIsOptimal(const std::vector<std::vector<WayType>>& map){
    return CheckGraphOfDefinedType(map, WayType::R) && CheckGraphOfDefinedType(map, WayType::B);
}

int main(){

    auto map = GetEdgeMatrix();

    std::cout << (CheckIfMapIsOptimal(map) ? "YES" : "NO") << '\n';

    return 0;
}                  