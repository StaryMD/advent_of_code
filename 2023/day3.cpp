#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool IsSymbol(const char ch) {
  return ch != '.' && not std::isdigit(ch);
}

int main() try {
  std::ifstream fin("data/day3.in");

  int ans = 0;

  std::vector<std::string> world;

  for (std::string str; std::getline(fin, str);) {
    world.push_back(str + '.');
  }

  const int world_size_x = world[0].size();
  const int world_size_y = world.size();

  for (int i = 0; i < world_size_y; ++i) {
    int len = 0;

    for (int j = 0; j < world_size_x; ++j) {
      if (std::isdigit(world[i][j])) {
        ++len;
      } else {
        const int top_left_x = std::max(0, j - len - 1);
        const int top_left_y = std::max(0, i - 1);

        const int bottom_right_x = std::min(world_size_x - 1, j);
        const int bottom_right_y = std::min(world_size_y - 1, i + 1);

        bool contains_symbol = false;

        for (int x = top_left_x; x <= bottom_right_x; ++x) {
          for (int y = top_left_y; y <= bottom_right_y; ++y) {
            if (IsSymbol(world[y][x])) {
              contains_symbol = true;
            }
          }
        }

        if (contains_symbol && len > 0) {
          std::cout << i << ' ' << j << ' ' << len << '\n';
          const std::string number_str = world[i].substr(j - len, len);
          const int number = std::stoi(number_str);

          ans += number;
        }

        len = 0;
      }
    }
  }

  std::cout << "Answer: " << ans << '\n';

  return 0;
} catch (const std::exception& excp) {

  std::cout << "C++ standard exception: " << excp.what() << '\n';
}
