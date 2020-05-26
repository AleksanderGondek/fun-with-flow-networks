#include "catch.hpp"

#include <vector>

#include "../src/graph.hpp"
#include "../src/eka.hpp"

SCENARIO( " DAGs can have their maximum flow calculated", "[Edmonds–Karp Algorithm]" ) {

  GIVEN( "Wikipedia-based example dag" ) {
    std::vector<Killdozer::Edge> edges = {
        { "A", "B", 0, 3},
        { "A", "C", 0, 3},
        { "A", "D", 0, 3},
        { "B", "C", 0, 4},
        { "B", "E", 0, 1},
        { "C", "D", 0, 1},
        { "C", "E", 0, 2},
        { "D", "F", 0, 6},
        { "D", "E", 0, 2},
        { "E", "G", 0, 1},
        { "F", "G", 0, 9}
    };
    
    Killdozer::DAG dag(edges);

    REQUIRE( dag.adjacenceMap.size() == 7 );

    WHEN( "has maximum flow calculated" ) {
      int result = edmondsKarp(dag, "A", "G");

      THEN( "properly" ) {
        REQUIRE( result == 5 );
      }
    }
  }

  GIVEN ("DAG without connection to sink" ) {
    std::vector<Killdozer::Edge> edges = {
        { "A", "B", 0, 6},
        { "A", "C", 0, 6},
        { "D", "B", 0, 1},
        { "D", "C", 0, 1},
    };
    
    Killdozer::DAG dag(edges);

    REQUIRE( dag.adjacenceMap.size() == 4 );

    WHEN( "has maximum flow calculated" ) {
      int result = edmondsKarp(dag, "A", "D");

      THEN( "properly" ) {
        REQUIRE( result == 0 );
      }
    }
  }
}
