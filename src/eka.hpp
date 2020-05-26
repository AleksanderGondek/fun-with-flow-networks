
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

  std::vector<std::string> backtrace(
    std::unordered_map<std::string, std::string> const &parents,
    std::string const &source,
    std::string const &terminate
  );

  std::vector<std::string> bfs(
    killdozer::DAG const &dag,
    std::string const &source,
    std::string const &terminate
  );

  int calculateFlow(
    killdozer::DAG const &dag,
    std::vector<std::string> const &path
  );

  void updateCurrentFlow(
    killdozer::DAG &dag,
    int const &currentFlow,
    std::vector<std::string> const &path
  );


  int edmondsKarp(
    killdozer::DAG &dag,
    std::string source,
    std::string terminate
  );
}

#endif
