#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int map_y = 103;
constexpr int map_x = 101;

struct Robot {
  int x, y, vx, vy;
};

void PrintMap(const std::vector<Robot> &robots) {
  std::vector<std::string> lines(map_y, std::string(map_x, '.'));

  for (const Robot &robot : robots) {
    lines[robot.y][robot.x] = 'X';
  }

  for (const std::string &line : lines) {
    std::cout << line << '\n';
  }
  std::cout << '\n';
}

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

int main() {
  std::ifstream fin("data/14.txt");

  std::vector<Robot> robots;

  for (std::string line; std::getline(fin, line);) {
    std::stringstream sline(line);

    Robot robot;
    sline >> robot.x >> robot.y >> robot.vx >> robot.vy;
    robots.push_back(robot);
  }

  int seconds = 0;
  while (seconds < 10000) {
    std::cout << "Second " << seconds << '\n';
    if (IsTree(robots)) {
      PrintMap(robots);

      getchar();
    }
    std::cout << "Moving the robots\n";

    seconds += 1;
    for (Robot &robot : robots) {
      robot.x = (robot.x + robot.vx + map_x) % map_x;
      robot.y = (robot.y + robot.vy + map_y) % map_y;
    }
  }

  std::cout << seconds << '\n';
}
