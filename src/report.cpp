#include <format>
#include <iostream>
#include <sstream>
#include <string>

#include "solution.hpp"
#include "solution_map.hpp"
#include "utility.hpp"

int main(const int argc, const char* const* const argv) {
  int iterations = 1;

  if (argc == 2) {
    iterations = std::stoi(argv[1]);
  }

  double total_elapsed_time_ms = 0;

  for (const auto &[year, days] : GetSolutionMap()) {
    for (const auto &[day, parts] : days) {
      const std::string input = GetInput(year, day);

      for (const auto &[part, solve] : parts) {
        const my::Timer timer;

#pragma unroll 1
        for (int i = 1; i < iterations; ++i) {
          solve(std::stringstream(input));
        }

        const std::string ans = solve(std::stringstream(input));

        const double elapsed_time_ms = timer.ElapsedTime() * 1e3;
        total_elapsed_time_ms += elapsed_time_ms;

        std::cout << std::format("{} {:2} {} in {:8.3f}ms for {}\n", year, day, part,
                                 elapsed_time_ms / iterations, ans);
      }
    }
  }

  std::cout << '\n';
  std::cout << std::format("Useful time: {:0.3f}ms\n", total_elapsed_time_ms / iterations);
  std::cout << std::format("Total elapsed time: {:0.3f}ms\n", total_elapsed_time_ms);

  return 0;
}
