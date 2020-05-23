#include <iostream>
#include <vector>

#include "graph.hpp"


int main() {
    std::cout << "Hello World!" << std::endl;

    std::vector<Killdozer::Edge> edges = {
        { "A", "B", 1}
    };
    
    Killdozer::DAG dag(edges);
    Killdozer::displayGraph(dag);    

    return 0;
}
