#include <cstddef>
#include <iostream>

bool CompareStrings(const std::string &s1, size_t i, const std::string &s2,
                    size_t j) {
  while (i < s1.size() && j < s2.size() && s1[i++] == s2[j++]) {
  }
  return i == s1.size() && j == s2.size();
}

bool IsEqual(const std::string &s1, const std::string &s2) {
  int shift = s1.size() - s2.size();
  size_t i = 0;
  size_t j = 0;
  while (s1[i] == s2[j] && i < s1.size() && j < s2.size()) {
    ++i;
    ++j;
  }

  if (i == s1.size() && j == s2.size()) {
    return true;
  }

  if ((i == s1.size() && s2.size() - i == 1) ||
      (j == s2.size() && s1.size() - j == 1)) {
    return true;
  } else if (shift == 1) {
    return CompareStrings(s1, i + 1, s2, j);
  } else if (shift == -1) {
    return CompareStrings(s1, i, s2, j + 1);
  } else if (shift == 0 && CompareStrings(s1, i + 1, s2, j + 1)) {
    return true;
  } else {
    return false;
  }
}

int main() {

  std::string s1, s2;
  std::cin >> s1 >> s2;

  std::cout << (IsEqual(s1, s2) ? "OK" : "FAIL");

  return 0;
}
