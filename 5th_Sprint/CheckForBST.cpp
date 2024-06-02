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

template <typename T>
bool CheckFor(const Node* root, int value, T comparator){
    if (root == nullptr){
        return true;
    }

    if (!comparator(root->value, value)){
        return false;
    }

    return CheckFor(root->left, value, comparator) && CheckFor(root->right, value, comparator);
}

bool Internal(const Node* root, const Node* lower = nullptr, const Node* upper = nullptr){
    if (root == nullptr){
        return true;
    }

    if ((upper != nullptr && root->value >= upper->value) || (lower != nullptr && root->value <= lower->value)){
        return false;
    }

    return Internal(root->left, lower, root) && Internal(root->right, root, upper);
}

bool Solution(const Node* root) {
  return Internal(root);
} 


// bool Solution(const Node* root) {
//     if (root == nullptr){
//         return true;
//     }

//     int value = root->value;

//     if (!(CheckFor(root->left, value, std::less<int>{}) && CheckFor(root->right, value, std::greater<int>{}))){
//         return false;
//     }

//     return Solution(root->left) && Solution(root->right);
// } 


#ifndef REMOTE_JUDGE
void test() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
    {
      Node node1({5, nullptr, nullptr});
      Node node2({3, nullptr, nullptr});
      Node node3({2, &node1, &node2});
      assert(!Solution(&node3));
    }
}


int main() {
  test();
}
#endif