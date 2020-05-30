#include <algorithm>
#include <limits>
#include <deque>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"
#include "eka.hpp"


namespace killdozer {
  namespace eka {

    void transposeMinFlowsVertices(
      killdozer::graph::DAG &dag
    ) {
    }

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
      killdozer::graph::DAG const &dag,
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

        for (killdozer::graph::Edge e: dag.adjacenceMap.at(currentNode)) {
          // Does queue already contains currentNode?
          bool visited = false;
          for (std::string n: queue) {
            if(currentNode == n) {
              visited = true;
            }
          }
          if(visited || e.maxFlow <= e.eka_currentFlow) {
            continue;
          };

          parents[e.to] = currentNode;
          queue.push_back(e.to);   
        };
      };

      return std::vector<std::string>();
    }

    int calculateFlow(
      killdozer::graph::DAG const &dag,
      std::vector<std::string> const &path
    ) {
      // Subsitute for Infinity in INT type
      int minFlow = std::numeric_limits<int>::max();

      for(std::vector<std::string>::size_type i = 0; i < path.size() - 1; i++) {
        std::string from = path[i];
        std::string to = path[i + 1];

        for (killdozer::graph::Edge const &e: dag.adjacenceMap.at(from)) {
          if(e.to != to) {
            continue;
          }
          minFlow = std::min(minFlow, e.maxFlow - e.eka_currentFlow);
        }
      }

      return minFlow;
    }

    void update_eka_currentFlow(
      killdozer::graph::DAG &dag,
      int const &currentFlow,
      std::vector<std::string> const &path
    ) {
      for(std::vector<std::string>::size_type i = 0; i < path.size() - 1; i++) {
        std::string from = path[i];
        std::string to = path[i + 1];

        for (killdozer::graph::Edge &e: dag.adjacenceMap.at(from)) {
          if(e.to != to) {
            continue;
          }
          e.eka_currentFlow = e.eka_currentFlow + currentFlow;
        }
      }
    }

    int edmondsKarp(
      killdozer::graph::DAG &dag,
      std::string source,
      std::string terminate
    ) {
      transposeMinFlowsVertices(dag);

      int flow = 0;

      std::vector<std::string> route = bfs(dag, source, terminate);
      while(!route.empty()) {
        int routeFlow = calculateFlow(dag, route);
        flow = flow + routeFlow;
        update_eka_currentFlow(dag, routeFlow, route);
        route = bfs(dag, source, terminate);
      }

      return flow;
    }

  }
}
