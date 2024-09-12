#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, std::vector<int> v) {
    bool is_first = true;
    for (size_t i = 0; i < v.size(); ++i) {
        if (is_first) {
            out << v[i];
            is_first = false;
        } else {
            out << " " << v[i];
        }
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>> v) {
    bool is_first = true;
    for (size_t i = 0; i < v.size(); ++i) {
        if (is_first) {
            out << v[i];
            is_first = false;
        } else {
            out << '\n' << v[i];
        }
    }
    return out;
}

std::vector<std::vector<int>> ReadField(int rows, int cols) {
    std::vector<std::vector<int>> field(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char c = 0;
            std::cin >> c;
            field[i][j] = c - '0';
        }
    }
    return field;
}

size_t GetMaxFlowers(const std::vector<std::vector<int>> v) {
    std::vector<std::vector<int>> field(v.size(), std::vector<int>(v[0].size(), 0));
    for (int i = v.size() - 1; i >= 0; --i) {
        for (size_t j = 0; j < v[0].size(); ++j) {
            field[i][j] = std::max(((j - 1) < 0 ? 0 : field[i][j - 1]),
                                   ((i + 1) >= (int)v.size() ? 0 : field[i + 1][j])) +
                          v[i][j];
        }
    }
    return field[0][field[0].size() - 1];
}

int main() {
    int rows, cols;

    std::cin >> rows >> cols;

    auto field = ReadField(rows, cols);

    std::cout << GetMaxFlowers(field);

    return 0;
}
