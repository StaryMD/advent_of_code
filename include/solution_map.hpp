#pragma once

#include <functional>
#include <map>
#include <string>

using solution_map_t =
    std::map<int, std::map<int, std::map<char, std::function<std::string(std::stringstream)>>>>;

const solution_map_t &GetSolutionMap();
