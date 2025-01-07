#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include "solution.hpp"

namespace day13a {

template <typename Functor>
void split(std::vector<int> &res, const std::string_view s, const char delimiter,
           const Functor &func) {
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

}  // namespace day13a

template <>
std::string Solve<2023, 13, 'A'>(std::stringstream input) {
  int ans = 0;

  constexpr std::array<char, 2> masked_char = {'.', '#'};
  std::vector<int> indices;
  std::vector<int> areas;
  std::vector<int> local_areas;

  for (std::string line; std::getline(input, line);) {
    indices.resize(0);
    areas.resize(0);

    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == '?') {
        indices.push_back(i);
      }
    }

    const size_t space_index = line.find(' ') + 1;

    day13a::split(areas, std::string_view(line.c_str() + space_index), ',',
                  [](const std::string_view str) {
                    return std::atoi(str.data());
                  });

    const uint64_t power = 1 << indices.size();

    for (uint64_t mask = 0; mask < power; ++mask) {
      for (int i = 0; i < indices.size(); ++i) {
        line[indices[i]] = masked_char[(mask >> i) & 1];
      }

      day13a::split(local_areas, std::string_view(line.c_str(), space_index - 1), '.',
                    [](const std::string_view str) -> int {
                      return str.size();
                    });

      bool is_valid = false;

      if (local_areas.size() == areas.size()) {
        is_valid = true;

        for (int i = 0; i < areas.size(); ++i) {
          if (local_areas[i] != areas[i]) {
            is_valid = false;
          }
        }
      }

      ans += is_valid;

      for (const int index : indices) {
        line[index] = '.';
      }
    }
  }

  return std::to_string(ans);
}
