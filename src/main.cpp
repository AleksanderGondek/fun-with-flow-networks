#include <iostream>
#include <vector>

#include "input.hpp"
#include "graph.hpp"
#include "eka.hpp"
#include "mmcca.hpp"


int main() {
    // Test flow of the application
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
    
    killdozer::graph::DAG test_dag(edges);   
    int test_result = killdozer::eka::edmondsKarp(test_dag, "A", "G");
    std::cout << "Max flow is: " << test_result << std::endl;


    // Proper flow of the application
    // aka. read-in in the data
    // create graph and find min cost
    edges = {};
    killdozer::graph::DAG dag(edges);    
    killdozer::input::parseFromStdin(
        dag,
        "S", // Name of starting node/vertex
        "T" //  Name of termination node/vertex
    );
    int minCost = killdozer::mmcca::minimumMeanCycleCancelingAlgorithm(
        dag,
        "S",
        "T"
    );
    std::cout << "Min cost is: " << minCost << std::endl;
    return 0;
}
