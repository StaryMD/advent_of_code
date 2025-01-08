#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "solution.hpp"

namespace day11_2024 {

int GetDigitCount(uint64_t num) {
  int counter = 0;

  while (num != 0) {
    num /= 10;
    ++counter;
  }

  return counter;
}

std::pair<uint64_t, uint64_t> SplitNumber(uint64_t num, const int digit_count) {
  uint64_t left = 0;
  uint64_t pow_10 = 1;

  for (int i = 0; i < digit_count / 2; ++i) {
    left += num % 10 * pow_10;
    num /= 10;
    pow_10 *= 10;
  }

  uint64_t right = 0;
  pow_10 = 1;

  for (int i = digit_count / 2; i < digit_count; ++i) {
    right += num % 10 * pow_10;
    num /= 10;
    pow_10 *= 10;
  }

  return {left, right};
}

uint64_t GetLength(std::vector<std::unordered_map<uint64_t, uint64_t>> &cache, const int iterations,
                   const uint64_t num, const int it) {
  if (it == iterations) {
    return 1;
  }

  uint64_t &cached_value = cache[it][num];
  if (cached_value != 0) {
    return cached_value;
  }

  uint64_t ans = 0;

  if (num == 0) {
    ans = GetLength(cache, iterations, 1, it + 1);
  } else {
    const int digit_count = GetDigitCount(num);

    if (digit_count % 2 == 0) {
      const auto [left, right] = SplitNumber(num, digit_count);

      ans = GetLength(cache, iterations, right, it + 1);
      ans += GetLength(cache, iterations, left, it + 1);
    } else {
      ans = GetLength(cache, iterations, num * 2024, it + 1);
    }
  }

  cached_value = ans;

  return ans;
}

std::string SolveHelper(std::stringstream &input, const int iterations) {
  std::vector<uint64_t> nums;
  for (uint64_t n; input >> n;) {
    nums.push_back(n);
  }

  struct State {
    uint64_t num;
    int it;
  };

  std::vector<std::unordered_map<uint64_t, uint64_t>> map(iterations);

  uint64_t points = 0;

  for (const uint64_t num : nums) {
    points += GetLength(map, iterations, num, 0);
  }

  return std::to_string(points);
}

}  // namespace day11_2024

template <>
std::string Solve<2024, 11, 'A'>(std::stringstream input) {
  return day11_2024::SolveHelper(input, 25);
}

template <>
std::string Solve<2024, 11, 'B'>(std::stringstream input) {
  return day11_2024::SolveHelper(input, 75);
}
