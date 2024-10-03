#include <iostream>
#include <map>
#include <string>

std::map<char, int> GetDictionary(const std::string& s) {
    std::map<char, int> m;
    for (const char c : s) {
        ++m[c];
    }
    return m;
}

std::string GetLongestPalindrome(std::map<char, int> m) {
    std::string result;
    for (auto it = m.begin(); it != m.end(); std::advance(it, 1)) {
        while (it->second > 1) {
            result += it->first;
            it->second -= 2;
        }
    }
    bool appended = false;
    for (auto it = m.begin(); it != m.end(); std::advance(it, 1)) {
        if (it->second == 1) {
            result += it->first;
            appended = true;
            break;
        }
    }

    if (appended) {
        std::string to_append = result.substr(0, result.size() - 1);
        result += std::string(to_append.rbegin(), to_append.rend());
    } else {
        result += std::string(result.rbegin(), result.rend());
    }

    return result;
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << GetLongestPalindrome(GetDictionary(s));
}
