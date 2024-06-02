#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>
#include <stack>

using namespace std;


using namespace std;


void PrintTree(const Node* root){

    if (root == nullptr){
        return;
    }

    const Node* node = root;
    std::stack<const Node*> s;

    while (node->left != nullptr){
        s.push(node);
        node = node->left;
    }

    std::cout << node->value << std::endl;

    PrintTree(node->right);

    while (!s.empty()){
        node = s.top();
        std::cout << node->value << std::endl;
        PrintTree(node->right);
        s.pop();
    } 
}
const Node* FindNext(std::stack<const Node*>& s, const Node* node){

    if (!s.empty() && node == s.top()->left){
        if (node->right != nullptr){
            node = node->right;
            while (node->left != nullptr){
                s.push(node);
                node = node->left;
            }
        }
        else {
            node = s.top();
            s.pop();
        }
    }
    else {
        if (node->right != nullptr){
            node = node->right;
            while (node->left != nullptr){
                s.push(node);
                node = node->left;
            }
        }
        else {

            if (s.empty()){
                return nullptr;
            }

            while (node == s.top()->right){
                node = s.top();
                s.pop();
            }
            node = s.top();
            s.pop();
        }
    }
    return node;
}


void print_range(Node* root, int l, int r) {
    std::stack<const Node*> s;
    const Node* node = root;

    s.push(node);

    while (node != nullptr /*&& node->value != l*/){

        if (node->value >= l){
            node = node->left;
        }
        else {
            node = node->right;
        }

        s.push(node);
    }

    if (s.size() > 1){
        s.pop();
    }

    if (node == nullptr){
        node = s.top();
        s.pop();
    }

    while (node->value < l){
        node = FindNext(s, node);
    }


    while (node != nullptr && node->value <= r){
        std::cout << node->value << std::endl;
        node = FindNext(s, node);
    }
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({nullptr, &node1, 1});
    Node node3({nullptr, nullptr, 8});
    Node node4({nullptr, &node3, 8});
    Node node5({&node4, nullptr, 9});
    Node node6({&node5, nullptr, 10});
    Node node7({&node2, &node6, 5});
    print_range(&node7, -100, 8);
    // expected output: 2 5 8 8
}

void test1() {
    Node node1({nullptr, nullptr, 1});
    Node node2({nullptr, nullptr, 3});
    Node node3({&node1, &node2, 2});
    Node node4({nullptr, nullptr, 3});
    Node node5({&node3, &node4, 3});
    Node node6({nullptr, nullptr, 7});
    Node node7({nullptr, nullptr, 8});
    Node node8({nullptr, nullptr, 8});
    Node node9({nullptr, nullptr, 10});
    Node node10({&node6, &node7, 7});
    Node node11({&node8, &node9, 9});
    Node node12({&node10, &node11, 8});
    Node node13({&node5, &node12, 5});
    print_range(&node13, -100, 800);
    // expected output: 2 5 8 8
}

void PrintFirst(const Node* root){
    if (root == nullptr){
        return;
    }
    std::cout << root->value << '\n';
    PrintFirst(root->left);
    PrintFirst(root->right);
}

void PrintMiddle(const Node* root){
    if (root == nullptr){
        return;
    }
    PrintMiddle(root->left);
    std::cout << root->value << '\n';
    PrintMiddle(root->right);
}

void PrintLast(const Node* root){
    if (root == nullptr){
        return;
    }
    PrintLast(root->left);
    PrintLast(root->right);
    std::cout << root->value << '\n';
}

int main() {
    Node node1({nullptr, nullptr, 1});
    Node node2({nullptr, nullptr, 3});
    Node node3({&node1, &node2, 2});
    Node node4({nullptr, nullptr, 3});
    Node node5({&node3, &node4, 3});
    Node node6({nullptr, nullptr, 7});
    Node node7({nullptr, nullptr, 8});
    Node node8({nullptr, nullptr, 8});
    Node node9({nullptr, nullptr, 10});
    Node node10({&node6, &node7, 7});
    Node node11({&node8, &node9, 9});
    Node node12({&node10, &node11, 8});
    Node node13({&node5, &node12, 5});

    // Node node1({nullptr, nullptr, 1});
    // Node node2({nullptr, nullptr, 3});
    // Node node3({&node1, &node2, 2});
    // Node node4({nullptr, nullptr, 5});
    // Node node5({&node3, &node4, 4});
    // Node node6({nullptr, nullptr, 7});
    // Node node8({nullptr, nullptr, 9});
    // Node node9({nullptr, nullptr, 11});
    // Node node11({&node8, &node9, 10});
    // Node node12({&node6, &node11, 8});
    // Node node13({&node5, &node12, 6});

    std::cout << "PrintFirst()" << std::endl;
    PrintFirst(&node13);

    std::cout << "PrintMiddle()" << std::endl;
    PrintMiddle(&node13);

    std::cout << "PrintLast()" << std::endl;
    PrintLast(&node13);
}

#endif
