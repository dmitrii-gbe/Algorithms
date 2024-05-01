//https://contest.yandex.ru/contest/23815/run-report/113293630/
/*
-- ПРИНЦИП РАБОТЫ --
Решение заключается в том, чтобы с помощью функции GetPartitionBorder найти точку стыка между двумя отсортированными 
частями массива. Функция использует бинарный поиск и в цикле ищет минимальный элемент всего массива.
Найдя такой элемент, функция возвращает итератор на него. Предварительно GetPartitionBorder сравнивает
первый элемент массива с последним, в случае, если последний больше первого или равен ему, возвращает итератор на элемент, следующий
за последним. Эта ситуация означает, что кольцевой буфер был разорван корректно и упорядоченность элементов сохранилась, либо, при условии, что 
массив содержал уникальные элементы, кольцевой буфер содержит только один элемент.
Затем для поиска индекса элемента выполняется бинарный поиск в двух отсортированных половинах массива, либо во всем массиве сразу,
если он сохранил упорядоченность. Из полученного с помощью std::lower_bound() итератора и begin() расчитывается индекс.
Если элемент не был найден, GetValueIndex возвращает -1.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Разрыв отсортированного по неубыванию массива на кольцевом буфере может привести только к двум исходам: массив останется упорядоченным,
либо будет содержать два подмассива, все элементы первого из которых будут не меньше всех элементов второго. Первая ситуация проверяется 
путем сравнения первого и последнего элементов массива. Если упорядоченность сохранена, то поиск искомого элемента можно вести во всем массиве целиком.
В противном случае, нужно найти точку сочленения двух упорядоченных половин. Таким элементом можно считать минимальный элемент всего массива.
Исходя из этого свойства, граница ищется бинарным поиском. Затем, когда граница найдена, выполняется поиск искомого элемента в двух упорядоченных половинах.


-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Поиск границы разрыва имеет сложность, не более, чем log2(N), где N - длина данного массива. Поиск искомого элемента имеет сложность, не более, чем
log2(N). Таким образом общаая сложность алгоритма не более log2(N).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Алгоритм использует дополнительную память только затем, чтобы хранить один итератор в функциях GetPartitionBorder и broken_search. Таким образом, пространственная сложность - O(1).
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

template <typename Iterator>
Iterator GetPartitionBorder(Iterator first, Iterator last){
	if (*first <= *std::prev(last)){
		return last;
	}

    Iterator start = first;
    Iterator end = std::prev(last);

    while (start < end){
    Iterator mid = start + (end - start + 1) / 2;
        if (*mid < *end){
            end = mid;
        }
        else {
            start = mid;
        }
    }
    return start;

}

template <typename Iterator, typename ValueType>
int GetValueIndex(Iterator first, Iterator last, Iterator border, ValueType value){
	if (border == last){
		auto it = std::lower_bound(first, last, value);
		return (it == last || *it != value) ? -1 : it - first;
 	}
	if (value < *first){
		auto it = std::lower_bound(border, last, value);
		return (it == last || *it != value) ? -1 : it - first;
	}
	else {
		auto it = std::lower_bound(first, border, value);
		return (it == border || *it != value) ? -1 : it - first;
	}
}

int broken_search(const std::vector<int>& vec, int k) {
	auto border_iterator = GetPartitionBorder(vec.begin(), vec.end());
	return GetValueIndex(vec.begin(), vec.end(), border_iterator, k);
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}


int main(){
	test();
	return 0;
}