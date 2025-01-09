#include <array>
#include <cstdint>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 1, 'B'>(std::stringstream input_stream) {
  const std::string &input = input_stream.str();

  std::vector<int32_t> list1;
  std::array<int32_t, 100'000> freq = {0};

  bool flag = true;
  int32_t num = 0;

  for (const char c : input) {
    if (std::isdigit(c)) {
      num = num * 10 + c - '0';
    } else {
      if (flag) {
        list1.push_back(num);
      } else {
        ++freq[num];
      }

      flag = not flag;
      num = 0;
    }
  }
  if (flag) {
    list1.push_back(num);
  } else {
    ++freq[num];
  }

  int64_t similarity = 0;

  for (const int32_t item : list1) {
    similarity += item * freq.at(item);
  }

  return std::to_string(similarity);
}
