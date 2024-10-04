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

int MaxPerimeter(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size() - 2; ++i) {
        if (v[i] < v[i + 1] + v[i + 2]) {
            return v[i] + v[i + 1] + v[i + 2];
        }
    }
    return 0;
}

int main() {
    auto v = GetNumbers();
    std::sort(v.begin(), v.end(), std::greater<int>{});
    // for (auto& item : v) {
    //     std::cout << item << " ";
    // }
    // std::cout << std::endl;
    std::cout << MaxPerimeter(v);
    return 0;
}
