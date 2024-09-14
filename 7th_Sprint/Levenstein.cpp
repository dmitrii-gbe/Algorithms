// https://contest.yandex.ru/contest/25597/run-report/117900884/
#include <iostream>
#include <vector>

std::string GetString() {
    std::string result;
    std::getline(std::cin, result);
    return result;
}

void AssignValues(const std::vector<int>& active, const std::vector<int>& buffer, int& top, int& left,
                  int& diag, size_t i, size_t j) {
    if (j - 1 == 0 && i - 1 == 0) {
        left = i;
        top = j;
        diag = 0;
    } else if (i - 1 == 0 && j - 1 != 0) {
        left = active[j - 1];
        top = j;
        diag = j - 1;
    } else if (i - 1 != 0 && j - 1 == 0) {
        left = i;
        top = buffer[j];
        diag = i - 1;
    } else if (i - 1 != 0 && j - 1 != 0) {
        left = active[j - 1];
        top = buffer[j];
        diag = buffer[j - 1];
    }
}

int CalculateDistance(const std::string& s1, const std::string& s2) {
    std::vector<int> active(s2.size() + 1);
    std::vector<int> buffer(s2.size() + 1);
    for (size_t i = 1; i < s1.size() + 1; ++i) {
        for (size_t j = 1; j < s2.size() + 1; ++j) {
            int left = 0;
            int top = 0;
            int diag = 0;

            AssignValues(active, buffer, top, left, diag, i, j);

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

int main() {
    auto seq1 = GetString();

    auto seq2 = GetString();

    std::cout << CalculateDistance(seq1, seq2);

    return 0;
}
