#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


namespace Killdozer {
	struct Edge {
		std::string from, to; 
		int currentFlow, maxFlow;
	};

	class DAG {
		public:
			std::unordered_map<std::string, std::vector<Edge>> adjacenceMap;  
			DAG(std::vector<Edge> const &edges);
	};

	void displayGraph(DAG const &dag);
}

#endif
