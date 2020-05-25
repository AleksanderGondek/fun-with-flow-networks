#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_set>

#include "graph.hpp"
#include "eka.hpp"


namespace Killdozer {
  bfsResponse bfs(
    Killdozer::DAG const &dag,
    std::string source,
    std::string terminate
  ) {
    // Subsitute for Infinity in INT type
    int minFlow = std::numeric_limits<int>::max();

    // Remember visited vertices
    std::unordered_set<std::string> visitedVertices;

    std::queue<std::stack<std::string>> q;
    
    std::stack<std::string> a;
    a.push(source);
    q.push(a);

    while(!q.empty()){
      std::stack<std::string> path = q.front();
      q.pop();
      
      std::string node = path.top();

      if(node == terminate) {
        return std::make_tuple(minFlow, path);
      };

      for (Edge e: dag.adjacenceMap.at(node)) {
        // If max flow is already established or vertice was visited
        if(e.maxFlow <= e.currentFlow || visitedVertices.contains(e.to)) {
          continue;
        };
        visitedVertices.insert(e.to);
        minFlow = std::min(minFlow, e.maxFlow - e.currentFlow);

        std::stack<std::string> newPath = path;
        path.push(e.to);
        q.push(newPath);
      };
    }
    // What if code will somehow get here?!
  }

  int edmondsKarp(
    Killdozer::DAG &dag,
    std::string source,
    std::string terminate
  ) {
    int flow = 0;

    // While a route from source to sink exists
    // and is valid
    //   Add curr flow to edges making up the route
    //   Increment flow by value which reached sink
    //   repeat 
    // If a route doesn't exist
    //   return flow

    std::string from;
    std::string to;

    int routeFlow = 0;
    std::stack<std::string> route;
    bfsResponse response;
    
    response = bfs(dag, source, terminate);
    routeFlow = std::get<0>(response);
    route = std::get<1>(response);
    
    flow = flow + routeFlow;

    while(!route.empty()) {
      // Ugly code - begin
      // Take 2 items at once from stack
      while(!route.empty()) {
        if(!to.empty()) {
          // to was not previously set
          from = to;
          to = route.top();
          route.pop();
        } else {
          from = route.top();
          route.pop();
          to = route.top();
          route.pop();
        }

        // It's rather not possible the map doesn't contain
        // path already traveled
        std::vector<Edge> connections = dag.adjacenceMap.at(from);
        for(Edge e: connections) {
          if(e.to != to) {
            continue;
          } else {
            e.currentFlow = e.currentFlow + routeFlow;
            break;
          }          
        }
      }

      response = bfs(dag, source, terminate);
      routeFlow = std::get<0>(response);
      route= std::get<1>(response);

      flow = flow + routeFlow;

      std::cout << "------" << std::endl << std::endl;
      Killdozer::displayGraph(dag);
    };

    return flow;
  }
}
