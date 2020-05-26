#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


namespace killdozer {
	namespace graph {

		struct Edge {
			std::string from, to; 
			int currentFlow, maxFlow;
		};

		class DAG {
			public:
				// Access times will be linear only with collisions, which there will be none
				// https://stackoverflow.com/questions/15470948/c-unordered-map-complexity
				std::unordered_map<std::string, std::vector<Edge>> adjacenceMap;  
				DAG(std::vector<Edge> const &edges);
			private:
				bool hasCycles(void);
		};

		void displayGraph(DAG const &dag);

	}
}

#endif
