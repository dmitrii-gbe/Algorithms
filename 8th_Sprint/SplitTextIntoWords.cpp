// https :  // contest.yandex.ru/contest/26133/run-report/119501160/
/*
-- ПРИНЦИП РАБОТЫ -
Решение принимает строку и массив слов, на которые ее предполагается разбить. Строка преобразуется в словарь,
где символам в соответствие ставятся их позиции в исходном тексте. Массив слов преобразуется в префиксное
дерево. Затем функция MapWordsToText проходит дереву и проверяет, есть ли в исходном тексте текущий символ на
позициях, соответствующих позициям следующим за теми, на которых встречался предыдущий символ. Если нет, то
поиск для префиксов в данной части дерева прекращается. Если же узел был помечен как терминальный, то позиции
текущего символа соответствуют позициям конца этого слова в исходном тексте. Тогда функции записывает
интервалы между начальным и конечным сиволами слова в массив результатов поиска. Затем функция
IsPossibleToSplit определяет, можно ли строку полностью покрыть последовательностью неперекрывающихся
интервалов.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Возможность накрыть строку последоватьностью неперекрывающихся интервалов определяется тем, есть ли интервал,
конец которого соответствует последнему символу строки, а начало располагается сразу за концом другого
интервала. Значит, чтобы ответить на исходный вопрос, нужно проверить все интеравалы, индекс конца которых
меньше текущего. Таким образом, массив интервалов необходимо отсортировать по возрастанию индекса конца и
последовательно перебрать, запоминая для каждого индекса конца, есть ли слева последовательность интервалов,
которую можно продолжить текущим. При условии, что найдется такая последовательность, оканчивающаяся индексом
последнего символа в строке, алгоритм дает положительный ответ.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Временная сложность построения префиксного дерева - О(N), где N - сумма длин слов.
Временная сложность построения индекса позиций символов строки - O(M), где M - длина строки.
Временная сложность поиска слов в строке в худшем случае - O(NM), где N - сумма длин слов, а M - длина строки.
Это возможно если и строка, и слово состоят из повторения одного символа. Тогда для поиска следующего символа
в строке алгоритм перебирает почти все индексы в строке. Временная сложность выстраивания последовательности
интервалов линейно зависит от числа интервалов. В худшем случае для каждого слова число вхождений будет
сопоставимо с длиной строки, поэтому в худшем случае сложность этого этапа O(n*M), где n - число слов, а M -
длина строки. Это возможно, если и строка и слова имеют регулярную структуру. В лучшем случае сложность
составит O(n), где n - число слов, если каждое слово найдется в строке фиксированное (независящее от длины
строки) число раз. Таким образом, сложность алгоритма в худшем случае - O(NM).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Ни один из этапов алгоритма не требует более O(N + M) памяти, где N - суммарная длина слов, а M - длина
строки. Исключение - массив интервалов, который в худшем случае может может потребовать O(n*M), где n - число
слов, а M - длина строки.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Interval {
    int start = 0;
    int end = 0;
};

struct Node {
    std::unordered_map<char, Node> nodes;
    bool is_terminal = false;
};

std::unordered_map<char, std::unordered_set<int>> GetTextAsIndex(std::string_view text) {
    std::unordered_map<char, std::unordered_set<int>> index;
    for (size_t i = 0; i < text.size(); ++i) {
        index[text[i]].insert(i);
    }
    return index;
}

void AddStringToPrefixTree(std::string_view word, size_t index, Node &prefix_tree) {
    if (index == word.size()) {
        prefix_tree.is_terminal = true;
    } else {
        AddStringToPrefixTree(word, index + 1, prefix_tree.nodes[word[index]]);
    }
}

Node BuildPrefixTree() {
    int count = 0;
    std::cin >> count;
    std::string s;
    Node prefix_tree;
    while (count != 0) {
        std::cin >> s;
        --count;
        AddStringToPrefixTree(s, 0, prefix_tree);
    }
    return prefix_tree;
}

std::unordered_set<int> RecalculatePositions(const std::unordered_set<int> &lhs,
                                             const std::unordered_set<int> &rhs) {
    if (lhs.empty()) {
        return rhs;
    }
    std::unordered_set<int> new_positions;
    for (int i : lhs) {
        if (rhs.count(i + 1)) {
            new_positions.insert(i + 1);
        }
    }
    return new_positions;
}

void MapWordsInternal(const std::unordered_map<char, std::unordered_set<int>> &text_index,
                      const Node &prefix_tree, const std::unordered_set<int> &positions, int counter,
                      std::vector<Interval> &result) {
    if (prefix_tree.is_terminal) {
        for (int position : positions) {
            result.push_back({position - counter + 1, position});
        }
    }

    for (auto it = prefix_tree.nodes.begin(), end = prefix_tree.nodes.end(); it != end; ++it) {
        if (text_index.count(it->first)) {
            std::unordered_set<int> new_positions = RecalculatePositions(positions, text_index.at(it->first));
            if (!new_positions.empty()) {
                MapWordsInternal(text_index, prefix_tree.nodes.at(it->first), new_positions, counter + 1,
                                 result);
            }
        }
    }
}

std::vector<Interval> MapWordsToText(const std::unordered_map<char, std::unordered_set<int>> &text_index,
                                     const Node &prefix_tree) {
    std::vector<Interval> result;
    MapWordsInternal(text_index, prefix_tree, std::unordered_set<int>{}, 0, result);
    std::sort(result.begin(), result.end(),
              [](const auto &lhs, const auto &rhs) { return lhs.end < rhs.end; });
    return result;
}

bool IsPossibleToSplit(const std::string &text, const std::vector<Interval> &intervals) {
    std::vector<bool> array(text.size(), false);
    for (int i = 0; i < (int)intervals.size(); ++i) {
        array[intervals[i].end] =
            array[intervals[i].end] || (intervals[i].start == 0 ? true : array[intervals[i].start - 1]);
    }
    return array.back();
}

int main() {
    std::string text;
    std::cin >> text;
    auto text_index = GetTextAsIndex(text);
    Node prefix_tree = BuildPrefixTree();
    std::cout << (IsPossibleToSplit(text, MapWordsToText(text_index, prefix_tree)) ? "YES" : "NO");
    return 0;
}
