#include <iostream>
#include <vector>

std::vector<int> GetNumbers(size_t num) {
    std::vector<int> result(num);
    size_t index = 0;
    while (index < num) {
        std::cin >> result[index];
        ++index;
    }
    return result;
}

int GetMaximumPartitioning(const std::vector<int>& v) {
    int result = 0;
    int min = 0;
    int max = v[0];
    int counter = 0;
    bool min_found = false;
    bool increment = false;
    for (size_t i = 0; i < v.size();) {
        while ((counter - 1 != max - min || !min_found || v[i] < max) && i < v.size()) {
            increment = true;
            min_found = min_found ? true : (v[i] == min);
            ++counter;
            max = std::max(max, v[i]);
            ++i;
        }

        if (increment) {
            increment = false;
        } else {
            max = v[i];
            ++i;
        }

        ++result;
        min = max + 1;
        min_found = false;
        counter = 0;
    }
    return result;
}

int main() {
    size_t num = 0;
    std::cin >> num;
    auto v = GetNumbers(num);
    std::cout << GetMaximumPartitioning(v);
    return 0;
}
