#include <algorithm>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
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
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v) {
    bool is_first = true;
    for (const auto& item : v) {
        if (is_first) {
            out << item;
            is_first = false;
        } else {
            out << '\n' << item;
        }
    }
    out << " ]" << '\n';
    return out;
}

std::vector<char> GetVector() {
    size_t len = 0;
    std::cin >> len;
    std::vector<char> result(len);
    for (size_t i = 0; i < len; ++i) {
        std::scanf("%c", &result[i]);
    }
    // std::cout << result;
    return result;
}

template <typename T>
std::pair<std::vector<T>, std::vector<T>> GetMaxSubseq(const std::vector<T>& v1, const std::vector<T>& v2) {
    std::vector<T> result;
    std::vector<std::vector<T>> matrix(v1.size() + 1, std::vector<T>(v2.size() + 1, 0));
    for (size_t i = 1; i < matrix.size(); ++i) {
        for (size_t j = 1; j < matrix[0].size(); ++j) {
            if (v1[i - 1] == v2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            } else {
                matrix[i][j] = std::max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }

    std::vector<int> sequence1, sequence2;
    for (int i = matrix.size() - 1, j = matrix[0].size() - 1; i > 0 && j > 0;) {
        if (matrix[i - 1][j] == matrix[i][j]) {
            --i;
        } else if (matrix[i][j - 1] == matrix[i][j]) {
            --j;
        } else {
            sequence1.push_back(i);
            sequence2.push_back(j);
            --i;
            --j;
        }
    }
    return {{sequence1.rbegin(), sequence1.rend()}, {sequence2.rbegin(), sequence2.rend()}};
}
int main() {
    auto seq1 = GetVector<char>();

    auto seq2 = GetVector<char>();
    std::cout << seq1 << std::endl << seq2 << std::endl;
    auto ans = GetMaxSubseq(seq1, seq2);
    std::cout << ans.first.size() << std::endl << ans.first << std::endl << ans.second;

    return 0;
}
