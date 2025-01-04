#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

int main() {
  std::ifstream fin("data/9.txt");

  std::string line;
  std::vector<int32_t> decomp;
  decomp.reserve(line.size() * 20);
  fin >> line;

  my::Timer timer;

  uint64_t points = 0;

  for (int i = 0; i < line.size(); ++i) {
    int c = -1;
    if ((i & 1) == 0) {
      c = i / 2;
    }

    for (int j = 0; j < line[i] - '0'; ++j) {
      decomp.push_back(c);
    }
  }

  uint64_t right = decomp.size();
  for (uint64_t left = 0; left < right;) {
    if (decomp[left] == -1) {
      if (decomp[--right] == -1) {
        decomp.pop_back();
        continue;
      }
      decomp[left] = decomp[right];
      decomp.pop_back();
    }
    ++left;
  }

  for (uint64_t i = 0; i < decomp.size(); ++i) {
    points += decomp[i] * i;
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
