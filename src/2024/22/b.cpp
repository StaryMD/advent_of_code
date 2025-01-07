#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
  std::vector<std::unordered_map<int32_t, int8_t>> prices;

  for (uint32_t n; input >> n;) {
    std::vector<int8_t> nums = {int8_t(n % 10)};

    for (int i = 0; i < 2000; ++i) {
      n = day22b_2024::Next(n);
      nums.push_back(n % 10);
    }

    union Stuff {
      int8_t diff[4];
      int32_t d;
    };

    std::unordered_map<int32_t, int8_t> price;

    for (int i = 1; i < nums.size() - 3; ++i) {
      const Stuff stuff = {
          .diff =
              {
                  int8_t(nums[i + 0] - nums[i - 1]),
                  int8_t(nums[i + 1] - nums[i + 0]),
                  int8_t(nums[i + 2] - nums[i + 1]),
                  int8_t(nums[i + 3] - nums[i + 2]),
              },
      };

      if (not price.contains(stuff.d)) {
        price[stuff.d] = nums[i + 3];
      }
    }

    prices.push_back(price);
  }

  const auto GetValue = [&](const int32_t diff) {
    int32_t sum = 0;

    for (const auto &price : prices) {
      if (price.contains(diff)) {
        sum += price.at(diff);
      }
    }

    return sum;
  };

  std::unordered_set<int32_t> diffs_to_ckeck;

  for (const auto &price_map : prices) {
    for (const auto [diff, price] : price_map) {
      diffs_to_ckeck.insert(diff);
    }
  }

  int32_t best_price = 0;

  for (const int32_t diff : diffs_to_ckeck) {
    best_price = std::max(best_price, GetValue(diff));
  }

  return std::to_string(best_price);
}
