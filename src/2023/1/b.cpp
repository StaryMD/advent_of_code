#include <cctype>
#include <string>
#include <string_view>
#include <unordered_map>

#include "solution.hpp"

int GetDigit(const std::string &str, const int pos) {
  const static std::unordered_map<std::string_view, int> digits = {
      {"one", 1},  {"two", 2},   {"six", 6},   {"four", 4},  {"five", 5},
      {"nine", 9}, {"three", 3}, {"seven", 7}, {"eight", 8},
  };

  for (const auto [digit_str, digit_int] : digits) {
    if (pos >= digit_str.size() - 1) {
      int local_ans = digit_int;

      for (int j = 0; j < digit_str.size(); ++j) {
        if (digit_str[j] != str[pos - digit_str.size() + 1 + j]) {
          local_ans = -1;
        }
      }

      if (local_ans != -1) {
        return local_ans;
      }
    }
  }

  return -1;
}

template <>
std::string Solve<2023, 1, 'B'>(std::stringstream input) {
  int ans = 0;

  for (std::string str; std::getline(input, str);) {
    int first = -1;
    int second = 0;

    for (int i = 0; i < str.size(); ++i) {
      if (std::isdigit(str[i])) {
        if (first == -1) {
          first = str[i] - '0';
        }

        second = str[i] - '0';
      } else {
        const int digit = GetDigit(str, i);

        if (digit != -1) {
          if (first == -1) {
            first = digit;
          }

          second = digit;
        }
      }
    }

    const int val = first * 10 + second;

    ans += val;
  }

  return std::to_string(ans);
}
