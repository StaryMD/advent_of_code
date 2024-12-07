#include <cstdint>
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

    std::vector<uint64_t> len(nums.size());
    for (size_t i = 0; i < len.size(); ++i) {
      len[i] = my::Pow<uint64_t>(10, std::to_string(nums[i]).size());
    }
    std::vector<uint64_t> pows3(nums.size());
    for (size_t i = 0; i < pows3.size(); ++i) {
      pows3[i] = my::Pow<uint64_t>(3, i);
    }

    const uint64_t n = my::Pow<uint64_t>(3, nums.size() - 1);
    for (uint64_t i = 0; i < n; ++i) {
      uint64_t sum = nums[0];

      for (size_t j = 1; j < nums.size(); ++j) {
        switch ((i / pows3[j - 1]) % 3) {
          case 0:
            sum += nums[j];
            break;
          case 1:
            sum *= nums[j];
            break;
          case 2:
            sum = sum * len[j] + nums[j];
            break;
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
