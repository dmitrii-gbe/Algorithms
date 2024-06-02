#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif


int siftUp(std::vector<int>& heap, int idx) {
    while (idx != 1){
        if (heap[idx / 2] < heap[idx]){
            std::swap(heap[idx / 2], heap[idx]);
            idx /= 2;
        }
        else {
            break;
        }
    }

    return idx;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 6, 8, 3, 15, 7};
    assert(siftUp(sample, 5) == 1);
}


int main() {
    test();
}
#endif