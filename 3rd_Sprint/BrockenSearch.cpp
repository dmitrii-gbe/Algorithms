//https://contest.yandex.ru/contest/23815/run-report/112435977/
//#include "solution.h"
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
	if (*middle > *std::prev(middle) && *middle > *std::next(middle)){
		return std::next(middle);
	}
	if (*middle > *std::prev(middle) && *middle < *std::next(middle) && *middle > first_value){
		return GetPartitionBorder(middle, last, first_value);
	}
	if (*middle > *std::prev(middle) && *middle < *std::next(middle) && *middle < first_value){
		return GetPartitionBorder(first, middle, first_value);
	}
	return last;
	
}

template <typename Iterator, typename ValueType>
int GetValueIndex(Iterator first, Iterator last, Iterator border, ValueType value){
	int result = 0;
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