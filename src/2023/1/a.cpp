#include <string>

#include "solution.hpp"

template <>
std::string Solve<2023, 1, 'A'>(std::stringstream input) {
  int ans = 0;

  for (std::string str; std::getline(input, str);) {
    int first = -1;
    int second = 0;

    for (auto ch : str) {
      if (ch >= '0' && ch <= '9') {
        if (first == -1) {
          first = ch;
        }

        second = ch;
      }
    }

    first -= '0';
    second -= '0';

    const int val = first * 10 + second;

    ans += val;
  }

  return std::to_string(ans);
}
