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

std::vector<size_t> FindOccurences(const std::string &text, const std::string &pattern) {
    std::vector<size_t> start_positions;

    std::string s = pattern + '0' + text;
    auto prefix = GetPrefix(s);
    for (size_t i = pattern.size() + 1; i < prefix.size(); ++i) {
        if (prefix[i] == (int)pattern.size()) {
            start_positions.push_back(i - 2 * pattern.size());
        }
    }
    std::cout << start_positions << std::endl;

    return start_positions;
}

void Replace(std::string &text, const std::string &pattern, const std::string &replacement) {
    auto start_positions = FindOccurences(text, pattern);
    std::string result;
    result.reserve(text.size());
    size_t begin = 0;
    for (size_t i = 0; i < start_positions.size(); ++i) {
        result += text.substr(begin, start_positions[i] - begin);
        begin = start_positions[i] + pattern.size();
        result += replacement;
    }
    result += text.substr(begin);
    text = std::move(result);
}

int main() {
    std::string text, pattern, replacement;
    std::cin >> text >> pattern >> replacement;
    // std::cout << FindOccurences(text, pattern) << std::endl;
    Replace(text, pattern, replacement);
    std::cout << text;
    return 0;
}
