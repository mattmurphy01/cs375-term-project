#include <iostream>

#include "bellmanFord.h"
using namespace std;

BellmanFord::BellmanFord(int vertices, int edges) : V(vertices), E(edges) {}

void BellmanFord::addEdge(int from, int to, int weight) {
    Edge edge = {from, to, weight};
    edges.push_back(edge);
}

std::vector<int> BellmanFord::shortestPath(int source) {
    std::vector<int> distance(V, std::numeric_limits<int>::max());
    distance[source] = 0;

    // Relax all edges V-1 times
    for(int i = 0; i < V - 1; i++) {
        for(const auto& edge : edges) {
            int f = edge.from;
            int t = edge.to;
            int w = edge.weight;
            if(distance[f] != std::numeric_limits<int>::max() && distance[f] + w < distance[t]) {
                distance[t] = distance[f] + w;
            }
        }
    }

    // Check for negative weight cycles (total sum of edge weights around the cycle is negative)
    for(const auto& edge : edges) {
        int f = edge.from;
        int t = edge.to;
        int w = edge.weight;
        if(distance[f] != std::numeric_limits<int>::max() && distance[f] + w < distance[t]) {
            // Negative cycle found, return an empty vector indicating no shortest paths
            return std::vector<int>();
        }
    }

    return distance;
}