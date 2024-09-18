#include <stdio.h>

void PrintArray(int *array, size_t size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", *array);
        ++array;
    }
    printf("%c", '\n');
}

int *GetArray(size_t size) {
    int array[size];
    for (size_t i = 0; i < size; ++i) {
        *array = i;
        ++array;
    }
    PrintArray(array, size);
    return array;
}

int main() {
    int ptr * = GetArray(12);
    PrintArray(ptr, 12);
}