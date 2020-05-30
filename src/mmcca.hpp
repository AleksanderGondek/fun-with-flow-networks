#ifndef MMCCA_HPP
#define MMCCA_HPP

#include <string>

#include "graph.hpp"


namespace killdozer {
  namespace mmcca {

    int minimumMeanCycleCancelingAlgorithm(
      killdozer::graph::DAG &dag,
      std::string source,
      std::string terminate
    );

  }
}

#endif
