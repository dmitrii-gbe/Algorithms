#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> ParseSequence(std::string_view s){
    if (s.empty()){
        return {};
    }
    std::vector<std::string> result;
    std::string tmp;

    for (size_t i = 0; i < s.size(); ++i){
        if (s[i] != '<'){
            tmp += s[i];
        }
        if (s[i] == '<'){
            if (!tmp.empty()){
                result.push_back(tmp);
                tmp.clear();
            }

            std::string tmp1;
            tmp1 += s[i];

            for (size_t j = i + 1; j < s.size(); ++j){
                if (s[j] != '>'){
                    tmp1 += s[j];
                }
                else {
                    tmp1 += s[j];
                    result.push_back(tmp1);
                    i = j;
                    break;
                }
            }
        }

    }
    return result;

}

std::string GetResult(const std::vector<std::string>& v){

    std::string result;
    size_t position = 0;
    bool empty = true;

    for (size_t i = 0; i < v.size(); ++i){

        if (v[i] != "<delete>" && v[i] != "<bspace>" && v[i] != "<left>" && v[i] != "<right>"){
            result.insert((empty ? position : position + 1), v[i]);
            position += (empty ? v[i].size() - 1 : v[i].size());
            empty = false;
        }

        if (v[i] == "<bspace>" && position >= 0){
            result.erase(result.begin() + position);
            --position;
        }

        if (v[i] == "<delete>" && position + 1 <= result.size() - 1){
            result.erase(result.begin() + position + 1);
        }

        if (v[i] == "<right>" && position < result.size() - 2){
            ++position;
        }
        if (v[i] == "<left>" && position > 0){
            --position;
        }
    }
    return result;
}

int main(){

std::string query;
std::string press_sequence;
std::getline(std::cin, query);
std::getline(std::cin, press_sequence);

std::vector<std::string> v = ParseSequence(press_sequence);
std::cout << ((GetResult(v) == query) ? "Yes" : "No");




    return 0;
}