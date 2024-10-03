#include <iostream>
#include <string>
#include <vector>

std::vector<int> GetPrefix(const std::string &s) {
    std::vector<int> prefix(s.size(), 0);
    for (size_t i = 1; i < s.size(); ++i) {
        int current = prefix[i - 1];

        while (s[i] != s[current] && current > 0) {
            current = prefix[current - 1];
        }

        if (s[i] == s[current]) {
            prefix[i] = current + 1;
        }
    }
    return prefix;
}

int MaxRepeat(const std::string &text) {
    auto prefix = GetPrefix(text);
    size_t i = prefix.size() - 1;
    int max = prefix.back();

    return ((text.size() % (prefix.size() - prefix.back()) == 0)
                ? text.size() / (prefix.size() - prefix.back())
                : 1);
}

int main() {
    std::string text;
    std::cin >> text;
    std::cout << MaxRepeat(text);
    return 0;
}
