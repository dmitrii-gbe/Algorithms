#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>

size_t GetCommonPrefix(const std::string_view s1, const std::string_view s2, size_t max_index) {
    size_t index = 0;
    while (s1[index] == s2[index] && index < std::min(std::min(s1.size(), s2.size()), max_index)) {
        ++index;
    }
    return index;
}

int main() {
    int count = 0;
    std::cin >> count;
    std::string s;
    std::cin >> s;
    size_t common_prefix_index = s.size();
    while (count != 1) {
        std::string s1;
        std::cin >> s1;
        common_prefix_index = std::min(common_prefix_index, GetCommonPrefix(s, s1, common_prefix_index));
        std::swap(s, s1);
        --count;
    }
    std::cout << common_prefix_index;
}
