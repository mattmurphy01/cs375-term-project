#include <iostream>
#include <chrono>

//#include "test.h"
#include "bellmanFord.h"
#include "aStar.h"
using namespace std;

int main(int argc, char const *argv[]) {
        /* Bellman-Ford Algorithm */
    // start runtime
    auto start = std::chrono::high_resolution_clock::now();

    int V = 5; // Number of vertices in graph
    int E = 8; // Number of edges in graph
    
    // initialize graph
    BellmanFord graph(V, E);
    
    // graph to test
    graph.addEdge(0, 1, -1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 1);
    graph.addEdge(4, 3, -3);

    int from = 0;   // source node
 
    std::vector<int> shortestDistances = graph.shortestPath(from);

    if (shortestDistances.empty()) std::cout << "Graph contains negative weight cycle!\n";
    else {
        std::cout << "Shortest distances from vertex " << from << " to other vertices:\n";
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex " << i << ": ";
            if (shortestDistances[i] == std::numeric_limits<int>::max()) std::cout << "INF\n";  // path from source to destination does not exist
            else std::cout << shortestDistances[i] << "\n"; // shortest distance from source to destination
        }
    }

    //end runtime
    auto end = std::chrono::high_resolution_clock::now();
    
    //calculate runtime
    std::chrono::duration<double> duration = end - start;
    std::cout << "Runtime (Bellman-Ford): " << duration.count() << " seconds" << std::endl;

    int grid[ROW][COL]
        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

    Pair src = make_pair(8,0);
    Pair dest = make_pair(0,0);
    AStar(grid, src, dest);

    //AStar();
    return 0;
}