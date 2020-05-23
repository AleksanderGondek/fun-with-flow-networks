
#ifndef FFA_HPP
#define FFA_HPP

#include "string"

#include "graph.hpp"


namespace Killdozer {
  int edmondsKarp(
    Killdozer::DAG &dag,
    std::string source,
    std::string terminate
  );
}

#endif
