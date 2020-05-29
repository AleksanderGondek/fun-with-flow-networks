#include "catch.hpp"

#include <vector>

#include "../src/graph.hpp"
#include "../src/eka.hpp"

SCENARIO( " DAGs can have their maximum flow calculated", "[Edmonds–Karp Algorithm]" ) {

  GIVEN( "Wikipedia-based example dag" ) {
    std::vector<killdozer::graph::Edge> edges = {
        { "A", "B", 3, 0, 0, 0},
        { "A", "C", 3, 0, 0, 0},
        { "A", "D", 3, 0, 0, 0},
        { "B", "C", 4, 0, 0, 0},
        { "B", "E", 1, 0, 0, 0},
        { "C", "D", 1, 0, 0, 0},
        { "C", "E", 2, 0, 0, 0},
        { "D", "F", 6, 0, 0, 0},
        { "D", "E", 2, 0, 0, 0},
        { "E", "G", 1, 0, 0, 0},
        { "F", "G", 9, 0, 0, 0}
    };
    
    killdozer::graph::DAG dag(edges);

    REQUIRE( dag.adjacenceMap.size() == 7 );

    WHEN( "has maximum flow calculated" ) {
      int result = killdozer::eka::edmondsKarp(dag, "A", "G");

      THEN( "properly" ) {
        REQUIRE( result == 5 );
      }
    }
  }

  GIVEN ("DAG without connection to sink" ) {
    std::vector<killdozer::graph::Edge> edges = {
        { "A", "B", 6, 0, 0, 0},
        { "A", "C", 6, 0, 0, 0},
        { "D", "B", 1, 0, 0, 0},
        { "D", "C", 1, 0, 0, 0}
    };
    
    killdozer::graph::DAG dag(edges);

    REQUIRE( dag.adjacenceMap.size() == 4 );

    WHEN( "has maximum flow calculated" ) {
      int result = killdozer::eka::edmondsKarp(dag, "A", "D");

      THEN( "properly" ) {
        REQUIRE( result == 0 );
      }
    }
  }
}
