#include <iostream>
#include <vector>

#include "graph.hpp"
#include "eka.hpp"


int main() {
    std::cout << "Hello World!" << std::endl;

    std::vector<killdozer::Edge> edges = {
        { "A", "B", 0, 3},
        { "A", "C", 0, 3},
        { "A", "D", 0, 3},
        { "B", "C", 0, 4},
        { "B", "E", 0, 1},
        { "C", "D", 0, 1},
        { "C", "E", 0, 2},
        { "D", "F", 0, 6},
        { "D", "E", 0, 2},
        { "E", "G", 0, 1},
        { "F", "G", 0, 9}
    };
    
    killdozer::DAG dag(edges);   
    int result = edmondsKarp(dag, "A", "G");
    std::cout << result << std::endl;

    return 0;
}
