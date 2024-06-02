#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif


int SiftDown(std::vector<int>& heap, int idx) {

    while (idx * 2 < (int)heap.size()){

        int left = 2 * idx;
        int right = left + 1;

        bool left_is_greater = (right < (int)heap.size()) ? heap[left] > heap[right] : true;

        if (left_is_greater && heap[idx] < heap[left]){
            std::swap(heap[idx], heap[left]);
            idx = left;
            continue;
        }

        if (!left_is_greater && heap[idx] < heap[right]){
            std::swap(heap[idx], heap[right]);
            idx = right;
            continue;
        }

        break;

    }

    return idx;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}


int main() {
    test();
}
#endif