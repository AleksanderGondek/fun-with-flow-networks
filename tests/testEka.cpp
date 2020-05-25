#include "catch.hpp"

#include <vector>

#include "../src/graph.hpp"
#include "../src/eka.hpp"

SCENARIO( " graphs can have their maximum flow calculated", "[Edmonds–Karp Algorithm]" ) {

  GIVEN( "A simple graph from wikipedia" ) {
    std::vector<Killdozer::Edge> edges = {
        { "A", "B", 0, 3},
        { "A", "D", 0, 3},
        { "B", "C", 0, 4},
        { "C", "A", 0, 3},
        { "C", "D", 0, 1},
        { "C", "E", 0, 2},
        { "D", "F", 0, 6},
        { "D", "E", 0, 2},
        { "E", "B", 0, 1},
        { "E", "G", 0, 1},
        { "F", "G", 0, 9}
    };
    
    // This graph is not Acyclic, but should do well as example
    Killdozer::DAG g(edges);

    REQUIRE( g.adjacenceMap.size() == 6 );


    WHEN( "maximum flow is calculated" ) {
      int result = edmondsKarp(g, "A", "F");
      //int result = 5;

      THEN( "result is accurate" ) {
        REQUIRE( result == 5 );
      }
    }
  }
}