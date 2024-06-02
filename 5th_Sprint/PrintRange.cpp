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

void PrintTree(const Node* root, int r){

    if (root == nullptr){
        return;
    }
    
    if (root->value > r){
        PrintTree(root->left, r);
    }

    else {
        PrintTree(root->left, r);
        std::cout << root->value << '\n';
        PrintTree(root->right, r);
    }
}

void print_range(const Node* root, int l, int r) {
    if (root == nullptr){
        return;
    }
    if (root->value >= l){
        print_range(root->left, l, r);
        if (root->value <= r){
            std::cout << root->value << '\n';
            PrintTree(root->right, r);
        }
    }
    else {
        print_range(root->right, l, r);
    }
}

#ifndef REMOTE_JUDGE


int main() {

}
#endif