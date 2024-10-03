#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> v) {
    bool is_first = true;
    for (const auto &item : v) {
        if (is_first) {
            out << item;
            is_first = false;
        } else {
            out << " " << item;
        }
    }
    return out;
}

std::vector<int> GetPrefix(const std::string &s) {
    std::vector<int> v(s.size(), 0);
    for (size_t i = 1; i < s.size(); ++i) {
        int current = v[i - 1];

        while (s[i] != s[current] && current > 0) {
            current = v[current - 1];
        }

        if (s[i] == s[current]) {
            v[i] = current + 1;
        }
    }
    return v;
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << GetPrefix(s);
    return 0;
}
