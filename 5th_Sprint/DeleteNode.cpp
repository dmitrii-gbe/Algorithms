//https://contest.yandex.ru/contest/24810/run-report/114815634/
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

        if (prev && node == prev->right){
            prev->right = replacement;
        }

        else if (prev && node == prev->left) {
            prev->left = replacement;
        }

        else {
            root = replacement;
        }
    }
    else {
        
        if (prev && node == prev->left){
            prev->left = node->right;
        }

        else if (prev && node == prev->right){
            prev->right = node->right;
        }

        else {
            root = node->right;
        }
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