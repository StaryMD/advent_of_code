#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "solution.hpp"

namespace day11_2024 {

uint64_t GetLength(std::unordered_map<uint64_t, uint64_t> cache[], const int iterations,
                   const uint64_t num, const int it) {
  if (it >= iterations) {
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
    const std::string s = std::to_string(num);

    if (s.size() % 2 == 0) {
      ans = GetLength(cache, iterations, std::stoi(s.substr(0, s.size() / 2)), it + 1) +
            GetLength(cache, iterations, std::stoi(s.substr(s.size() / 2)), it + 1);
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

  std::unordered_map<uint64_t, uint64_t> map[iterations];

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
