
#ifndef FFA_HPP
#define FFA_HPP

#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_set>

#include "graph.hpp"


namespace Killdozer {

  typedef std::tuple<int, std::stack<std::string>> bfsResponse;

  int edmondsKarp(
    Killdozer::DAG &dag,
    std::string source,
    std::string terminate
  );
}

#endif
