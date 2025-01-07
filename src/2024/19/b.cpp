#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "solution.hpp"

namespace day19b_2024 {

uint64_t SolveHelper(std::unordered_map<std::string_view, uint64_t> &cache,
                     const std::vector<std::string_view> &towels, const std::string_view pattern) {
  if (pattern.empty()) {
    return 1;
  }

  uint64_t &cached_value = cache[pattern];
  if (cached_value != 0) {
    return cached_value;
  }

  uint64_t curr_points = 0;

  for (const std::string_view towel : towels) {
    if (pattern.starts_with(towel)) {
      curr_points += SolveHelper(cache, towels, pattern.substr(towel.size()));
    }
  }

  cached_value = curr_points;

  return curr_points;
}

}  // namespace day19b_2024

template <>
std::string Solve<2024, 19, 'B'>(std::stringstream input_stream) {
  const std::string input = input_stream.str() + '\n';

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

  std::unordered_map<std::string_view, uint64_t> cache;

  uint64_t points = 0;

  for (word_start = i += 2; i < input.size(); ++i) {
    if (input[i] == '\n') {
      const std::string_view pattern(input.cbegin() + word_start, input.cbegin() + i);
      cache.clear();

      points += day19b_2024::SolveHelper(cache, towels, pattern);

      word_start = i + 1;
    }
  }

  return std::to_string(points);
}
