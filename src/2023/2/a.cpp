#include <cctype>
#include <string>

#include "solution.hpp"

template <>
std::string Solve<2023, 2, 'A'>(std::stringstream input) {
  int ans = 0;

  std::string str = input.str() + '\n';

  for (int pos = 5, temp; pos < str.size(); pos += 6) {
    int game_id = 0;

    while (str[pos] != ':') {
      game_id = game_id * 10 + str[pos] - '0';
      ++pos;
    }

    int red_cubes = 0;
    int green_cubes = 0;
    int blue_cubes = 0;

    int num = 0;
    bool was_space = true;
    bool good = true;

    for (; str[pos] != '\n'; ++pos) {
      if (std::isdigit(str[pos])) {
        num = num * 10 + str[pos] - '0';
      } else if (str[pos] == ';') {
        good &= red_cubes <= 12 && green_cubes <= 13 && blue_cubes <= 14;

        red_cubes = 0;
        green_cubes = 0;
        blue_cubes = 0;
      } else if (was_space) {
        switch (str[pos]) {
          case 'r': {
            red_cubes = num;
            break;
          }
          case 'g': {
            green_cubes = num;
            break;
          }
          case 'b': {
            blue_cubes = num;
            break;
          }
        }
        num = 0;
      }

      was_space = (str[pos] == ' ');
    }

    good &= red_cubes <= 12 && green_cubes <= 13 && blue_cubes <= 14;

    if (good) {
      ans += game_id;
    }
  }

  return std::to_string(ans);
}
