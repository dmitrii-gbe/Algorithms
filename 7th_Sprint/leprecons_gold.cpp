#include <strings.h>

#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, std::vector<int> v) {
    bool is_first = true;
    for (size_t i = 0; i < v.size(); ++i) {
        if (is_first) {
            out << v[i];
            is_first = false;
        } else {
            out << " " << v[i];
        }
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>> v) {
    bool is_first = true;
    for (size_t i = 0; i < v.size(); ++i) {
        if (is_first) {
            out << v[i];
            is_first = false;
        } else {
            out << '\n' << v[i];
        }
    }
    return out;
}

std::vector<int> GetIngots(int number) {
    std::vector<int> ingots(number, 0);
    for (int i = 0; i != number; ++i) {
        std::cin >> ingots[i];
    }
    return ingots;
}

int GetMaxCost(const std::vector<int>& ingots, int max_capacity) {
    std::vector<std::vector<int>> matrix(ingots.size() + 1, std::vector<int>(max_capacity + 1));
    for (int ingot = 1; ingot < (int)ingots.size() + 1; ++ingot) {
        for (int capacity = 1; capacity < max_capacity + 1; ++capacity) {
            size_t index = capacity - ingots[ingot - 1] >= 0 ? capacity - ingots[ingot - 1] : 0;
            int value = std::max(matrix[ingot - 1][capacity], matrix[ingot - 1][index] + ingots[ingot - 1]);
            if (value <= capacity) {
                matrix[ingot][capacity] = value;
            } else {
                matrix[ingot][capacity] = matrix[ingot - 1][capacity];
            }
        }
    }

    return matrix.back().back();
}

int main() {
    int max_capacity = 0;

    int ingots_number = 0;

    std::cin >> ingots_number >> max_capacity;

    auto ingots = GetIngots(ingots_number);

    std::cout << GetMaxCost(ingots, max_capacity) << std::endl;

    return 0;
}
