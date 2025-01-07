#include <algorithm>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "solution.hpp"

namespace day24b_2024 {

struct Instruction {
  int32_t in1, in2, out;
  char op;
};

constexpr int32_t Hash(const char* name) {
  return name[0] * 256 * 256 + name[1] * 256 + name[2];
}

constexpr std::string Unhash(const int32_t name) {
  return {
      char(name / (256 * 256)),
      char(name / 256 % 256),
      char(name % 256),
      0,
  };
}

}  // namespace day24b_2024

template <>
std::string Solve<2024, 24, 'B'>(std::stringstream input) {
  using namespace day24b_2024;

  std::vector<std::string> lines;
  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  int i = 0;
  while (not lines[i].empty()) {
    ++i;
  }

  std::vector<Instruction> instructions;

  for (++i; i < lines.size(); ++i) {
    if (lines[i][4] == 'O') {
      instructions.emplace_back(Hash(lines[i].data() + 0), Hash(lines[i].data() + 7),
                                Hash(lines[i].data() + 14), 'O');
    } else {
      instructions.emplace_back(Hash(lines[i].data() + 0), Hash(lines[i].data() + 8),
                                Hash(lines[i].data() + 15), lines[i][4]);
    }
  }

  std::unordered_map<char, std::unordered_set<int32_t>> lookup = {
      {'O', {}},
      {'X', {}},
      {'A', {}},
  };

  for (int i = 0; i < instructions.size(); ++i) {
    const auto &[in1, in2, out, op] = instructions[i];

    lookup.at(op).insert(in1);
    lookup.at(op).insert(in2);
  }

  std::unordered_set<int32_t> swapped;

  for (const auto &[in1, in2, out, op] : instructions) {
    switch (op) {
      case 'A': {
        if (in1 != Hash("x00") and in2 != Hash("x00") and not lookup['O'].contains(out)) {
          swapped.insert(out);
        }
        break;
      }
      case 'O': {
        if (out / (256 * 256) == 'z' and out != Hash("z45")) {
          swapped.insert(out);
        }
        if (lookup['O'].contains(out)) {
          swapped.insert(out);
        }
        break;
      }
      case 'X': {
        if (in1 / (256 * 256) == 'x' or in2 / (256 * 256) == 'x') {
          if (in1 != Hash("x00") and in2 != Hash("x00") and not lookup['X'].contains(out)) {
            swapped.insert(out);
          }
        } else {
          if (out / (256 * 256) != 'z') {
            swapped.insert(out);
          }
        }
        break;
      }
    }
  }

  std::vector<int32_t> ans_vec;
  ans_vec.reserve(swapped.size());

  for (const int32_t x : swapped) {
    ans_vec.push_back(x);
  }

  std::ranges::sort(ans_vec);

  std::string ans = Unhash(ans_vec[0]);

  for (int i = 1; i < ans_vec.size(); ++i) {
    ans += ',' + Unhash(ans_vec[i]);
  }

  return ans;
}
