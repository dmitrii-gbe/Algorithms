#include <iostream>
#include <string>

bool CheckForEvenSymbols(const std::string &s, size_t index) {
  for (; index < s.size(); ++index) {
    if (s[index] % 2 == 0) {
      return true;
    }
  }
  return false;
}

int CompareStrings(const std::string &first, const std::string &second) {
  size_t i = 0;
  size_t j = 0;
  for (; i < first.size() && j < second.size();) {
    while (i < first.size() && first[i] % 2 != 0) {
      ++i;
    }
    while (j < second.size() && second[j] % 2 != 0) {
      ++j;
    }

    if (i == first.size() || j == second.size()) {
      break;
    }

    if (first[i] < second[j]) {
      return -1;
    } else if (second[j] < first[i]) {
      return 1;
    } else {
      ++i;
      ++j;
    }
  }

  if (i < first.size() && CheckForEvenSymbols(first, i)) {
    return 1;
  } else if (j < second.size() && CheckForEvenSymbols(second, j)) {
    return -1;
  } else {
    return 0;
  }
}

int main() {
  std::string first, second;
  std::cin >> first >> second;
  std::cout << CompareStrings(first, second);
  return 0;
}
