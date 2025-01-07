#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "solution.hpp"

template <>
std::string Solve<2024, 14, 'A'>(std::stringstream input) {
  constexpr int size[] = {103, 101};
  constexpr int iterations = 100;

  int64_t q[4] = {0};

  for (char c; input >> c;) {
    int px, py, vx, vy;

    input >> c >> px >> c >> py >> c >> c >> vx >> c >> vy;

    px = (px + iterations * vx + iterations * size[1]) % size[1];
    py = (py + iterations * vy + iterations * size[0]) % size[0];

    if (px <= size[1] / 2 - 1) {
      if (py <= size[0] / 2 - 1)
        ++q[0];
      else if (py > size[0] / 2)
        ++q[1];
    } else if (px > size[1] / 2) {
      if (py <= size[0] / 2 - 1)
        ++q[2];
      else if (py > size[0] / 2)
        ++q[3];
    }
  }

  return std::to_string(q[0] * q[1] * q[2] * q[3]);
}
