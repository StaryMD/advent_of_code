#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::ifstream fin("data/1.txt");

  std::vector<int32_t> list1;
  std::vector<int32_t> list2;

  for (int32_t a, b; fin >> a >> b;) {
    list1.push_back(a);
    list2.push_back(b);
  }

  {  // Part 1
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    int64_t dist_sum = 0;

    for (size_t i = 0; i != list1.size(); ++i) {
      dist_sum += std::abs(list1[i] - list2[i]);
    }

    std::cout << "Answer 1: " << dist_sum << '\n';
  }

  {  // Part 2
    std::unordered_map<int32_t, int32_t> frequency;

    for (const int32_t item : list2) {
      ++frequency[item];
    }

    int64_t similarity = 0;

    for (const int32_t item : list1) {
      if (frequency.find(item) != frequency.end()) {
        similarity += item * frequency.at(item);
      }
    }

    std::cout << "Answer 2: " << similarity << '\n';
  }

  return 0;
}
