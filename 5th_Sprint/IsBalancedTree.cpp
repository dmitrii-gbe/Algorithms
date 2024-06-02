#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

int Internal(const Node* node, bool& b){
    if (!node || !b){
        return 0;
    }

    int l = Internal(node->left, b);
    int r = Internal(node->right, b);
    
    if (std::abs(l - r) > 1){
        b = false;
    }

    return std::max(l, r) + 1;


}

bool Solution(const Node* root) {
    bool b = true;
    Internal(root, b);
    return b;
}


#ifndef REMOTE_JUDGE
void test() {
{
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    assert(Solution(&node5));
}
{
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    Node node6({18, &node5, nullptr});
    assert(!Solution(&node6));
}
}

int main() {
  test();
}
#endif
