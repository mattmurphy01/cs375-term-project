#include <iostream>
#include <chrono>

//#include "test.h"
#include "bellmanFord.h"
#include "aStar.h"
// #include "random-graph.cpp"
using namespace std;

struct GraphData {
    vector<Node> nodes; // A*
    vector<Edge> edges; // Bellman-Ford
};

vector<Node> createGraph(int numRows, int numCols, double defaultCost = 1.0) {
    int numNodes = numRows * numCols;
    vector<Node> graph(numNodes);

    for (int i = 0; i < numNodes; ++i) {
        graph[i].id = i;
        int row = i / numCols;
        int col = i % numCols;

        // Connect to the left neighbor
        if (col > 0) {
            int leftNeighbor = i - 1;
            graph[i].neighbors.push_back(make_pair(leftNeighbor, defaultCost));
        }

        // Connect to the right neighbor
        if (col < numCols - 1) {
            int rightNeighbor = i + 1;
            graph[i].neighbors.push_back(make_pair(rightNeighbor, defaultCost));
        }

        // Connect to the top neighbor
        if (row > 0) {
            int topNeighbor = i - numCols;
            graph[i].neighbors.push_back(make_pair(topNeighbor, defaultCost));
        }

        // Connect to the bottom neighbor
        if (row < numRows - 1) {
            int bottomNeighbor = i + numCols;
            graph[i].neighbors.push_back(make_pair(bottomNeighbor, defaultCost));
        }
    }

    return graph;
}

/*
vector<Node> createRandomGraph(int n) {
    vector<Node> graph(n);

    srand(time(nullptr));

    for (int i = 0; i < n; ++i) {
        graph[i].id = i;
        int numConnections = rand() % 10 + 1;
        for(int j = 0; j < numConnections; ++j) {
            int neighborId = rand() % n;

            if(i != neighborId && find_if(graph[i].neighbors.begin(), graph[i].neighbors.end(), [neighborId](const pair<int, double>& p) { return p.first == neighborId; }) == graph[i].neighbors.end()) {

                double weight = rand() %  100 + 1;
                graph[i].neighbors.push_back(make_pair(neighborId, weight));
            }
        }
    }
    return graph;
}
*/

GraphData createRandomGraph(int numNodes, int numEdges) {
    GraphData graphData;
    graphData.nodes.resize(numNodes);

    srand(time(nullptr));

    // Populate edges
    while (graphData.edges.size() < numEdges) {
        int from = rand() % numNodes;
        int to = rand() % numNodes;

        // Avoid self-loops and ensure limited number of outgoing connections
        if (from != to && graphData.nodes[from].neighbors.size() < 10) {
            double weight = rand() % 100 + 1;  // Random weight between 1 and 100

            // Add to Node structure for A*
            graphData.nodes[from].neighbors.push_back(std::make_pair(to, weight));

            // Add to Edge structure for Bellman-Ford
            Edge edge = {from, to, static_cast<int>(weight)};
            graphData.edges.push_back(edge);
        }
    }

    return graphData;
}


void printGraph(const vector<Node>& graph) {
    for(const Node& node : graph) {
        cout << "Node " << node.id << " connects to: ";
        for(const auto& neighbor : node.neighbors) {
            cout << "[Node " << neighbor.first << ", Weight: " << neighbor.second << "] ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[]) {
    /* Bellman-Ford Algorithm */
    std::cout << "***** Bellman-Ford Algorithm test *****\n";
    // start runtime
    auto start1 = std::chrono::high_resolution_clock::now();

    int V = 5; // Number of vertices in graph
    int E = 8; // Number of edges in graph
    
    // initialize graph
    BellmanFord graph(V, E);
    
    // graph to test
    
    /*
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 2);
    graph.addEdge(3, 2, 5);
    graph.addEdge(3, 1, 2); // 3
    graph.addEdge(4, 3, 3);
    */

    
    graph.addEdge(0,2,6);
    graph.addEdge(0,2,2);
    graph.addEdge(1,2,2);
    graph.addEdge(1,3,5);
    graph.addEdge(2,3,2);
    graph.addEdge(3,4,3);
    

    /*
    graph.addEdge(0, 1, 7);
    graph.addEdge(0, 2, 4);

    graph.addEdge(1, 0, 7);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 5);

    graph.addEdge(2, 0, 4);
    graph.addEdge(2, 5, 8);

    graph.addEdge(3, 1, 2);
    graph.addEdge(3, 6, 9);

    graph.addEdge(4, 1, 5);
    graph.addEdge(4, 7, 6);

    graph.addEdge(5, 2, 8);
    graph.addEdge(5, 8, 3);

    graph.addEdge(6, 3, 9);
    graph.addEdge(6, 9, 1);

    graph.addEdge(7, 4, 6);
    graph.addEdge(7, 8, 7);

    graph.addEdge(8, 5, 3);
    graph.addEdge(8, 7, 7);
    graph.addEdge(8, 9, 4);

    graph.addEdge(9, 6, 1);
    graph.addEdge(9, 8, 4);
    */

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
    auto end1 = std::chrono::high_resolution_clock::now();
    
    //calculate runtime
    std::chrono::duration<double> duration1 = end1 - start1;
    std::cout << "Runtime (Bellman-Ford): " << duration1.count() << " seconds" << std::endl;

    /* A* Algorithm */
    std::cout << "\n***** A* Algorithm test ******\n";

    // start runtime
    auto start2 = std::chrono::high_resolution_clock::now();
        
    vector<Node> graph1;
    graph1.resize(5);

    graph1[0].id = 0;
    graph1[0].neighbors.push_back(std::make_pair(1, 6.0));
    graph1[0].neighbors.push_back(std::make_pair(2, 2.0));

    graph1[1].id = 1;
    graph1[1].neighbors.push_back(std::make_pair(0, 6.0));
    graph1[1].neighbors.push_back(std::make_pair(2, 2.0));
    graph1[1].neighbors.push_back(std::make_pair(3, 5.0));

    graph1[2].id = 2;
    graph1[2].neighbors.push_back(std::make_pair(0, 2.0));
    graph1[2].neighbors.push_back(std::make_pair(1, 2.0));
    graph1[2].neighbors.push_back(std::make_pair(3, 2.0));

    graph1[3].id = 3;
    graph1[3].neighbors.push_back(std::make_pair(1, 5.0));
    graph1[3].neighbors.push_back(std::make_pair(2, 2.0));
    graph1[3].neighbors.push_back(std::make_pair(4, 3.0));

    graph1[4].id = 4;
    graph1[4].neighbors.push_back(std::make_pair(3, 3.0));

    int numNodes = 100;
    int numEdges = 100;
    // vector<Node> randomGraph = createRandomGraph(numNodes);
    GraphData randomGraph = createRandomGraph(numNodes, numEdges);
    printGraph(randomGraph.nodes);

    int fromV = 3;
    int toV = 10;
    int result = AStar(randomGraph.nodes, fromV, toV);
    cout << "Shortest path from " << fromV << " to " << toV << " is " << result << " length" << endl;

    //end runtime
    auto end2 = std::chrono::high_resolution_clock::now();
    
    //calculate runtime
    std::chrono::duration<double> duration2 = end2 - start2;
    std::cout << "Runtime (A*): " << duration2.count() << " seconds" << std::endl;

    return 0;
}