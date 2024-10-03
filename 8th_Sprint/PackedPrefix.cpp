// https://contest.yandex.ru/contest/26133/run-report/119577789/
/*
-- ПРИНЦИП РАБОТЫ --
Решение принимает массив ЗС, после чего с помошью функций UnPack и MultiplyStringByCount рекурсивно ее
распаковывает. Затем функция ResizePrefix ищет общий префикс распакованных строк.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
На вход подается строка, запакованная рекурсивно, то есть при распаковке ЗС может снова получиться
запакованная строка. Поэтому алгоритм рекурсивно доходит до максимальной уровня упаковки, после чего
последательно для каждого уровня распаковывает содержимое, получая, таким образом исходные неупаковованные
строки, для которых затем вычисляется общий префикс максимальной длины.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Распаковка строки имеет сложность O(d*N), где d - число вложенных уровней упаковки, а N - длина распакованной
строки. Поиск общего префикса имеет сложность O(n * M), где n - число строк, а M - длина самой короткой
распакованной строки. В худшем случае сложность этого шага составит O(U), где U - совокупная длина
распакованных строк. Таким образом, общая сложность - не более O(P^2) + O(U), где P и U - совокупная длина
запакованных и распакованных строк, соответственно.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Алгоритм требует не более O(L) памяти, где L - длина самой длинной распакованной строки.
*/

#include <algorithm>
#include <iostream>
#include <string>

std::string MultiplyStringByCount(int n, const std::string &str) {
    std::string result;
    result.reserve(str.size() * n);
    while (n != 0) {
        result += str;
        --n;
    }
    return result;
}

size_t FindClosingBracket(const std::string &str, size_t start_index) {
    int brackets_count = 1;
    ++start_index;
    while (brackets_count != 0) {
        if (str[start_index] == '[') {
            ++brackets_count;
        } else if (str[start_index] == ']') {
            --brackets_count;
        }
        ++start_index;
    }
    return start_index;
}

std::string UnPack(const std::string &str) {
    std::string result;
    for (size_t i = 0; i < str.size();) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result += str[i++];
        } else if (str[i] >= '0' && str[i] <= '9') {
            size_t shift = FindClosingBracket(str, i + 1) - i;
            result += MultiplyStringByCount(str[i] - '0', UnPack(str.substr(i + 2, shift - 3)));
            i += shift;
        }
    }
    return result;
}

void ResizePrefix(std::string &prefix, const std::string_view s) {
    size_t i = 0;
    while (prefix[i] == s[i] && i < std::min(prefix.size(), s.size())) {
        ++i;
    }
    prefix.resize(i);
}

int main() {
    int count = 0;
    std::cin >> count;
    std::string s;
    std::cin >> s;
    --count;
    std::string prefix = UnPack(s);
    while (count != 0) {
        std::cin >> s;
        --count;
        s = UnPack(s);
        ResizePrefix(prefix, s);
    }
    std::cout << prefix;
    return 0;
}
