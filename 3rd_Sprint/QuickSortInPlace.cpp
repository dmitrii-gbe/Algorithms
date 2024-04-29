//https://contest.yandex.ru/contest/23815/run-report/113184605/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает входные данные с помощью фукнции GetInputData и конcтруирует из них std::vector<Participant>.
Затем полученный вектор сортируется с помощью функции QuickSortInPlace, принимающей итераторы на начало массива 
и элемент, следующий за последним, а также компаратор, возвращающий true, если первый аргумент меньше второго. 
Функция QuickSortInPlace не делает ничего, если в переданном диапазоне было менее двух элементов. В противном 
случае она случайным образом выбирает элемент диапазона (с помощью функции GetRandomIndex) в качестве осевого,
и, начиная с двух концов массива, обменивает пары элементов, нарушающие упорядоченность относительно оси. Первый
элемент такой пары должен быть строго больше осевого, а второй - меньше, либо равен. Если один или оба элемента
не соответствуют этому условию (то есть, текущие элементы упорядочены относительно оси), итераторы сдвигаются
навстречу друг другу. Затем, когда левый итератор станет больше правого или равен ему, QuickSortInPlace вызывается 
рекурсивно для двух частей массива, элементы одной из которых меньше или равны осевому, а элементы второй - больше.
Процедура повторяется, пока число элементов в подмассивах-аргументах не станет меньше двух. 

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Алгоритм основан на разделении исходного массива (и рекурсивном разделении и упорядочивании его частей) так,
чтобы элементы одной "половины" были меньше другой. Границей такого разделения служит произвольный элемент
массива. Таким образом, корректность его работы зависит от корректности разделения. Во-первых, это достигается
благодаря критериям обмена элементов и сдвига итераторов, если обмен в текущий момент невозможен. Во-вторых,
алгоритм учитывает возможность, что левый итератор в момент, когда должно произойти разделение, будет указывать
на элемент меньший, чем осевой. Так может произойти, если левый итератор был сдвинут вправо, тогда как правый
указывал на подходящий для обмена элемент. В этой ситуации в качестве подмассив для рекурсивного вызова
используются диапазоны [first, left + 1) и [left + 1, last). В противном случае, QuickSortInPlace вызывается
для [first, left) и [left, last). 

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Функция QuickSortInPlace вызывается и переупорядочивает N элементов, где N - длина исходного массива, столько раз,
сколько раз его требуется поделить, чтобы получить массивы, длиной не превосходящие 1.  Таким образом, сложность
быстрой сортировки составит O(Nlog(N)).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Каждый последовательный рекурсивный вызов QuickSortInPlace требует память только, чтобы хранить пару итераторов
и значение осевого элемента. Таким образом, пространственная сложность алгоритма составляет O(logN).
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

size_t GetRandomIndex(size_t upper_limit){
    return size_t((std::rand() / (RAND_MAX * 1.0)) * upper_limit);
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
void QuickSortInPlace(It first, It last, Comparator comparator){
    if (last - first < 2){
        return;
    }
    else {
        typename std::iterator_traits<It>::value_type pivot = *(first + std::min(GetRandomIndex(last - first), size_t(last - first - 1)));
        It left = first;
        It right = last - 1;
        while (right > left){
            if (!comparator(*left, pivot) && *left != pivot && (comparator(*right, pivot) || *right == pivot)){ 
                std::swap(*left, *right);
                ++left;
                --right;
                continue;
            }

            if (comparator(*left, pivot) || *left == pivot){ 
                ++left;
            }

            if (!comparator(*right, pivot) && *right != pivot){ 
                --right;
            }
        }
        QuickSortInPlace(first, comparator(*left, pivot) ? left + 1 : left, comparator);
        QuickSortInPlace(comparator(*left, pivot) ? left + 1 : left, last, comparator);
    }
}

int main(){

    std::vector<Participant> input_data = GetInputData();

    QuickSortInPlace(input_data.begin(), input_data.end(), [](const Participant& left, const Participant& right)
                                                            { return std::tuple(-left.points_, left.penalty_, left.login_) < std::tuple(-right.points_, right.penalty_, right.login_); });

    std::cout << input_data;
    return 0;
}