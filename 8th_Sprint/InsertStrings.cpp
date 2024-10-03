#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct StrPos {
  std::string s;
  size_t pos = 0;
  StrPos() = default;
  StrPos(const std::string &s_, size_t pos_) : s(s_), pos(pos_) {}
};

std::vector<StrPos> Read(int n) {
  std::vector<StrPos> v(n);

  for (int i = 0; i < n; ++i) {
    StrPos item;
    std::cin >> item.s >> item.pos;
    v[i] = item;
  }
  std::sort(v.begin(), v.end(),
            [](const auto &lhs, const auto &rhs) { return lhs.pos < rhs.pos; });
  return v;
}

std::string Insert(const std::string &s, const ::std::vector<StrPos> &v) {
  size_t size = 0;
  for (auto &item : v) {
    size += item.s.size();
  }
  size += s.size();
  std::string result(size, ' ');
  size_t index_dest = 0;
  size_t index_orig = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    while (index_orig < v[i].pos && index_orig < s.size()) {
      result[index_dest++] = s[index_orig++];
    }
    for (char c : v[i].s) {
      result[index_dest++] = c;
    }
  }
  while (index_orig < s.size()) {
    result[index_dest++] = s[index_orig++];
  }
  return result;
}

int main() {
  std::string to;
  std::getline(std::cin, to);
  int count = 0;
  std::cin >> count;
  auto v = Read(count);
  std::cout << Insert(to, v);
  return 0;
}
