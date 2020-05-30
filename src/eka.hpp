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

    void transposeMinFlowsVertices(
      killdozer::graph::DAG &dag
    );

    // Why not std::vector<>* ?
    // In > C++11, std::vector has move-semantics, 
    // which means the local vector declared in function
    // will be moved on return and, in some cases, even 
    // the move can be elided by the compiler.

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

    void update_eka_currentFlow(
      killdozer::graph::DAG &dag,
      int const &eka_currentFlow,
      std::vector<std::string> const &path
    );

    // https://en.wikipedia.org/wiki/Edmonds–Karp_algorithm
    // Find maximum flow in a flow network in O(VE^2) time
    //
    // Important!!
    // TODO: If dag contains edges with minimal flow specified
    // one needs to transpose it, into something that Edmond's Karp
    // algorithm can work with.
    // 
    // In short, we need to map single min_flow vertex into two. 
    // See: https://stackoverflow.com/questions/8751327/edmonds-karp-algorithm-for-a-graph-which-has-nodes-with-flow-capacities
    int edmondsKarp(
      killdozer::graph::DAG &dag,
      std::string source,
      std::string terminate
    );

  }
}

#endif
