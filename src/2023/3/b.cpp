#include <cctype>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day3b {

struct number_t {
  number_t(const int y_, const int x_, const int val) : y(y_), x(x_), value(val) {
    len = 1;
  }

  int value;
  int len;

  int x;
  int y;
};

std::vector<number_t> ExtractNumbers(const std::vector<std::string> &world) {
  std::vector<number_t> numbers;

  bool in_number = false;

  for (int y = 0; y < world.size(); ++y) {
    const std::string &line = world[y];

    for (int x = 0; x < line.size(); ++x) {
      if (std::isdigit(line[x])) {
        if (in_number) {
          number_t &number = numbers.back();

          number.value = number.value * 10 + (line[x] - '0');
          ++number.len;
        } else {
          number_t number(y, x, line[x] - '0');

          numbers.push_back(number);
          in_number = true;
        }
      } else {
        in_number = false;
      }
    }
    in_number = false;
  }

  return numbers;
}

std::vector<std::vector<int>> ExtractStarMap(const std::vector<std::string> &world,
                                             const std::vector<number_t> &numbers) {
  std::vector<std::vector<int>> starmap(world.size() * world[0].size());

  for (const number_t &num : numbers) {
    const int y_left = std::max(0, num.y - 1);
    const int x_left = std::max(0, num.x - 1);

    const int y_right = std::min<int>(world.size(), num.y + 2);

    for (int y = y_left; y < y_right; ++y) {
      const std::string &line = world[y];
      const int x_right = std::min<int>(line.size(), num.x + num.len + 1);

      for (int x = x_left; x < x_right; ++x) {
        if (line[x] == '*') {
          starmap[y * line.size() + x].push_back(num.value);
        }
      }
    }
  }

  return starmap;
}

}  // namespace day3b

template <>
std::string Solve<2023, 3, 'B'>(std::stringstream input) {
  std::vector<std::string> world;

  for (std::string str; std::getline(input, str);) {
    world.push_back(str);
  }

  const std::vector<day3b::number_t> numbers = day3b::ExtractNumbers(world);
  const std::vector<std::vector<int>> starmap = ExtractStarMap(world, numbers);

  int64_t sum = 0;

  for (const std::vector<int> &num_list : starmap) {
    if (num_list.size() == 2) {
      sum += num_list[0] * num_list[1];
    }
  }

  return std::to_string(sum);
}
