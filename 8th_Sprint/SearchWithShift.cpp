#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T> v) {
    bool is_first = true;
    for (const auto& item : v) {
        if (is_first) {
            out << item;
            is_first = false;
        } else {
            out << " " << item;
        }
    }
    return out;
}

template <typename T>
std::vector<T> GetVector() {
    std::vector<T> result;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        T item;
        std::cin >> item;
        result.push_back(item);
    }
    return result;
}

bool IsEqual(const std::vector<int>& array, size_t i, const std::vector<int>& query) {
    size_t j = 0;
    int shift = array[i] - query[0];
    for (; j < query.size() && i < array.size();) {
        if (array[i++] - query[j++] != shift) {
            return false;
        }
    }
    return j == query.size();
}

std::vector<size_t> Search(const std::vector<int>& array, const std::vector<int>& query) {
    std::vector<size_t> result;
    for (size_t i = 0; i < array.size(); ++i) {
        if (IsEqual(array, i, query)) {
            result.push_back(i + 1);
        }
    }
    return result;
}

int main() {
    auto array = GetVector<int>();
    auto query = GetVector<int>();
    std::cout << Search(array, query);
    return 0;
}
