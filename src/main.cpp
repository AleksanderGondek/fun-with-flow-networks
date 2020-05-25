#include <iostream>
#include <vector>

#include "graph.hpp"
#include "eka.hpp"


int main() {
    std::cout << "Hello World!" << std::endl;

    std::vector<Killdozer::Edge> edges = {
        { "A", "B", 0, 3},
        { "A", "D", 0, 3},
        { "B", "C", 0, 4},
        { "C", "A", 0, 3},
        { "C", "D", 0, 1},
        { "C", "E", 0, 2},
        { "D", "F", 0, 6},
        { "D", "E", 0, 2},
        { "E", "B", 0, 1},
        { "E", "G", 0, 1},
        { "F", "G", 0, 9}
    };
    
    Killdozer::DAG dag(edges);
    Killdozer::displayGraph(dag);
    int result = edmondsKarp(dag, "A", "G");

    return 0;
}
