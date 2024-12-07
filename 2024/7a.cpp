#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ifstream fin("data/7.txt");

  int points = 0;

  for (std::string line; std::getline(fin, line);) {
    std::cout << line << '\n';
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

      for (int j = 1; j < nums.size(); ++j) {
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

  std::cout << points << '\n';
}
