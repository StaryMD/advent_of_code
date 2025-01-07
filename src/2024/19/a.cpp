#include <string>
#include <vector>

#include "solution.hpp"

namespace day19a_2024 {

bool SolveHelper(const std::vector<std::string_view> &towels, const std::string_view pattern,
                 const size_t index) {
  if (index == pattern.size()) {
    return true;
  }

  for (const std::string_view towel : towels) {
    if (pattern.substr(index, towel.size()).compare(towel) == 0 &&
        SolveHelper(towels, pattern, index + towel.size())) {
      return true;
    }
  }

  return false;
}

}  // namespace day19a_2024

template <>
std::string Solve<2024, 19, 'A'>(std::stringstream sinput) {
  const std::string input = sinput.str() + '\n';

  std::vector<std::string_view> towels;

  size_t word_start = 0;
  size_t i = 0;

  for (; input[i] != '\n'; ++i) {
    if (input[i] == ',') {
      towels.emplace_back(input.cbegin() + word_start, input.cbegin() + i);
      word_start = i += 2;
    }
  }
  towels.emplace_back(input.cbegin() + word_start, input.cbegin() + i);

  int points = 0;

  for (word_start = i += 2; i < input.size(); ++i) {
    if (input[i] == '\n') {
      const std::string_view pattern(input.cbegin() + word_start, input.cbegin() + i);

      if (day19a_2024::SolveHelper(towels, pattern, 0)) {
        ++points;
      }

      word_start = i + 1;
    }
  }

  return std::to_string(points);
}
