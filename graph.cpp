#include <iostream>
#include <vector>
#include <list>

#include "graph.h"
using namespace std;

Graph::Graph(int vertices) : adjList(vertices) {}

void Graph::addEdge(int from, int to, int weight) {
    Edge edge = {to, weight};
    adjList[from].push_back(edge);
}

void Graph::printGraph() {
    int v = 0;
    for (auto &edges : adjList) {
        std::cout << "Vertex " << v << " has edges to:\n";
        for (auto &edge : edges) {
            std::cout << "\tVertex " << edge.to << " with weight " << edge.weight << "\n";
        }
        v++;
    }
}