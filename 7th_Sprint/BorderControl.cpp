#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

int CalculateDistance(const std::string &s1, const std::string &s2) {
    std::vector<int> active(s2.size() + 1);
    std::vector<int> buffer(s2.size() + 1);
    std::iota(buffer.begin(), buffer.end(), 0);
    for (size_t i = 1; i < s1.size() + 1; ++i) {
        active[0] = i;
        for (size_t j = 1; j < s2.size() + 1; ++j) {
            int left = active[j - 1];
            int top = buffer[j];
            int diag = buffer[j - 1];

            if (s1[i - 1] == s2[j - 1]) {
                active[j] = diag;
            } else {
                active[j] = std::min(left, std::min(top, diag)) + 1;
            }
        }
        std::swap(buffer, active);
    }

    return buffer.back();
}

bool IsEqual(const std::string &s1, const std::string &s2) {
    int shift = s1.size() - s2.size();
    size_t i = 0;
    size_t j = 0;
    while (s1[i] == s2[j] && i < s1.size() && j < s2.size()) {
        ++i;
        ++j;
    }

    if (i == s1.size() && j == s2.size()) {
        return true;
    }

    if ((i == s1.size() && s2.size() - i == 1) || (j == s2.size() && s1.size() - j == 1)) {
        return true;
    } else if (shift == 1) {
        std::string s = s1[i] + s2.substr(j);
        return s1.substr(i) == s;
    } else if (shift == -1) {
        std::string s = s2[j] + s1.substr(i);
        return s2.substr(j) == s;
    } else if (shift == 0 && s1.substr(i + 1) == s2.substr(j + 1)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;

    std::cout << (IsEqual(s1, s2) ? "OK" : "FAIL");

    return 0;
}
