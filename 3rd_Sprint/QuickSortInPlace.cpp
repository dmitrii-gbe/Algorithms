//https://contest.yandex.ru/contest/23815/run-report/113024345/

//https://contest.yandex.ru/contest/23815/run-report/113078991/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает входные данные с помощью фукнции GetInputData и контруирует из них std::vector<Participant>.
Затем полученный вектор сортируется с помощью функции QuickSortInPlace, принимающей итераторы на начало массива и элемент следующих за последним,
а также компаратор, возвращающий true, если первый аргумент меньше второго. Функция QuickSortInPlace не делает ничего, если в переданном диапазоне было менее 
двух элементов. В противном случае, она случайным образом выбирает элемент диапазона (с помощью функции GetRandomIndex) в качестве осевогои, начиная с двух концов массива, обменивает 
элементы, нарушающие упорядоченность относительно оси. Затем, QuickSortInPlace вызывается рекурсивно для двух частей массива, элементы первой из которых меньше или равны осевому,
а элементы второго - больше либо равны. Процедура повторяется, число элементов в подмассивах-аргументах не станет меньше двух.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --



-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Сложность конструирования массива входных данных - О(N). Сложность быстрой сортировки
Поиск границы разрыва имеет сложность, не более, чем log2(N), где N - длина данного массива. Поиск искомого элемента имеет сложность, не более, чем
2log2(N), так как сначала проверяется наличие элемента в подмассиве за log2(n), а затем за log2(n) выполняется поиск итератора, указывающего на него. При этом n <= N. 
Таким образом общаая сложность алгоритма не более 3log2(N).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Алгоритм использует дополнительную память только за тем, чтобы хранить один итератор в функциях GetPartitionBorder и broken_search. Таким образом, пространственная сложность - O(1).
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <tuple>

size_t GetRandomIndex(size_t upper_limit){
    std::srand(std::time(nullptr));
    return static_cast<size_t>((std::rand() * 1.0) / RAND_MAX * upper_limit);
}

struct Participant {
    Participant(const std::string& login, const int64_t points, const int64_t penalty) : login_(login)
                                                                           , points_(points)  
                                                                           , penalty_(penalty)
                                                                             {}
    
    std::string login_;
    int64_t points_ = 0;
    int64_t penalty_ = 0;

    bool operator==(const Participant& other) const {
        return login_ == other.login_ && points_ == other.points_ && penalty_ == other.penalty_;
    }

    bool operator!=(const Participant& other) const {
        return !(*this == other);
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

template <typename It, typename Comparator>
void QuickSortInPlace(It first, It last, Comparator comp){
    if (last - first < 2){
        return;
    }
    else {
        typename std::iterator_traits<It>::value_type pivot = *(first + GetRandomIndex(last - first - 1));
        It left = first;
        It right = std::prev(last);
        while (right >= left){
            if (!comp(*left, pivot) && (comp(*right, pivot) || *right == pivot)){
                std::swap(*left, *right);
                ++left;
                --right;
            }
            else if (comp(*left, pivot) && (comp(*right, pivot) || *right == pivot)){
                ++left;
            }
            else if (!comp(*left, pivot) && (!comp(*right, pivot) && *right != pivot)){
                --right;
            }
            else {
                ++left;
                --right;
            }
        }
        QuickSortInPlace(first, left, comp);
        QuickSortInPlace(left, last, comp);
    }
}

int main(){

    std::vector<Participant> input_data = GetInputData();

    QuickSortInPlace(input_data.begin(), input_data.end(), [](const Participant& left, const Participant& right)
                                                            { return std::tuple(-left.points_, left.penalty_, left.login_) < std::tuple(-right.points_, right.penalty_, right.login_); });

    std::cout << input_data;
    return 0;
}