#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
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

// Check if a contains b, assumes both vectors are already sorted.
bool Contains(const std::vector<uint16_t> &a, const std::vector<std::pair<uint16_t, uint16_t>> &b) {
  const uint16_t* end_a = a.data() + a.size();
  const std::pair<uint16_t, uint16_t>* end_b = b.data() + b.size() - 1;

  const uint16_t* ptr_a = a.data();
  const std::pair<uint16_t, uint16_t>* ptr_b = b.data();

  while (ptr_a != end_a && ptr_b != end_b) {
    if (*ptr_a == ptr_b->first) {
      ++ptr_b;
    }
    ++ptr_a;
  }

  return ptr_b == end_b;
}

struct Graph {
  Graph(const std::vector<std::string> &lines) {
    edges.resize(26 * 26);

    for (const std::string &line : lines) {
      const uint16_t start = (line[0] - 'a') * 26 + (line[1] - 'a');
      const uint16_t end = (line[3] - 'a') * 26 + (line[4] - 'a');

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
  DFS(const Graph &graph_) : graph(graph_) {}

  void Traverse() {
    std::vector<std::pair<uint16_t, uint16_t>> current_group;
    std::vector<bool> visited(graph.edges.size());

    for (uint16_t node = 0; node < graph.edges.size(); ++node) {
      if (not graph.edges[node].empty()) {
        std::fill(visited.begin() + node + 1, visited.end(), false);

        current_group.emplace_back(node, 0);

        while (not current_group.empty()) {
          const uint16_t node = current_group.back().first;

          visited[node] = true;

          const std::vector<uint16_t> &node_edges = graph.edges[node];

          if (Contains(node_edges, current_group)) {
            if (current_group.size() > biggest_group.size()) {
              biggest_group.resize(current_group.size());

              for (size_t i = 0; i < current_group.size(); ++i) {
                biggest_group[i] = current_group[i].first;
              }
            }

            uint16_t &starting_index = current_group.back().second;
            while (starting_index != node_edges.size() && visited[node_edges[starting_index]]) {
              ++starting_index;
            }

            if (starting_index != node_edges.size()) {
              current_group.emplace_back(node_edges[starting_index], 0);
              continue;
            }
          }

          current_group.pop_back();
        }
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

  const Graph &graph;

  std::vector<uint16_t> biggest_group;
};

int main(const int argc, const char* const* argv) {
  int ITERATIONS = 1;
  if (argc == 2) {
    ITERATIONS = std::stoi(argv[1]);
  }

  std::ifstream fin("data/23.txt");

  std::vector<std::string> lines;

  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  std::string answer;

  my::Timer timer;

  for (int _ = 0; _ != ITERATIONS; ++_) {
    Graph graph(lines);

    DFS dfs(graph);
    dfs.Traverse();

    answer = dfs.TranslateBiggestClique();

    if (answer != "bd,bu,dv,gl,qc,rn,so,tm,wf,yl,ys,ze,zr") {
      std::cout << "Answer: " << answer << '\n';
      std::cerr << "Expect: bd,bu,dv,gl,qc,rn,so,tm,wf,yl,ys,ze,zr\n";
      std::cerr << "BAD ANSWER!!!\n";
      return 1;
    }
  }

  const double elapsed_time = timer.ElapsedTime() / ITERATIONS;

  std::cout << "Answer: " << answer << '\n';
  std::cout << std::fixed << std::setprecision(3) << elapsed_time * 1e6 << " us\n";

  return 0;
}
