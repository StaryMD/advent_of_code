#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day17_2024 {

// Shamelessly reverse engineered the instructions
uint64_t GetNextDigit(uint64_t a) {
  uint64_t b = a % 8;
  b = b ^ 5;
  const uint64_t c = a >> b;
  b = b ^ 6;
  a = a >> 3;
  b = b ^ c;

  return b;
};

}  // namespace day17_2024

template <>
std::string Solve<2024, 17, 'B'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  const std::string program1 = lines[4].substr(9);
  std::vector<uint64_t> program(program1.size() / 2 + 1);

  for (int i = 0; i < program1.size(); i += 2) {
    program[i / 2] = program1[i] - '0';
  }

  std::ranges::reverse(program);

  uint64_t ans = std::numeric_limits<uint64_t>::max();

  struct State {
    uint64_t i, a;
  };

  std::vector<State> states;
  states.emplace_back(0, 0);

  while (not states.empty()) {
    const auto [i, a] = states.back();
    states.pop_back();

    if (i == program.size()) {
      ans = std::min(ans, a);
    } else {
      const uint64_t wanted = program[i];

      for (uint64_t j = 0; j < 8; ++j) {
        const uint64_t new_a = a * 8 + j;
        const uint64_t new_b = day17_2024::GetNextDigit(new_a);

        if (new_b % 8 == wanted) {
          states.emplace_back(i + 1, new_a);
        }
      }
    }
  }

  return std::to_string(ans);
}
