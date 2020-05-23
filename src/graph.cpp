#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"

namespace Killdozer {

	DAG::DAG(std::vector<Edge> const &edges) {
		for (auto &edge: edges) {
			std::string from = edge.from;
			std::string to = edge.to;
			int weight = edge.weight;

			adjacenceMap[from].push_back(make_pair(to, weight));
		}
	}

	void displayGraph(DAG const &dag) {
		for (const auto& m : dag.adjacenceMap) {
			for (Link l: m.second) {
				std::cout << "(";
				std::cout << m.first;
				std::cout << ", ";
				std::cout << l.first;
				std::cout << ", ";
				std::cout << l.second;
				std::cout << ")";
				std::cout << std::endl;
			}
		}
	}

}