#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "log_duration.h"

template <typename T>

std::ostream& operator<<(std::ostream& out, const std::vector<T> v) {
    bool is_first = true;
    out << "[ ";
    for (const auto& item : v) {
        if (is_first) {
            out << item;
            is_first = false;
        } else {
            out << " " << item;
        }
    }
    out << " ]" << '\n';
    return out;
}

template <typename T>
std::vector<T> GetVector() {
    std::string tmp1;
    std::getline(std::cin, tmp1);
    int size = std::stoi(tmp1);
    std::vector<T> result;
    result.reserve(size);

    std::string query;
    std::getline(std::cin, query);

    std::string tmp;

    for (char c : query) {
        if (c != ' ') {
            tmp += c;
            continue;
        }
        if (c == ' ' && !tmp.empty()) {
            result.push_back(std::stoi(tmp));
            tmp.clear();
        }
    }
    result.push_back(std::stoi(tmp));

    return result;
}

size_t CalculateHash(int key) { return key + (key < 0) * (long(INT_MAX) * 2 + 1); }

int main() {
    for (int i = -10; i < 11; ++i) {
        std::cout << CalculateHash(i) << '\n';
    }

    return 0;
}