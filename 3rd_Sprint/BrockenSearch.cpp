//https://contest.yandex.ru/contest/23815/run-report/113078991/
/*
-- ПРИНЦИП РАБОТЫ --
Решение заключается в том, чтобы с помощью функции GetPartitionBorder найти точку стыка между двумя отсортированными 
частями массива. Функция использует бинарный поиск и рекурсивно ищет элемент такой, чтобы он был меньше и предыдущего, и следующего 
за ним элементов. Найдя такой элемент, функция возвращает итератор на него. Предварительно GetPartitionBorder сравнивает
первый элемент массива с последним, в случае, если последний больше первого, возвращает итератор на элемент, следующий
за последним. Эта ситуация означает, что кольцевой буфер был разорван корректно и упорядоченность элементов сохранилась.
Затем для поиска индекса элемента выполняется бинарный поиск в двух отсортированных половинах массива, либо во всем массиве сразу,
если он сохранил упорядоченность. Из полученного с помощью std::lower_bound() итератора и begin() расчитывается индекс.
Если элемент не был найден, GetValueIndex возвращает -1.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Разрыв отсортированного по неубыванию массива на кольцевом буфере может привести только к двум исходам: массив останется упорядоченным,
либо будет содержать два подмассива, все элементы первого из которых будут не меньше всех элементов второго. Первая ситуация проверяется 
путем сравнения первого и последнего элементов массива. Если упорядоченность сохранена, то поиск искомого элемента можно вести во всем массиве целиком.
В противном случае, нужно найти точку сочленения двух упорядоченных половин. Первый элемент второго массива, содержащего меньшие элементы должен быть
больше следующего за ним и меньше предыдущего. При этом, при соблюдении условия задачи, такой элемент будет единственным. Исходя из этого свойства, 
граница ищется бинарным поиском. Если на очередной итерации поиска целевой элемент не был найден, нужно решить, с какой стороны
от текущего элемента искать. Для этого текущий элемент сравнивается с первым элементом. Если текущий больше первого, то искать нужно справа и наоборот.
Затем, когда граница найдена, выполняется поиск искомого элемента в двух упорядоченных половинах.


-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Поиск границы разрыва имеет сложность, не более, чем log2(N), где N - длина данного массива. Поиск искомого элемента имеет сложность, не более, чем
2log2(N), так как сначала проверяется наличие элемента в подмассиве за log2(n), а затем за log2(n) выполняется поиск итератора, указывающего на него. При этом n <= N. 
Таким образом общаая сложность алгоритма не более 3log2(N).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Алгоритм использует дополнительную память только затем, чтобы хранить один итератор в функциях GetPartitionBorder и broken_search. Таким образом, пространственная сложность - O(1).
*/


#include "solution.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

template <typename Iterator, typename ValueType>
Iterator GetPartitionBorder(Iterator first, Iterator last, ValueType first_value){
	if (*first < *std::prev(last)){
		return last;
	}

	Iterator middle = first + (last - first) / 2;
	if ((*middle < *std::prev(middle) && std::next(middle) == last) || (*middle < *std::prev(middle) && *middle < *std::next(middle))){
		return middle;
	}
	else if (*middle > *std::prev(middle) && *middle > *std::next(middle)){
		return std::next(middle);
	}
	else if (*middle > *std::prev(middle) && *middle < *std::next(middle) && *middle > first_value){
		return GetPartitionBorder(middle, last, first_value);
	}
	else if (*middle > *std::prev(middle) && *middle < *std::next(middle) && *middle < first_value){
		return GetPartitionBorder(first, middle, first_value);
	}
	else {
		return last;
	}	
}

template <typename Iterator, typename ValueType>
int GetValueIndex(Iterator first, Iterator last, Iterator border, ValueType value){
	if (border == last){
		return (!std::binary_search(first, last, value)) ? -1 : std::lower_bound(first, last, value) - first;
 	}
	if (value < *first){
		return (!std::binary_search(border, last, value)) ? -1 : std::lower_bound(border, last, value) - first;
	}
	else {
		return (!std::binary_search(first, border, value)) ? -1 : std::lower_bound(first, border, value) - first;
	}
}

int broken_search(const std::vector<int>& vec, int k) {
	auto border_iterator = GetPartitionBorder(vec.begin(), vec.end(), vec.front());
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