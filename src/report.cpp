#include <cctype>
#include <format>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "solution.hpp"
#include "solution_map.hpp"
#include "utility.hpp"

int main(const int argc, const char* const* const argv) {
  int iterations = 1;
  int wanted_year = 0;
  int wanted_day = 0;
  char wanted_part = 0;

  if (argc >= 2) {
    iterations = std::stoi(argv[1]);

    if (iterations < 1) {
      throw std::runtime_error(
          std::format("Cannot have a non-positive iterations number! : {}", iterations));
    }
    if (iterations != 1) {
      std::cout << std::format("Will do {} iterations for every part\n", iterations);
    }
  }

  if (argc >= 3) {
    wanted_year = std::stoi(argv[2]);
    std::cout << std::format("Will do only year {}\n", wanted_year);
  }

  if (argc >= 4) {
    wanted_day = std::stoi(argv[3]);
    std::cout << std::format("Will do only day {}\n", wanted_day);
  }

  if (argc >= 5) {
    wanted_part = std::toupper(argv[4][0]);
    std::cout << std::format("Will do only part {}\n", wanted_part);
  }

  double total_elapsed_time_ms = 0;
  int star_counter = 0;

  for (const auto &[year, days] : GetSolutionMap()) {
    if (wanted_year == 0 || year == wanted_year) {
      for (const auto &[day, parts] : days) {
        if (wanted_day == 0 || day == wanted_day) {
          const std::string input = GetInput(year, day);

          for (const auto &[part, solve] : parts) {
            if (wanted_part == 0 || part == wanted_part) {
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
              ++star_counter;
            }
          }
        }
      }
    }
  }

  std::cout << '\n';
  std::cout << std::format("Total elapsed time: {:0.3f}ms\n", total_elapsed_time_ms);
  std::cout << std::format("Useful time: {:0.3f}ms\n", total_elapsed_time_ms / iterations);
  std::cout << std::format("Stars: {}\n", star_counter);

  return 0;
}
