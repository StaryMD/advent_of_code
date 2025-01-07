#include <algorithm>
#include <string>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 5, 'A'>(std::stringstream input) {
  std::vector<int> map[100];

  for (std::string line; std::getline(input, line);) {
    if (line.empty()) {
      break;
    }

    const int a = (line[0] - '0') * 10 + line[1] - '0';
    const int b = (line[3] - '0') * 10 + line[4] - '0';

    map[a].push_back(b);
  }

  int points = 0;

  for (std::string line; std::getline(input, line);) {
    std::vector<int> nums(line.size() / 3 + 1);

    for (int i = 0; i < line.size(); i += 3) {
      nums[i / 3] = (line[i] - '0') * 10 + line[i + 1] - '0';
    }

    bool good = true;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        if (std::find(map[nums[j]].begin(), map[nums[j]].end(), nums[i]) != map[nums[j]].end()) {
          good = false;
        }
      }
    }

    if (good) {
      points += nums[nums.size() / 2];
    }
  }

  return std::to_string(points);
}
