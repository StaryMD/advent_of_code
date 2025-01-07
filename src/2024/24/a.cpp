#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "solution.hpp"

namespace day24a_2024 {

struct Instruction {
  int32_t in1, in2, out;
  char op;
};

int32_t Hash(const char* name) {
  return name[0] * 256 * 256 + name[1] * 256 + name[2];
}

}  // namespace day24a_2024

template <>
std::string Solve<2024, 24, 'A'>(std::stringstream input) {
  std::unordered_map<int32_t, bool> vars;

  std::vector<std::string> lines;
  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  int i = 0;
  for (; not lines[i].empty(); ++i) {
    vars[day24a_2024::Hash(lines[i].data())] = lines[i][5] == '1';
  }

  std::vector<day24a_2024::Instruction> instructions;

  for (++i; i < lines.size(); ++i) {
    if (lines[i][4] == 'O') {
      instructions.emplace_back(day24a_2024::Hash(lines[i].data() + 0),
                                day24a_2024::Hash(lines[i].data() + 7),
                                day24a_2024::Hash(lines[i].data() + 14), 'O');
    } else {
      instructions.emplace_back(day24a_2024::Hash(lines[i].data() + 0),
                                day24a_2024::Hash(lines[i].data() + 8),
                                day24a_2024::Hash(lines[i].data() + 15), lines[i][4]);
    }
  }

  for (int i = 0; i < instructions.size(); ++i) {
    const auto &[in1, in2, out, op] = instructions[i];

    if (not(vars.contains(in1) && vars.contains(in2))) {
      instructions.emplace_back(in1, in2, out, op);
    } else {
      switch (op) {
        case 'O': {
          vars[out] = vars.at(in1) | vars.at(in2);
          break;
        }
        case 'X': {
          vars[out] = vars.at(in1) ^ vars.at(in2);
          break;
        }
        case 'A': {
          vars[out] = vars.at(in1) & vars.at(in2);
          break;
        }
      }
    }
  }

  uint64_t z = 0;

  for (const auto &[var, val] : vars) {
    if (var / (256 * 256) == 'z' and val) {
      const int exp = (var / 256 % 256 - '0') * 10 + (var % 256 - '0');
      z |= 1ULL << exp;
    }
  }

  return std::to_string(z);
}
