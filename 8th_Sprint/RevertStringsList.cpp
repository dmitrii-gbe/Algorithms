#include <iostream>
#include <string>
#include <vector>

template <typename T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> v) {
  bool is_first = true;
  for (const auto &item : v) {
    if (is_first) {
      out << item;
      is_first = false;
    } else {
      out << " " << item;
    }
  }
  return out;
}

template <typename T> std::vector<T> GetVector() {
  std::vector<T> result;

  std::string query;
  std::getline(std::cin, query);

  std::string tmp;

  for (char c : query) {
    if (c != ' ') {
      tmp += c;
      continue;
    }
    if (c == ' ' && !tmp.empty()) {
      result.push_back(tmp);
      tmp.clear();
    }
  }
  result.push_back(tmp);

  return result;
}

int main() {
  auto v = GetVector<std::string>();
  std::vector<std::string> rev = {v.rbegin(), v.rend()};
  std::cout << rev;
  return 0;
}
