#ifndef FFA_HPP
#define FFA_HPP

#include <algorithm>
#include <limits>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"


namespace killdozer {
  namespace eka {

    std::vector<std::string> backtrace(
      std::unordered_map<std::string, std::string> const &parents,
      std::string const &source,
      std::string const &terminate
    );

    std::vector<std::string> bfs(
      killdozer::graph::DAG const &dag,
      std::string const &source,
      std::string const &terminate
    );

    int calculateFlow(
      killdozer::graph::DAG const &dag,
      std::vector<std::string> const &path
    );

    void updateeka_currentFlow(
      killdozer::graph::DAG &dag,
      int const &eka_currentFlow,
      std::vector<std::string> const &path
    );

    // https://en.wikipedia.org/wiki/Edmonds–Karp_algorithm
    // Find maximum flow in a flow network in O(VE^2) time
    // Note: current implementation ignores minFlow param
    int edmondsKarp(
      killdozer::graph::DAG &dag,
      std::string source,
      std::string terminate
    );

  }
}

#endif
