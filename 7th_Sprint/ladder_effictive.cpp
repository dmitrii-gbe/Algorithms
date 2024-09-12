#include <iostream>
#include <vector>

const long base = 1e9 + 7;

int WayCount(int lenght, int steps) {
    std::vector<long long> array(lenght);
    array[0] = 1;
    array[1] = 1;
    for (auto it = array.begin() + 2; it != array.end(); ++it) {
        int to_subtract = ((it - steps - 1) < array.begin() ? 0 : *(it - steps - 1));
        int assign_value = ((((*(it - 1)) * 2) - to_subtract) % base);
        *it = ((assign_value < 0) ? (assign_value + base) : assign_value);
    }
    return *(array.end() - 1);
}

int main() {
    int lenght, steps;
    std::cin >> lenght >> steps;

    std::cout << WayCount(lenght, steps);

    return 0;
}
