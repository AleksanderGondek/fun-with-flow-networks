#include <iostream>
#include <vector>

#include "graph.hpp"
#include "eka.hpp"


int main() {
    std::vector<killdozer::graph::Edge> edges = {
        { "A", "B", 3, 0, 0, 0},
        { "A", "C", 3, 0, 0, 0},
        { "A", "D", 3, 0, 0, 0},
        { "B", "C", 4, 0, 0, 0},
        { "B", "E", 1, 0, 0, 0},
        { "C", "D", 1, 0, 0, 0},
        { "C", "E", 2, 0, 0, 0},
        { "D", "F", 6, 0, 0, 0},
        { "D", "E", 2, 0, 0, 0},
        { "E", "G", 1, 0, 0, 0},
        { "F", "G", 9, 0, 0, 0}
    };
    
    killdozer::graph::DAG dag(edges);   
    int result = killdozer::eka::edmondsKarp(dag, "A", "G");
    std::cout << result << std::endl;

    return 0;
}
