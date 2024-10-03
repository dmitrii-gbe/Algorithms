#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::string CountWords(int count) {
    std::map<std::string, int> map;
    while (count != 0) {
        std::string s;
        std::cin >> s;
        ++map[s];
        --count;
    }
    std::vector<std::pair<std::string, int>> v{map.begin(), map.end()};

    std::sort(v.begin(), v.end(), [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });
    int freq = v[0].second;
    size_t i = 0;
    for (; i < v.size(); ++i) {
        if (v[i].second != freq) {
            break;
        }
    }
    std::sort(v.begin(), v.begin() + i,
              [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
    return v.front().first;
}

int main() {
    int count = 0;
    std::cin >> count;
    std::cout << CountWords(count);
}
