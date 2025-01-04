#pragma once

#include <format>
#include <fstream>
#include <sstream>
#include <string>

inline std::string GetInput(const int year, const int day) {
  const std::string input_file = std::format("data/{}_{}_input.txt", year, day);

  std::ifstream file(input_file);

  if (file.fail()) {
    throw std::runtime_error(std::format("could not open {}", input_file));
  }

  std::stringstream ans;
  ans << file.rdbuf();

  return ans.str();
}

template <int year, int day, char part>
std::string Solve(std::stringstream input);
