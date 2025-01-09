#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include <vector>

#include "solution.hpp"

template <>
std::string Solve<2024, 23, 'A'>(std::stringstream stream_input) {
  std::array<std::vector<uint16_t>, 26 * 26> edges;

  const std::string input = stream_input.str();

  for (size_t i = 0; i < input.size(); i += 6) {
    const uint16_t start = (input[i + 0] - 'a') * 26 + (input[i + 1] - 'a');
    const uint16_t end = (input[i + 3] - 'a') * 26 + (input[i + 4] - 'a');

    edges[start].push_back(end);
    edges[end].push_back(start);
  }

  std::unordered_set<uint32_t> groups;
  std::array<bool, 1 << 16> node0_edge_freq = {0};

  for (uint16_t node0 = ('t' - 'a') * 26; node0 < ('t' - 'a' + 1) * 26; ++node0) {
    for (const uint16_t node1 : edges[node0]) {
      node0_edge_freq[node1] = true;
    }

    for (const uint16_t node1 : edges[node0]) {
      for (const uint16_t node2 : edges[node1]) {
        if (node0_edge_freq[node2]) {
          uint16_t nodes[] = {node0, node1, node2};

          if (nodes[0] < nodes[1])
            std::swap(nodes[0], nodes[1]);
          if (nodes[1] < nodes[2])
            std::swap(nodes[1], nodes[2]);
          if (nodes[0] < nodes[1])
            std::swap(nodes[0], nodes[1]);

          const uint32_t hash = ((nodes[0] * 26 * 26) + nodes[1]) * 26 * 26 + nodes[2];
          groups.insert(hash);
        }
      }
    }

    for (const uint16_t node1 : edges[node0]) {
      node0_edge_freq[node1] = false;
    }
  }

  return std::to_string(groups.size());
}
