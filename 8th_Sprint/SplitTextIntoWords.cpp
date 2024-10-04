// https://contest.yandex.ru/contest/26133/run-report/119655549/
/*
-- ПРИНЦИП РАБОТЫ -
Решение принимает строку и массив слов, на которые ее предполагается
разбить. Массив слов преобразуется в префиксное дерево. Функция
IsPossibleToSplit проходит по строке дереву и проверяет, есть ли для
текущей стартовой позиции слова в дереве, соответствующие символам строки.
Если есть, то в набор стартовых позиций вносятся индексы символов,
следующих за индексами последних символов совпавших слов. Цикл повторяется
пока либо не будет достигнут конец строки либо, набор стартовых позиций не
опустеет. Если был достигнут конец строки и последнее слово было найдено в
строке целиком функция возвращает true.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Возможность накрыть строку последоватьностью неперекрывающихся слов
определяется тем, есть ли слово, конец которого соответствует последнему
символу строки, а начало располагается сразу за концом другого слова.
Значит, чтобы ответить на исходный вопрос, нужно, начиная с начала строки
попытаться последовательно вписать в нее строки и данного набора так, чтобы
начало следующего слова обязательно следовало за концом предыдущего.
При условии, что удастся это сделать вплоть до конца строки, алгоритм дает
положительный ответ.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Временная сложность построения префиксного дерева - О(N), где N - сумма
длин слов. Временная сложность прохода по строке в худшем случае составит
O(M*L), где L - длина самого длинного слова, a M - длина строки. Худший
случай наступает, если строка и набор слов состоят из повторения одного
символа, и слова являются префиксами друго друга. Тогда каждый индекс в
строке будет начальным для прохода по префиксному дереву. Таким образом,
сложность алгоритма в худшем случае - O(ML + N).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Префиксное дерево требует более O(N) памяти, где N -
суммарная длина слов. Таким образом, алгоритм требует O(N + M) памяти, где
N - суммарная длина слов, а M - длина строки.
*/

#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>

struct Interval {
    int start = 0;
    int end = 0;
};

struct Node {
    std::unordered_map<char, Node> nodes;
    bool is_terminal = false;
};

void AddStringToPrefixTree(std::string_view word, Node& prefix_tree) {
    Node* node = &prefix_tree;
    for (char c : word) {
        node = &node->nodes[c];
    }
    node->is_terminal = true;
}

Node BuildPrefixTree() {
    int count = 0;
    std::cin >> count;
    std::string s;
    Node prefix_tree;
    while (count != 0) {
        std::cin >> s;
        --count;
        AddStringToPrefixTree(s, prefix_tree);
    }
    return prefix_tree;
}

bool IsPossibleToSplit(const std::string& text, Node& root) {
    Node* node = &root;
    size_t index = 0;
    bool match = true;
    std::set<size_t> positions;
    positions.insert(index);
    while (!positions.empty() && index < text.size()) {
        index = *positions.begin();
        positions.erase(positions.begin());
        while (!node->nodes.empty() && index < text.size()) {
            if (node->is_terminal) {
                positions.insert(index);
            }

            if (node->nodes.count(text[index])) {
                match = true;
                node = &node->nodes[text[index++]];
            } else {
                match = false;
                break;
            }
        }

        if (node->is_terminal) {
            positions.insert(index);
        } else {
            match = false;
        }

        node = &root;
    }

    return index == text.size() && match;
}

int main() {
    std::string text;
    std::cin >> text;
    Node prefix_tree = BuildPrefixTree();
    std::cout << (IsPossibleToSplit(text, prefix_tree) ? "YES" : "NO");
    return 0;
}
