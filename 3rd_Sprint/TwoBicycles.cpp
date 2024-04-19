#include <iostream>

#include <vector>
#include <string>


// #include <utility>
// #include <chrono>
// #include "log_duration"
// #include <unordered_map>
// #include <unordered_set>
// #include <map>
// #include <set>
#include <algorithm>

int main(){

    int day_count = 0;
    std::cin >> day_count;

    std::vector<int> days(day_count);

    for (int i = 0; i < day_count; ++i){
        std::cin >> days[i];
    }

    int target = 0;
    std::cin >> target;

    auto pair_single = std::equal_range(days.begin(), days.end(), target);
    auto pair_two = std::equal_range(days.begin(), days.end(), target * 2);
    std::cout << ((pair_single.first != days.end()) ? (pair_single.first - days.begin() + 1) : -1) << " " << ((pair_two.first != days.end()) ? (pair_two.first - days.begin() + 1) : -1) << '\n';


    return 0;
}