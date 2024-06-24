#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

enum class WayType {
    NONE,
    R,
    B
};

WayType operator+(WayType lhs, WayType rhs){
    return (lhs == rhs) ? lhs : WayType::NONE;
}

std::vector<std::vector<WayType>> GetEdgeMatrix(){
    int cities = 0;
    std::cin >> cities;
    std::vector<std::vector<WayType>> matrix(cities, std::vector<WayType>(cities, WayType::NONE));
    
    for (int i = 0; i < cities - 1; ++i){
        std::string s;
        std::cin >> s;
        for (int j = i + 1; j < cities; ++j){
            matrix[i][j] = (s[j - i - 1] == 'B') ? WayType::B : WayType::R;
        }
    }
    return matrix;
}

bool CheckIfMapIsOptimal(const std::vector<std::vector<WayType>>& map){
    for (int i = (int)map.size() - 2, j = 1; i >= 0; --i, ++j){
            for (int left_col = i + 1, bottom_row = i + 1; left_col < j; ++left_col, ++bottom_row){
                WayType sum = map[i][left_col] + map[bottom_row][j];
                if (sum != map[i][j] && sum != WayType::NONE){
                    return false;
                }
            }
    }

    return true;
}

int main(){

    auto map = GetEdgeMatrix();

    std::cout << (CheckIfMapIsOptimal(map) ? "YES" : "NO") << '\n';

    return 0;
}