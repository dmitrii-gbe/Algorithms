#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>


bool IsSubsequence(const std::string& left, const std::string& right){
	auto start = right.begin();
	for (char c : left){
		auto it = std::find(start, right.end(), c);
		if (it == right.end()){
			return false;
		}
		start = it + 1;
	}
	return true;
		
}

int main(){
	std::string first, second;
	std::getline(std::cin, first);
	std::getline(std::cin, second);
	
	if (IsSubsequence(first, second)){
		std::cout << "True";
	}
	else {
		std::cout << "False";
	}
	return 0;
}}
