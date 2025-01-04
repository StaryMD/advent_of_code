#include <format>
#include <fstream>

#include "solution.hpp"
#include "solution_map.hpp"

const solution_map_t solution_map = {
#include "solution_files.hpp"
};

const solution_map_t &GetSolutionMap() {
  return solution_map;
}

std::string GetInput(const int year, const int day) {
  const std::string input_file = std::format("data/{}_{}_input.txt", year, day);

  std::ifstream file(input_file);

  if (file.fail()) {
    throw std::runtime_error(std::format("could not open {}", input_file));
  }

  std::stringstream ans;
  ans << file.rdbuf();

  return ans.str();
}
