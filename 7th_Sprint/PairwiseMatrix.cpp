#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>

struct PairOfWords {
    std::string lhs;
    std::string rhs;
    double distance = 0;
    std::tuple<double&, std::string&, std::string&> Key() { return {distance, lhs, rhs}; }
};

std::ostream& operator<<(std::ostream& out, const PairOfWords& arg) {
    out << arg.lhs << " " << arg.rhs << " " << arg.distance;
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    bool is_first = true;
    for (auto it = v.begin(), end = v.end(); it != end; ++it) {
        if (is_first) {
            out << *it;
            is_first = false;
        } else {
            out << '\n' << *it;
        }
    }
    return out;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<T>>& v) {
    bool is_first = true;
    for (auto it = v.begin(), end = v.end(); it != end; ++it) {
        if (is_first) {
            out << *it;
            is_first = false;
        } else {
            out << '\n' << *it;
        }
    }
    return out;
}

void ProcessString(std::string& s) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + ('a' - 'A');
        } else if ((s[i] >= 33 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64)) {
            s.erase(i);
        }
    }
}
std::vector<std::string> GetText() {
    std::string tmp;
    std::unordered_set<std::string> set;
    while (std::cin >> tmp) {
        ProcessString(tmp);
        set.insert(std::move(tmp));
    }
    return {set.begin(), set.end()};
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

std::vector<PairOfWords> CalculateDistances(const std::vector<std::string>& v) {
    std::vector<PairOfWords> result(v.size() * v.size());
    size_t index = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v.size(); ++j) {
            if (v[i] != v[j]) {
                result[index++] = {
                    v[i], v[j],
                    (double)CalculateDistance(v[i], v[j]) / (double)std::max(v[i].size(), v[j].size())};
            }
        }
    }
    std::sort(result.begin(), result.end(), [](auto& lhs, auto& rhs) { return lhs.Key() < rhs.Key(); });
    std::vector<PairOfWords> tmp(result.size());
    size_t counter = 0;
    std::copy_if(result.begin(), result.end(), tmp.begin(), [&counter](const auto& item) {
        if (item.distance > 0.2 && item.distance < 0.8) {
            ++counter;
            return true;
        } else {
            return false;
        }
    });
    tmp.resize(counter);
    std::swap(tmp, result);
    return result;
}

// std::vector<std::vector<double>> CalculateMatrix(const std::vector<std::string>& v) {
//     std::vector<std::vector<double>> result(v.size(), std::vector<double>(v.size(), 0.0));
//
//     for (size_t i = 0; i < v.size(); ++i) {
//         for (size_t j = 0; j < v.size(); ++j) {
//             result[i][j] = (double)CalculateDistance(v[i], v[j]) / (double)std::max(v[i].size(),
//             v[j].size());
//         }
//     }
//
//     return result;
// }

int main() {
    auto text = GetText();

    std::cout << CalculateDistances(text);

    return 0;
}
