#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>

bool CheckSequence(const std::map<std::pair<int, int>, char>& field
                    , const std::pair<int, int>& p, char c, int field_size){
    
    std::set<std::pair<int, int>> left_diag;
    std::set<std::pair<int, int>> right_diag;

    for (int i = 0; i <= field_size; ++i){
        std::pair<int, int> tmp(i, i);
        left_diag.insert(tmp);
    }

    for (int i = 0, j = field_size; i <= field_size; ++i, --j){
        std::pair<int, int> tmp(i, j);
        right_diag.insert(tmp);
    }
    
    bool first_found = false;
    int counter_row = 0;
    for (int i = p.second - 4; i < p.second + 5; ++i){
        std::pair<int, int> key(p.first, i);
        if (!field.count(key) && !first_found){
            continue;
        }
        if ((!field.count(key) && first_found) || (field.at(key) != c && first_found)){
            first_found = false;
            counter_row = 0;
            continue;
        }
        if (field.at(key) == c) {
            ++counter_row;
            first_found = true;
            if (counter_row == 5){
                break;
            }
        }
    }

    first_found = false;
    int counter_col = 0;
    for (int i = p.first - 4; i < p.first + 5; ++i){
        std::pair<int, int> key(i, p.second);
        if (!field.count(key) && !first_found){
            continue;
        }
        if ((!field.count(key) && first_found) || (field.at(key) != c && first_found)){
            first_found = false;
            counter_col = 0;
            continue;
        }
        if (field.at(key) == c) {
            ++counter_col;
            first_found = true;
            if (counter_col == 5){
                break;
            }
        }
    }

    first_found = false;
    int counter_left = 0;
    if (left_diag.count(p)){
        for (int i = p.first - 4, j = p.second - 4; i < p.first + 5; ++i, ++j){
            std::pair<int, int> key(i, j);
            if (!field.count(key) && !first_found){
                continue;
            }
            if ((!field.count(key) && first_found) || (field.at(key) != c && first_found)){
                first_found = false;
                counter_left = 0;
                continue;
            }
            if (field.at(key) == c) {
                ++counter_left;
                first_found = true;
                if (counter_left == 5){
                    break;
                }
            }
        }        
    }

    first_found = false;
    int counter_right = 0;
    if (right_diag.count(p)){
        for (int i = p.first + 4, j = p.second - 4; i < p.first - 5; ++i, ++j){
            std::pair<int, int> key(i, j);
            if (!field.count(key) && !first_found){
                continue;
            }
            if ((!field.count(key) && first_found) || (field.at(key) != c && first_found)){
                first_found = false;
                counter_right = 0;
                continue;
            }
            if (field.at(key) == c) {
                ++counter_right;
                first_found = true;
                if (counter_right == 5){
                    break;
                }
            }
        }        
    }

    return counter_row >= 5 || counter_col >= 5 || counter_left >= 5 || counter_right >= 5;
}

void Play(){
    int field_size = 0;
    int size = 0;
    std::cin >> size;
    if (size == 0){
        std::cout << "Draw";
        return;
    }
    std::vector<std::pair<int, int>> result;
    result.reserve(size);
    std::map<std::pair<int, int>, char> field;
    std::pair<int, int> tmp;

    for (int i = 0; i < size; ++i){
        std::cin >> tmp.first >> tmp.second;
        if (field_size < std::max(tmp.first, tmp.second)){
            field_size = std::max(tmp.first, tmp.second);
        }
        result.push_back(tmp);
    }
    int i = 0;
    auto pair = result.begin();
    bool ended_game = false;
    for (; pair != result.end(); ++pair){
        char c = (i % 2 == 0) ? 'x' : '0';
        field[*pair] = c;
        if (CheckSequence(field, *pair, c, field_size)){
            ended_game = true;
            if (pair != std::prev(result.end())){
                std::cout << "Inattention";
            }
            else {
                std::cout << ((i % 2 == 0) ? "First" : "Second");
            }
            break;
        }
        ++i;
    }
    if (!ended_game){
        std::cout << "Draw";
    }
    
}

int main(){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Play();

    //std::cout << field_size << " * " << field_size << "\n";


    return 0;
}