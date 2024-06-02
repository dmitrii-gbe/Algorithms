//https://contest.yandex.ru/contest/24810/run-report/114877790/
/*
-- ПРИНЦИП РАБОТЫ --
Функция remove принимает корень дерева и ключ, узел с которым нужно удалить. Она ищет искомый узел и, если не находит, возвращает корень неизмененного дерева.
В противном случае, если узел найден, она выбирает элемент на замену с помощью функции GetReplacement. В качестве замены выбирается самый большой (самый правый) элемент
левого поддерева удаляемого узла. Если левого поддерева нет, то замена - первый узел правого поддерева. Затем образуются новые связи между узлами, благодаря чему целевой узел
удаляется, и сохраняются целостность и свойства дерева.


-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
Корректность алгоритма строится на том, чтобы правильно подобрать узел на замену и образовать новые связи между узлами. Чтобы сохранить свойства бинарного дерева поиска, 
заменяющий узел должен быть больше всех элементов левого поддерева и меньше всех правого. Этому требованию удовлетворяет самый правый узел левого поддерева и самый левый элемент в правом поддереве.
В настоящей реализации используется первый вариант. Если узел-замена найден, в него записываются указатели на левого и правого потомка удаляемого узла, а в узел-предок удаляемого узла записывается
указатель на заменяющий узел. В случае, если у удаляемого узла нет левого поддерева, узел просто удаляется и образуется новая связь между родительским узлом и правым потомком удаляемого 
узла. В случа, если удаляемый узел - корень дерева, замещающий узел становится новым корнем дерева.
Для поддержания свойств дерева изменяются связи между узлами и при переносе замещающего узла из своего исходного местоположения в новое. А именно, удаляется связь между замещающим узлом и его
предком и образуется новая связь между предком и левым поддеревом замещающего узла.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
Временная сложность определяется временем на поиск узла, который нужно удалить, и на поиск узла на замену. Обе величины не превышают O(H), где H - высота дерева. Таким
образом, временная сложность всего алгоритма - O(H).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
Дополнительная память требуется, чтобы хранить указатели на предыдущий узел (при переборе узлов), узел замену и узел, подлежащий удалению. Таким образом, алгоритм требует O(1)
дополнительной памяти.
*/

#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>

Node* GetReplacement(Node* root){
    Node* node = root->left;
    Node* prev = nullptr;
    while (node->right){
        prev = node;
        node = node->right;
    }

    if (prev){
        prev->right = node->left;
        node->left = nullptr;
    }
    else {
        root->left = node->left;
        node->left = nullptr;
    }

    return node;
}

void Replace(Node** root_ptr, Node* node, Node* prev, Node* replacement){
    if (prev && node == prev->right){
        prev->right = replacement;
    }

    else if (prev && node == prev->left) {
        prev->left = replacement;
    }

    else {
        *root_ptr = replacement;
    }
}

Node* remove(Node* root, int key) {
    Node* node = root;
    Node* prev = nullptr;

    while (node && node->value != key){
        prev = node;
        node = (key > node->value) ? node->right : node->left;
    }

    if (!node){
        return root;
    }

    Node* replacement = (!node->left) ? nullptr : GetReplacement(node);

    if (replacement){

        replacement->left = node->left;
        replacement->right = node->right;

        Replace(&root, node, prev, replacement);

    }

    else {

        Replace(&root, node, prev, node->right);

    }

    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
    test();
}
#endif