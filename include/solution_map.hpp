#pragma once

#include <functional>
#include <map>
#include <string>

#include "solution.hpp"

inline const std::map<int,
                      std::map<int, std::map<char, std::function<std::string(std::stringstream)>>>>
    solution_map = {
#include "solution_files.hpp"
};
