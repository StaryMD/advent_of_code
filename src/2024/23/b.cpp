#include <algorithm>
#include <array>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "solution.hpp"

namespace day23b {

std::string Unhash(const uint16_t node) {
  std::string answer;
  answer += node / 26 + 'a';
  answer += node % 26 + 'a';
  return answer;
}

// Check if a contains b, assumes both vectors are already sorted.
bool Contains(const std::vector<uint16_t> &a, const std::vector<uint16_t> &b) {
  const uint16_t* end_a = &a.back() + 1;
  const uint16_t* end_b = &b.back() + 1;

  const uint16_t* ptr_a = a.data();
  const uint16_t* ptr_b = b.data();

  while (ptr_a != end_a && ptr_b != end_b) {
    if (*ptr_a == *ptr_b) {
      ++ptr_b;
    }
    ++ptr_a;
  }

  return ptr_b == end_b;
}

template <size_t edge_count>
struct Graph {
  Graph(const std::string &input) {
    for (size_t i = 0; i < input.size(); i += 6) {
      const uint16_t start = (input[i + 0] - 'a') * 26 + (input[i + 1] - 'a');
      const uint16_t end = (input[i + 3] - 'a') * 26 + (input[i + 4] - 'a');

      AddBothEdges(start, end);
    }

    for (std::vector<uint16_t> &node_edges : edges) {
      std::sort(node_edges.begin(), node_edges.end());
    }
  }

  void AddBothEdges(const uint16_t start, const uint16_t end) {
    edges[start].push_back(end);
    edges[end].push_back(start);
  }

  // void PrintGraph() const {
  //   for (size_t node = 0; node < edges.size(); ++node) {
  //     if (not edges[node].empty()) {
  //       std::cout << Unhash(node) << ": ";

  //       for (const uint16_t other_node : edges[node]) {
  //         std::cout << Unhash(other_node) << ' ';
  //       }

  //       std::cout << '\n';
  //     }
  //   }
  // }

  std::array<std::vector<uint16_t>, edge_count> edges;
};

template <size_t edge_count>
struct DFS {
  DFS(const Graph<edge_count> &graph_) : graph(graph_) {}

  void Traverse(const uint16_t node) {
    visited[node] = true;

    if (not Contains(graph.edges[node], current_group)) {
      return;
    }

    current_group.push_back(node);

    if (current_group.size() > biggest_group.size()) {
      biggest_group = current_group;
    }

    for (const uint16_t other_node : graph.edges[node]) {
      if (not visited[other_node]) {
        Traverse(other_node);
      }
    }
    current_group.pop_back();
  }

  void Traverse() {
    for (uint16_t node = 0; node < graph.edges.size(); ++node) {
      if (not graph.edges[node].empty()) {
        std::fill(visited.begin() + node + 1, visited.end(), false);

        Traverse(node);
      }
    }
  }

  std::string TranslateBiggestClique() {
    std::sort(biggest_group.begin(), biggest_group.end());

    std::string answer;
    answer.reserve(biggest_group.size() * 3);

    for (const uint16_t node : biggest_group) {
      answer += node / 26 + 'a';
      answer += node % 26 + 'a';
      answer += ',';
    }
    answer.pop_back();

    return answer;
  }

  const Graph<edge_count> &graph;
  std::array<bool, edge_count> visited;

  std::vector<uint16_t> biggest_group;
  std::vector<uint16_t> current_group;
};

}  // namespace day23b

template <>
std::string Solve<2024, 23, 'B'>(std::stringstream input) {
  day23b::Graph<26 * 26> graph(input.str());

  day23b::DFS dfs(graph);
  dfs.Traverse();

  return dfs.TranslateBiggestClique();
}
