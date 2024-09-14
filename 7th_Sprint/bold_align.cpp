#include <strings.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
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

std::string GetVector() {
    std::string result;
    std::getline(std::cin, result);
    return result;
}

std::pair<std::vector<int>, std::vector<int>> GetMaxSubseq(const std::string& v1, const std::string& v2) {
    std::vector<int> result;
    std::vector<std::vector<int>> matrix(v1.size() + 1, std::vector<int>(v2.size() + 1, 0));
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
            sequence1.push_back(i - 1);
            sequence2.push_back(j - 1);
            --i;
            --j;
        }
    }
    return {{sequence1.rbegin(), sequence1.rend()}, {sequence2.rbegin(), sequence2.rend()}};
}

void BoldString(std::string& orig, const std::vector<int>& span) {
    std::string left_tag = "<span style=\"color:red\">";
    std::string right_tag = "</span>";

    std::string result;
    result.reserve(orig.size());
    size_t index = 0;
    for (size_t i = 0; i < span.size(); ++i) {
        while (index != (size_t)span[i] && index < orig.size()) {
            result += orig[index++];
        }
        result += left_tag;
        while (span[i] == span[std::min(span.size() - 1, i + 1)] - 1) {
            result += orig[index++];
            ++i;
        }
        result += orig[index++];
        result += right_tag;
    }
    orig = std::move(result);
}

int main() {
    auto seq1 = GetVector();

    auto seq2 = GetVector();

    auto ans = GetMaxSubseq(seq1, seq2);
    BoldString(seq1, ans.first);
    BoldString(seq2, ans.second);
    std::cout << seq1 << '\n' << seq2 << '\n';
    return 0;
}
