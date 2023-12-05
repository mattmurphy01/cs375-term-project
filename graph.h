#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>

struct Edge {
    int from;
    int to;
    int weight;
};

class Graph {
public:
    Graph(int vertices);
    void addEdge(int from, int to, int weight);
    void printGraph();

private:
    std::vector<std::list<Edge>> adjList; // Adjacency list representation
};

#endif // GRAPH_H