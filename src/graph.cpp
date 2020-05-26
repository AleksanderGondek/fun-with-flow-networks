#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"


namespace killdozer {

	DAG::DAG(std::vector<Edge> const &edges) {
		for (Edge const &edge: edges) {
			adjacenceMap[edge.from].push_back(edge);
			// Ensure all verticies have their edge list
			adjacenceMap[edge.to];
		}

		if(hasCycles()) {
			throw std::domain_error(
				"Resulting graph would have contained cycles, aborting!"
			);
		}
	}

	bool DAG::hasCycles() {
		// TODO: Maybe one day :)
		return false;
	}

	void displayGraph(DAG const &dag) {
		for (const auto& m : dag.adjacenceMap) {
			for (Edge e: m.second) {
				std::cout << "(";
				std::cout << e.from << " -> " << e.to << ", ";
				std::cout << "max: " << e.maxFlow << ", ";
				std::cout << "current: " << e.currentFlow << ", ";
				std::cout << ")";
				std::cout << std::endl;
			}
		}
	}

}