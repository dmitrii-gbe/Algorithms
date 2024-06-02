//https://contest.yandex.ru/contest/24810/run-report/114873413/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает входные данные с помощью фукнции GetInputData и конcтруирует из них std::vector<Participant>.
Затем полученный вектор сортируется с помощью функции HeapSort, принимающей итераторы на начало массива 
и элемент, следующий за последним, а также компаратор, возвращающий true, если первый аргумент меньше второго.
Внутри функции HeapSort создается куча, в которой вершина - минимальный элемент исходного диапазона
(с точки зрения компаратора). Из кучи элементы извлекаются по одному из вершины и используются для перезаписи
элементов исходного массива. Извлечение происходит путем обмена вершины и последнего элемента массива, после чего
последний элемент удаляется, а свойства кучи восстанавливаются функцией SiftDown. Операция повторяется до тех пор, 
пока в куче не останется один фиктивный нулевой элемент. В итоге исходный массив полностью перезаписывается
элементами в порядке их возрастания.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Корректность алгоритма зависит, в первую очередь, от использования компаратора, переданного в качестве аргумента
в функцию HeapSort. Он возвращает true, если в отсортированном массиве перевый аргумент должен быть расположен перед вторым.
Компаратор используется в функциях SiftUp и SiftDown для переупорядочения элементов кучи после вставки и удаления.
При этом обе функции предназначены для поддержания кучи с минимальным (таким элементом, который должен быть первым в отсортированном
массиве) элементом в вершине. Обе функции учитывают то, что все элементы в массиве уникальны. 

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Функция HeapSort строит из исходного массива размером N двоичную кучу за время, небольшее, чем O(NlogN), так как каждый из N элементов
вставляется в кучу, после чего переупорядочивается за O(logN). Аналогично с извлечением элементов из кучи. Каждый из N элементов извлекается, после
чего свойства кучи восстанавливаются за время не большее, чем O(logN). Таким образом, временная сложность всего алгоритма - O(logN).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Алгоритм требует O(N) дополнительной памяти для построения кучи на основе исходного массива.
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>


struct Participant {
    Participant(const std::string& login, const int64_t points, const int64_t penalty) : login_(login)
                                                                           , points_(points)  
                                                                           , penalty_(penalty)
                                                                             {}

    Participant() = default;
    
    std::string login_;
    int64_t points_ = 0;
    int64_t penalty_ = 0;

    bool operator==(const Participant& other) const {
        return this->Key() == other.Key();
    }

    bool operator!=(const Participant& other) const {
        return !(*this == other);
    }

    std::tuple<int64_t, int64_t, std::string> Key() const {
        return std::tuple(-points_, penalty_, login_);
    }
};

std::ostream& operator<<(std::ostream& out, const Participant& item){
    out << item.login_;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    bool is_first = true;
    for (const auto& item : v){
        if (is_first){
            out << item;
            is_first = false;
        }
        else {
            out << '\n' << item;
        }
    }
    return out;
}

std::vector<Participant> GetInputData(){ 
    size_t count = 0;
    std::cin >> count;
    std::vector<Participant> result;
    result.reserve(count);

    while (count > 0){
        std::string login;
        int64_t points, penalty;
        std::cin >> login >> points >> penalty;
        Participant item = {login, points, penalty};
        result.push_back(item);
        --count;
    }

    return result;
}

template <typename T, typename Comparator>
void SiftDown(std::vector<T>& heap, size_t idx, Comparator comparator) {

    while (idx * 2 < heap.size()){

        size_t left = 2 * idx;
        size_t right = left + 1;

        bool left_is_greater = (right < heap.size()) ? !comparator(heap[right], heap[left]) : true;

        if (left_is_greater && !comparator(heap[idx], heap[left])){
            std::swap(heap[idx], heap[left]);
            idx = left;
            continue;
        }

        if (!left_is_greater && !comparator(heap[idx], heap[right])){
            std::swap(heap[idx], heap[right]);
            idx = right;
            continue;
        }

        break;

    }

}

template <typename T, typename Comparator>
void SiftUp(std::vector<T>& heap, size_t idx, Comparator comparator) {
    while (idx != 1){
        if (!comparator(heap[idx / 2], heap[idx])){
            std::swap(heap[idx / 2], heap[idx]);
            idx /= 2;
        }
        else {
            break;
        }
    }
}

template <typename It, typename Comparator>
std::vector<typename std::iterator_traits<It>::value_type> BuildHeap(It begin, It end, Comparator comparator){
    std::vector<typename std::iterator_traits<It>::value_type> heap;
    heap.reserve(end - begin + 1);
    heap.push_back(typename std::iterator_traits<It>::value_type {});

    for (It it = begin; it != end; ++it){
        heap.push_back(*it);
        SiftUp(heap, heap.size() - 1, comparator);
    }

    return heap;
}



template <typename It, typename Comparator>
void HeapSort(It begin, It end, Comparator comparator){

    auto heap = BuildHeap(begin, end, comparator);
    
    size_t counter = 0;
    
    while (heap.size() != 1){
        *(begin + counter++) = heap[1];
        std::swap(heap[1], heap.back());
        heap.pop_back();
        SiftDown(heap, 1, comparator);
    }


}

int main(){

    std::vector<Participant> input_data = GetInputData();

    HeapSort(input_data.begin(), input_data.end(), [](const Participant& left, const Participant& right)
                                                             { return left.Key() < right.Key(); });

    std::cout << input_data;
    return 0;
}