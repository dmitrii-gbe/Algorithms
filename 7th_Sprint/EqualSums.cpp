#include <iostream>
#include <numeric>
#include <vector>

std::vector<int> GetNumbers(int number) {
    std::vector<int> numbers(number, 0);
    for (int i = 0; i != number; ++i) {
        std::cin >> numbers[i];
    }
    return numbers;
}

bool IfPossibleToSplit(const std::vector<int>& numbers) {
    int max_sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    if (numbers.size() < 2 || max_sum % 2 != 0) {
        return false;
    }

    int half_sum = max_sum / 2;
    std::vector<int> active(half_sum + 1, 0);
    std::vector<int> buffer = active;

    for (int i = 1; i < (int)numbers.size() + 1; ++i) {
        for (int j = 1; j < (int)active.size(); ++j) {
            int top_left = (numbers[i - 1] > j ? buffer[j] - numbers[i - 1] : buffer[j - numbers[i - 1]]);
            int value = std::max(buffer[j], top_left + numbers[i - 1]);
            active[j] = value;
        }

        if (active.back() == half_sum) {
            return true;
        }

        std::swap(active, buffer);
    }

    return false;
}

int main() {
    int numbers_count = 0;

    std::cin >> numbers_count;

    auto numbers = GetNumbers(numbers_count);

    std::cout << (IfPossibleToSplit(numbers) ? "True" : "False");

    return 0;
}
