#include <set>
#include <string>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 17, 'A'>(std::stringstream input) {
  std::vector<std::string> lines;

  for (std::string line; std::getline(input, line);) {
    lines.push_back(line);
  }

  int a = std::stoi(lines[0].data() + 12);
  int b = std::stoi(lines[1].data() + 12);
  int c = std::stoi(lines[2].data() + 12);
  std::string &program = lines[4];

  const std::set<int> combo_ops = {0, 2, 5, 6, 7};

  std::string ans;

  for (int i = 9; i < program.size(); i += 4) {
    const int inst = program[i] - '0';
    int op = program[i + 2] - '0';

    if (combo_ops.contains(inst)) {
      switch (op) {
        case 4: {
          op = a;
          break;
        }
        case 5: {
          op = b;
          break;
        }
        case 6: {
          op = c;
          break;
        }
      }
    }

    switch (inst) {
      case 0: {
        a >>= op;
        break;
      }
      case 1: {
        b ^= op;
        break;
      }
      case 2: {
        b = op % 8;
        break;
      }
      case 3: {
        if (a != 0) {
          i = (op * 2 + 9) - 4;
        }
        break;
      }
      case 4: {
        b ^= c;
        break;
      }
      case 5: {
        if (not ans.empty()) {
          ans += ',';
        }

        ans += op % 8 + '0';
        break;
      }
      case 6: {
        b = a >> op;
        break;
      }
      case 7: {
        c = a >> op;
        break;
      }
    }
  }

  return ans;
}
