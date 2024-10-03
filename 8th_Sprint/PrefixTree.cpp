#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Node {
    std::unordered_map<char, Node> nodes;
    std::string word;
};

void AddString(std::string_view word, size_t index, Node& prefix_tree) {
    if (index == word.size() - 1) {
        prefix_tree.nodes[word[index]].word = word;
    } else {
        AddString(word, index + 1, prefix_tree.nodes[word[index]]);
    }
}

void BuildTree(Node& prefix_tree, const std::vector<std::string>& words) {
    for (const auto& item : words) {
        AddString(item, 0, prefix_tree);
    }
}

void PrintTree(Node& prefix_tree) {
    if (!prefix_tree.word.empty()) {
        std::cout << prefix_tree.word << std::endl;
    }
    for (auto it = prefix_tree.nodes.begin(); it != prefix_tree.nodes.end(); ++it) {
        std::cout << it->first << " ";
        PrintTree(it->second);
    }
}

int main() {
    Node prefix_tree;
    int count = 0;
    std::cin >> count;
    std::string s;
    while (count != 0) {
        std::cin >> s;
        --count;
        AddString(s, 0, prefix_tree);
    }
    PrintTree(prefix_tree);
    return 0;
}
