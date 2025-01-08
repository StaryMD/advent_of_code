#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day22b_2024 {

uint32_t Next(uint32_t n) {
  constexpr uint32_t m = 16777216;

  n ^= n * 64;
  n %= m;

  n ^= n / 32;
  n %= m;

  n ^= n * 2048;
  n %= m;

  return n;
}

}  // namespace day22b_2024

template <>
std::string Solve<2024, 22, 'B'>(std::stringstream input) {
  constexpr int32_t kSize = 19 * 19 * 19 * 19;

  std::array<uint8_t, 2001> nums;
  std::array<uint8_t, 2001> diffs;

  std::array<int16_t, kSize> price_map;
  std::ranges::fill(price_map, 0);

  std::vector<bool> local_prices(kSize);

  for (uint32_t n; input >> n;) {
    nums[0] = n % 10;

    for (int i = 1; i <= 2000; ++i) {
      n = day22b_2024::Next(n);
      nums[i] = n % 10;
      diffs[i] = 9 + nums[i] - nums[i - 1];
    }

    std::fill(local_prices.begin(), local_prices.end(), false);

    for (int i = 1; i < nums.size() - 3; ++i) {
      const int32_t diff = ((diffs[i] * 19 + diffs[i + 1]) * 19 + diffs[i + 2]) * 19 + diffs[i + 3];

      price_map[diff] += not local_prices[diff] * nums[i + 3];
      local_prices[diff] = not local_prices[diff];
    }
  }

  int16_t best_price = 0;

  for (const auto price : price_map) {
    best_price = std::max(best_price, price);
  }

  return std::to_string(best_price);
}
