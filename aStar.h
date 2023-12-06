#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <vector>
// #include <limits>
// #include <set>
// #include <cmath>
// #include <stack>
#include <bits/stdc++.h>

#include "graph.h"
using namespace std;

#define ROW 10
#define COL 10

typedef pair<int, int> Pair;
typedef pair<double, pair<int, int>> doublePair;
typedef pair<double, int> dPair;

struct Node {
    int id;
    vector<pair<int, double>> neighbors;
};

/*
// holds necessary parameters for algorithm
struct Cell {
    // row and column of parent
    int parent_i, parent_j;
    // f = g + h, g = cost from start to current node, h = estimated cost from current node to dest node
    int f, g, h;
};
*/

// holds necessary parameters for algorithm
struct Cell {
    // row and column of parent
    int parent_id;
    // f = g + h, g = cost from start to current node, h = estimated cost from current node to dest node
    double f, g, h;
};

// checks if a node is a valid cell, is row and column number in range?
// bool isValid(int row, int col);
bool isValid(int nodeId);

// checks if cell is blocked or not
// bool isUnblocked(int grid[][COL], int row, int col);
bool isUnblocked(int nodeId);

// checks if destination cell was reached
// bool isDest(int row, int col, Pair dest);

// calculate utility value 'h'
// double calculateHVal(int row, int col, Pair dest);
double calculateHVal(int nodeId, int destId);

// trace path from source to destination
// void tracePath(Cell cellDetails[][COL], Pair dest);
void tracePath(map<int, Node> nodeDetails, int destId);

// shortest path A* algorithm
// void AStar(int grid[][COL], Pair src, Pair dest);
double AStar(const vector<Node>& graph, int srcId, int destId);

#endif //ASTAR_H