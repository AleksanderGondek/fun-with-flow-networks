#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Killdozer {
	struct Edge {
		std::string from, to; 
		int weight;
	};

	typedef std::pair<std::string, int> Link;

	class DAG {
		public:
			std::unordered_map<std::string, std::vector<Link>> adjacenceMap;  
			DAG(std::vector<Edge> const &edges);
	};

	void displayGraph(DAG const &dag);
}

#endif
