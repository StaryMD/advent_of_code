#include <cstdint>
#include <iostream>
#include <regex>
#include <string>

#include "solution.hpp"

template <>
std::string Solve<2024, 3, 'B'>(std::stringstream input) {
  const std::regex regex("mul\\(([0-9]+),([0-9]+)\\)");

  const std::string str = input.str();

  int64_t points = 0;

  {
    int left = 0;
    int right = str.find("don't()");
    if (right == std::string::npos) {
      right = str.size();
    }

    while (left != str.size()) {
      {
        const auto words_begin =
            std::sregex_iterator(str.begin() + left, str.begin() + right, regex);
        const auto words_end = std::sregex_iterator();

        for (auto i = words_begin; i != words_end; ++i) {
          const std::smatch match = *i;

          points += std::stoi(match[1]) * std::stoi(match[2]);
        }
      }

      left = str.find("do()", right);
      if (left == std::string::npos) {
        left = str.size();
      }

      right = str.find("don't()", left);
      if (right == std::string::npos) {
        right = str.size();
      }
    }
  }

  return std::to_string(points);
}
