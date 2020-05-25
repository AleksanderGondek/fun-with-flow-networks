#include <algorithm>
#include <limits>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"
#include "eka.hpp"


namespace Killdozer {
  std::vector<std::string> backtrace(
    std::unordered_map<std::string, std::string> const parents,
    std::string const source,
    std::string const terminate
  ) {
    std::vector<std::string> pathTaken = { terminate };
    while( pathTaken.back() != source ) {
      pathTaken.push_back(parents.at(pathTaken.back()));
    }
    std::reverse(pathTaken.begin(), pathTaken.end());
    return pathTaken;
  }

  std::vector<std::string> bfs(
    Killdozer::DAG const &dag,
    std::string const source,
    std::string const terminate
  ) {
    // Remember parents (and thus, visited vertices)
    std::unordered_map<std::string, std::string> parents;
    std::queue<std::string> queue;
    std::string currentNode;
    
    queue.push(source);
    while(!queue.empty()) {
      currentNode = queue.front();
      queue.pop();

      if (currentNode == terminate) {
        return backtrace(
          parents,
          source,
          terminate
        );
      }

      for (Edge e: dag.adjacenceMap.at(currentNode)) {
        // If already visited node or flow limit exceeded
        if(parents.contains(e.to) || e.maxFlow <= e.currentFlow) {
          continue;
        };

        parents[e.to] = currentNode;
        queue.push(e.to);   
      };
    };
  }

  int edmondsKarp(
    Killdozer::DAG &dag,
    std::string source,
    std::string terminate
  ) {
    int flow = 0;

    std::vector<std::string> route;
    route = bfs(dag, source, terminate);

    return flow;
  }
}
