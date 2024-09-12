#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> GetPrices() {
    size_t days = 0;
    std::cin >> days;
    std::vector<int> prices(days);
    size_t counter = 0;

    while (counter != days) {
        std::cin >> prices[counter++];
    }

    return prices;
}

int CalculateMaxGain(const std::vector<int>& prices) {
    int result = 0;

    std::vector<int> differences(prices.size() - 1);

    for (size_t i = 0; i < prices.size() - 1; ++i) {
        differences[i] = prices[i + 1] - prices[i];
    }

    std::vector<size_t> min, max;

    for (size_t i = 0; i < differences.size(); ++i) {
        if (i == 0 && differences[i] > 0) {
            min.push_back(i);
        }

        if (i + 1 == differences.size() && differences[i] > 0) {
            max.push_back(i + 1);
        }

        if (i > 0 && differences[i - 1] >= 0 && differences[i] < 0) {
            max.push_back(i);
        }

        if (i > 0 && differences[i - 1] < 0 && differences[i] >= 0) {
            min.push_back(i);
        }
    }

    for (size_t i = 0; i < min.size(); ++i) {
        auto maxi = std::upper_bound(max.begin(), max.end(), min[i]);

        if (maxi != max.end()) {
            result += prices[*maxi] - prices[min[i]];
        }
    }

    return result;
}

int main() {
    std::vector<int> prices = GetPrices();

    std::cout << CalculateMaxGain(prices);

    return 0;
}