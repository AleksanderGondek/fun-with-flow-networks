#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"


namespace Killdozer {

	DAG::DAG(std::vector<Edge> const &edges) {
		for (auto &edge: edges) {
			adjacenceMap[edge.from].push_back(edge);
		}
	}

	void displayGraph(DAG const &dag) {
		for (const auto& m : dag.adjacenceMap) {
			for (Edge e: m.second) {
				std::cout << "(";
				std::cout << e.from << " -> " << e.to << ", ";
				std::cout << "max: " << e.maxFlow << ", ";
				std::cout << "current: " << e.maxFlow << ", ";
				std::cout << ")";
				std::cout << std::endl;
			}
		}
	}

}