#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> GetNumbers() {
    size_t number = 0;
    std::cin >> number;
    std::vector<int> result(number);
    size_t index = 0;
    while (index < number) {
        std::cin >> result[index++];
    }
    return result;
}

int MaxSatisfied(const std::vector<int>& kids, const std::vector<int>& cookies) {
    int satisfied = 0;
    size_t j = 0;
    for (size_t i = 0; i < kids.size() && j < cookies.size();) {
        if (kids[i] <= cookies[j]) {
            ++satisfied;
            ++j;
            ++i;
        } else {
            ++i;
        }
    }
    return satisfied;
}

int main() {
    auto kids = GetNumbers();
    auto cookies = GetNumbers();
    std::sort(cookies.begin(), cookies.end(), std::greater<int>{});
    std::sort(kids.begin(), kids.end(), std::greater<int>{});
    std::cout << MaxSatisfied(kids, cookies);
    return 0;
}
