#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

struct File {
  int id;
  int size;
};

int main() {
  std::ifstream fin("data/9.txt");

  std::string line;
  fin >> line;

  my::Timer timer;

  std::vector<File> files;
  std::vector<int> decomp;

  for (int i = 0; i < line.size(); ++i) {
    const int id = ((i & 1)) ? -1 : (i / 2);
    files.push_back({id, line[i] - '0'});
  }

  for (int right = files.size() - 1; right > 0; --right) {
    if (files[right].id != -1) {
      for (int left = 0; left < right; ++left) {
        if (files[left].id == -1 && files[right].size <= files[left].size) {
          const File file = files[right];

          files[left].size -= files[right].size;
          files[right].id = -1;
          files.insert(files.begin() + left, file);
          break;
        }
      }
    }
  }

  for (int i = 0; i < files.size(); ++i) {
    for (int j = 0; j < files[i].size; ++j) {
      decomp.push_back(files[i].id);
    }
  }

  uint64_t points = 0;

  for (uint64_t i = 0; i < decomp.size(); ++i) {
    if (decomp[i] != -1) {
      points += decomp[i] * i;
    }
  }

  const double elapsed_time = timer.ElapsedTime();

  std::cout << points << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e3 << " ms\n";
}
