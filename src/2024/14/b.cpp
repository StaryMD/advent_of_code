#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day14_2024 {

constexpr int map_y = 103;
constexpr int map_x = 101;

struct Robot {
  int x, y, vx, vy;
};

// #include <fstream>

// void PrintMap(const std::vector<Robot> &robots) {
//   std::vector<std::string> lines(map_y, std::string(map_x, '.'));

//   for (const Robot &robot : robots) {
//     lines[robot.y][robot.x] = 'X';
//   }

//   for (const std::string &line : lines) {
//     std::cout << line << '\n';
//   }
//   std::cout << '\n';
// }

bool IsTree(const std::vector<Robot> &robots) {
  int counter = 0;

  for (const Robot &robot : robots) {
    if (robot.x < map_x / 2) {
      if (robot.y < (map_x / 2 - robot.x) / 2) {
        counter++;
      }
    } else {
      if (robot.y - map_x / 2 < robot.x / 2) {
        counter++;
      }
    }
  }

  return counter > robots.size() * 0.8;
}

}  // namespace day14_2024

template <>
std::string Solve<2024, 14, 'B'>(std::stringstream input) {
  std::vector<day14_2024::Robot> robots;

  while (input) {
    day14_2024::Robot robot;
    char c;

    input >> c >> c >> robot.x >> c >> robot.y >> c >> c >> robot.vx >> c >> robot.vy;
    robots.push_back(robot);
  }

  int seconds = 0;

  while (not IsTree(robots)) {
    ++seconds;

    // PrintMap(robots);
    // getchar();

    for (day14_2024::Robot &robot : robots) {
      robot.x = (robot.x + robot.vx + day14_2024::map_x) % day14_2024::map_x;
      robot.y = (robot.y + robot.vy + day14_2024::map_y) % day14_2024::map_y;
    }
  }

  return std::to_string(seconds);
}
