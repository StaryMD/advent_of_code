#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "utils.hpp"

int main() {
  std::ifstream fin("data/7.txt");

  uint64_t points = 0;

  my::Timer timer;

  for (std::string line; std::getline(fin, line);) {
    std::stringstream sline(line);

    uint64_t test_value;
    char temp;
    std::vector<uint64_t> nums;
    sline >> test_value;
    sline >> temp;
    for (uint64_t a; sline >> a;) {
      nums.push_back(a);
    }

    const uint64_t n = (1 << (nums.size() - 1));

    for (uint64_t i = 0; i < n; ++i) {
      uint64_t sum = nums[0];

      for (size_t j = 1; j < nums.size(); ++j) {
        if (i & (1 << (j - 1))) {
          sum += nums[j];
        } else {
          sum *= nums[j];
        }
      }

      if (test_value == sum) {
        points += test_value;
        break;
      }
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
