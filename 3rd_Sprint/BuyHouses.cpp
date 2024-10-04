#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> GetNumbers(size_t num) {
    std::vector<int> result(num);
    size_t index = 0;
    while (index < num) {
        std::cin >> result[index++];
    }
    return result;
}

int GetMaximumHouses(const std::vector<int>& v, int money) {
    int result = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (money >= v[i]) {
            money -= v[i];
            ++result;
        }
    }
    return result;
}

int main() {
    size_t num = 0;
    int money = 0;
    std::cin >> num >> money;
    auto v = GetNumbers(num);
    std::sort(v.begin(), v.end());
    std::cout << GetMaximumHouses(v, money);
    return 0;
}
