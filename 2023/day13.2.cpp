#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

static int alloc_counter = 0;

void* operator new(const size_t size) {
  ++alloc_counter;
  return malloc(size);
}

template <typename Functor>
void split(std::vector<int>& res, const std::string_view s, const char delimiter, const Functor& func) {
  size_t pos_start = 0;

  res.resize(0);

  for (size_t pos_end; (pos_end = s.find(delimiter, pos_start)) != std::string::npos;) {
    std::string_view token(s.data() + pos_start, pos_end - pos_start);
    pos_start = pos_end + 1;

    if (not token.empty()) {
      res.push_back(func(token));
    }
  }

  if (not std::string_view(s.data() + pos_start, s.size() - pos_start).empty()) {
    res.push_back(func(std::string_view(s.data() + pos_start, s.size() - pos_start)));
  }
}

int main() {
  std::ifstream fin("data/day13.in");

  size_t ans = 0;

  constexpr std::array<char, 2> masked_char = {'.', '#'};
  std::vector<int> indices;
  std::vector<int> areas;
  std::vector<int> local_areas;
  std::string map_str;

  for (std::string line; std::getline(fin, line);) {
    indices.resize(0);
    areas.resize(0);

    const size_t space_index = line.find(' ');

    split(areas, std::string_view(line.c_str() + space_index + 1), ',',
          [](const std::string_view str) { return std::atoi(str.data()); });

    {
      const size_t prev_size = areas.size();
      areas.resize(prev_size * 5);

      for (size_t i = prev_size / 5; i < areas.size(); ++i) {
        areas[i] = areas[i % prev_size];
      }
    }

    line.resize(space_index * 5);
    for (size_t i = space_index; i < space_index * 5; ++i) {
      line[i] = line[i % space_index];
    }

    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == '?') {
        indices.push_back(i);
      }
    }

    const uint64_t power = 1 << indices.size();
    std::cout << "Possibilities: " << indices.size() << " : " << power << '\n';

    for (uint64_t mask = 0; mask < power; ++mask) {
      for (int i = 0; i < indices.size(); ++i) {
        line[indices[i]] = masked_char[(mask >> i) & 1];
      }

      split(local_areas, std::string_view(line.c_str(), space_index), '.',
            [](const std::string_view str) -> int { return str.size(); });

      if (local_areas.size() == areas.size()) {
        for (size_t i = 0; i < areas.size(); ++i) {
          if (local_areas[i] != areas[i]) {
            goto BAD;
          }
        }

        ++ans;
      }

    BAD:
      for (const int index : indices) {
        line[index] = '.';
      }
    }
  }

  std::cout << "Answer: " << ans << '\n';

  std::cout << "Allocations: " << alloc_counter << '\n';

  return 0;
}
