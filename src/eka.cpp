#include <algorithm>
#include <limits>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"
#include "eka.hpp"


namespace killdozer {

  // Why not std::vector<>* ?
  // In > C++11, std::vector has move-semantics, 
  // which means the local vector declared in function
  // will be moved on return and, in some cases, even 
  // the move can be elided by the compiler.

  std::vector<std::string> backtrace(
    std::unordered_map<std::string, std::string> const &parents,
    std::string const &source,
    std::string const &terminate
  ) {
    std::vector<std::string> pathTaken = { terminate };
    while( pathTaken.back() != source ) {
      pathTaken.push_back(parents.at(pathTaken.back()));
    }
    std::reverse(pathTaken.begin(), pathTaken.end());
    return pathTaken;
  }

  std::vector<std::string> bfs(
    killdozer::DAG const &dag,
    std::string const &source,
    std::string const &terminate
  ) {
    // Remember parents (for backtracing)
    std::unordered_map<std::string, std::string> parents;
    std::deque<std::string> queue;
    std::string currentNode;
    
    queue.push_back(source);
    while(!queue.empty()) {
      currentNode = queue.front();
      queue.pop_front();

      if (currentNode == terminate) {
        return backtrace(
          parents,
          source,
          terminate
        );
      }

      for (killdozer::Edge e: dag.adjacenceMap.at(currentNode)) {
        // Does queue already contains currentNode?
        bool visited = false;
        for (std::string n: queue) {
          if(currentNode == n) {
            visited = true;
          }
        }
        if(visited || e.maxFlow <= e.currentFlow) {
          continue;
        };

        parents[e.to] = currentNode;
        queue.push_back(e.to);   
      };
    };

    return std::vector<std::string>();
  }

  int calculateFlow(
    killdozer::DAG const &dag,
    std::vector<std::string> const &path
  ) {
    // Subsitute for Infinity in INT type
    int minFlow = std::numeric_limits<int>::max();

    for(std::vector<std::string>::size_type i = 0; i < path.size() - 1; i++) {
      std::string from = path[i];
      std::string to = path[i + 1];

      for (killdozer::Edge const &e: dag.adjacenceMap.at(from)) {
        if(e.to != to) {
          continue;
        }
        minFlow = std::min(minFlow, e.maxFlow - e.currentFlow);
      }
    }

    return minFlow;
  }

  void updateCurrentFlow(
    killdozer::DAG &dag,
    int const &currentFlow,
    std::vector<std::string> const &path
  ) {
    for(std::vector<std::string>::size_type i = 0; i < path.size() - 1; i++) {
      std::string from = path[i];
      std::string to = path[i + 1];

      for (killdozer::Edge &e: dag.adjacenceMap.at(from)) {
        if(e.to != to) {
          continue;
        }
        e.currentFlow = e.currentFlow + currentFlow;
      }
    }
  }

  int edmondsKarp(
    killdozer::DAG &dag,
    std::string source,
    std::string terminate
  ) {
    int flow = 0;

    std::vector<std::string> route = bfs(dag, source, terminate);
    while(!route.empty()) {
      int routeFlow = calculateFlow(dag, route);
      flow = flow + routeFlow;
      updateCurrentFlow(dag, routeFlow, route);
      route = bfs(dag, source, terminate);
    }

    return flow;
  }
}
