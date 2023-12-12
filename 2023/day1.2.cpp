#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

int GetDigit(const std::string &str, const int pos) {
  const static std::unordered_map<std::string_view, int> digits = {
      {"one", 1},  {"two", 2},   {"six", 6},   {"four", 4},  {"five", 5},
      {"nine", 9}, {"three", 3}, {"seven", 7}, {"eight", 8},
  };

  int ans = -1;

  for (const auto [digit_str, digit_int] : digits) {
    if (pos >= digit_str.size() - 1) {
      int local_ans = digit_int;

      for (int j = 0; j < digit_str.size(); ++j) {
        if (digit_str[j] != str[pos - digit_str.size() + 1 + j]) {
          local_ans = -1;
        }
      }

      if (local_ans != -1) {
        ans = local_ans;
      }
    }
  }

  return ans;
}

int main() {
  std::ifstream fin("data/day1.in");

  int ans = 0;

  for (std::string str; std::getline(fin, str);) {
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

    std::cout << str << ' ' << first << ' ' << second << '\n';

    const int val = first * 10 + second;

    ans += val;
  }

  std::cout << "Answer: " << ans << '\n';

  return 0;
}
