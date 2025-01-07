#pragma once

#include <sstream>
#include <string>

std::string GetInput(int year, int day);

template <int year, int day, char part>
std::string Solve(std::stringstream);
