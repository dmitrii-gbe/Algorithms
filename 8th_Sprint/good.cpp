
// https :  // contest.yandex.ru/contest/26133/run-report/119501160/
/*
-- ПРИНЦИП РАБОТЫ -
Решение принимает строку и массив слов, на которые ее предполагается разбить.
Строка преобразуется в словарь, где символам в соответствие ставятся их позиции
в исходном тексте. Массив слов преобразуется в префиксное дерево. Затем функция
MapWordsToText проходит дереву и проверяет, есть ли в исходном тексте текущий
символ на позициях, соответствующих позициям следующим за теми, на которых
встречался предыдущий символ. Если нет, то поиск для префиксов в данной части
дерева прекращается. Если же узел был помечен как терминальный, то позиции
текущего символа соответствуют позициям конца этого слова в исходном тексте.
Тогда функции записывает интервалы между начальным и конечным сиволами слова в
массив результатов поиска. Затем функция IsPossibleToSplit определяет, можно ли
строку полностью покрыть последовательностью неперекрывающихся интервалов.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Возможность накрыть строку последоватьностью неперекрывающихся интервалов
определяется тем, есть ли интервал, конец которого соответствует последнему
символу строки, а начало располагается сразу за концом другого интервала.
Значит, чтобы ответить на исходный вопрос, нужно проверить все интеравалы,
индекс конца которых меньше текущего. Таким образом, массив интервалов
необходимо отсортировать по возрастанию индекса конца и последовательно
перебрать, запоминая для каждого индекса конца, есть ли слева последовательность
интервалов, которую можно продолжить текущим. При условии, что найдется такая
последовательность, оканчивающаяся индексом последнего символа в строке,
алгоритм дает положительный ответ.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Временная сложность построения префиксного дерева - О(N), где N - сумма длин
слов. Временная сложность построения индекса позиций символов строки - O(M), где
M - длина строки. Временная сложность поиска слов в строке в худшем случае -
O(NM), где N - сумма длин слов, а M - длина строки. Это возможно если и строка,
и слово состоят из повторения одного символа. Тогда для поиска следующего
символа в строке алгоритм перебирает почти все индексы в строке. Временная
сложность выстраивания последовательности интервалов линейно зависит от числа
интервалов. В худшем случае для каждого слова число вхождений будет сопоставимо
с длиной строки, поэтому в худшем случае сложность этого этапа O(n*M), где n -
число слов, а M - длина строки. Это возможно, если и строка и слова имеют
регулярную структуру. В лучшем случае сложность составит O(n), где n - число
слов, если каждое слово найдется в строке фиксированное (независящее от длины
строки) число раз. Таким образом, сложность алгоритма в худшем случае - O(NM).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Ни один из этапов алгоритма не требует более O(N + M) памяти, где N - суммарная
длина слов, а M - длина строки. Исключение - массив интервалов, который в худшем
случае может может потребовать O(n*M), где n - число слов, а M - длина строки.
*/

#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>

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
    std::queue<size_t> start_points;
    start_points.push(0);
    size_t index = 0;
    bool match = true;
    std::unordered_set<size_t> positions;
    while (!start_points.empty() && index < text.size()) {
        index = start_points.front();
        start_points.pop();
        while (!node->nodes.empty() && index < text.size()) {
            if (node->is_terminal && root.nodes.count(text[index]) && positions.count(index) == 0) {
                start_points.push(index);
                positions.insert(index);
            }

            if (node->nodes.count(text[index])) {
                match = true;
                // std::cout << text[index] << std::endl;
                node = &node->nodes[text[index++]];
            } else {
                match = false;
                break;
            }
        }

        if (node->is_terminal && positions.count(index) == 0) {
            start_points.push(index);
            positions.insert(index);
        } else if (node != &root) {
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
