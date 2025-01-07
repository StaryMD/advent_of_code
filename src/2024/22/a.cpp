#include <cstdint>
#include <iostream>
#include <string>

#include "solution.hpp"

namespace day22a_2024 {

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

}  // namespace day22a_2024

template <>
std::string Solve<2024, 22, 'A'>(std::stringstream input) {
  uint64_t points = 0;

  for (uint32_t n; input >> n;) {
    for (int i = 0; i < 2000; ++i) {
      n = day22a_2024::Next(n);
    }

    points += n;
  }

  return std::to_string(points);
}
