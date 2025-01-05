#include <cstdint>
#include <regex>
#include <string>

#include "solution.hpp"

template <>
std::string Solve<2024, 3, 'A'>(std::stringstream input) {
  const std::string str = input.str();

  std::regex regex("mul\\(([0-9]+),([0-9]+)\\)");

  const auto words_begin = std::sregex_iterator(str.begin(), str.end(), regex);
  const auto words_end = std::sregex_iterator();

  int64_t points = 0;

  for (auto i = words_begin; i != words_end; ++i) {
    const std::smatch match = *i;

    points += std::stoi(match[1]) * std::stoi(match[2]);
  }

  return std::to_string(points);
}
