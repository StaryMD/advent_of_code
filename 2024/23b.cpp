#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"

std::string Unhash(const uint16_t node) {
  std::string answer;
  answer += node / 26 + 'a';
  answer += node % 26 + 'a';
  return answer;
}

struct Graph {
  Graph(const std::vector<std::string> &lines) {
    edges.resize(26 * 26);

    for (const std::string &line : lines) {
      const uint16_t start = (line[0] - 'a') * 26 + (line[1] - 'a');
      const uint16_t end = (line[3] - 'a') * 26 + (line[4] - 'a');

      AddBothEdges(start, end);
    }
  }

  void AddBothEdges(const uint16_t start, const uint16_t end) {
    edges[start].push_back(end);
    edges[end].push_back(start);
  }

  bool IsConnected(std::string_view start, std::string_view end) const {
    const uint16_t _start = (start[0] - 'a') * 26 + (start[1] - 'a');
    const uint16_t _end = (end[0] - 'a') * 26 + (end[1] - 'a');

    return IsConnected(_start, _end);
  }

  bool IsConnected(const uint16_t start, const uint16_t end) const {
    const std::vector<uint16_t> &start_edges = edges[start];

    return std::find(start_edges.cbegin(), start_edges.cend(), end) != start_edges.cend();
  }

  void PrintGraph() const {
    for (size_t node = 0; node < edges.size(); ++node) {
      if (not edges[node].empty()) {
        std::cout << Unhash(node) << ": ";

        for (const uint16_t other_node : edges[node]) {
          std::cout << Unhash(other_node) << ' ';
        }

        std::cout << '\n';
      }
    }
  }

  std::vector<std::vector<uint16_t>> edges;
  std::vector<uint16_t> unique_nodes;
};

struct DFS {
  DFS(const Graph &graph_) : graph(graph_) {
    visited.resize(graph.edges.size());
  }

  void ClearVisits() {
    std::fill(visited.begin(), visited.end(), false);
  }

  void Traverse(const uint16_t node) {
    if (not visited[node]) {
      current_group.push_back(node);
      visited[node] = true;

      for (size_t i = 0; i < current_group.size() - 1; ++i) {
        const uint16_t other_node = current_group[i];

        if (not graph.IsConnected(other_node, node)) {
          current_group.pop_back();
          return;
        }
      }

      if (current_group.size() > biggest_group.size()) {
        biggest_group = current_group;
      }

      for (const uint16_t other_node : graph.edges[node]) {
        Traverse(other_node);
      }
      current_group.pop_back();
    }
  }

  void Traverse() {
    for (uint16_t node = 0; node < graph.edges.size(); ++node) {
      if (not graph.edges[node].empty()) {
        ClearVisits();

        Traverse(node);
      }
    }
  }

  std::string TranslateBiggestClique() {
    std::sort(biggest_group.begin(), biggest_group.end(), [](const uint16_t a, const uint16_t b) {
      return a / 26 < b / 26 || (a / 26 == b / 16 && a % 26 < b % 26);
    });

    std::string answer;
    std::vector<std::string> computers;

    for (const uint16_t node : biggest_group) {
      answer += node / 26 + 'a';
      answer += node % 26 + 'a';
      answer += ',';
    }
    answer.pop_back();

    return answer;
  }

  const Graph &graph;
  std::vector<bool> visited;

  std::vector<uint16_t> biggest_group;
  std::vector<uint16_t> current_group;
};

int main() {
  my::Timer timer;

  std::ifstream fin("data/23.txt");

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  Graph graph(lines);

  DFS dfs(graph);
  dfs.Traverse();

  const std::string answer = dfs.TranslateBiggestClique();

  std::cout << "Answer: " << answer << '\n';

  const double elapsed_time = timer.ElapsedTime();

  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e6 << " us\n";

  return 0;
}
