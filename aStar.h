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

#define ROW 9
#define COL 10

// int, int pair shortcut
typedef pair<int, int> Pair;
// int, pair<int, int> shortcut
typedef pair<double, pair<int, int>> doublePair;

// holds necessary parameters for algorithm
struct Cell {
    // row and column of parent
    int parent_i, parent_j;
    // f = g + h, g = cost from start to current node, h = estimated cost from current node to dest node
    int f, g, h;
};

// checks if a node is a valid cell, is row and column number in range?
bool isValid(int row, int col);

// checks if cell is blocked or not
bool isUnblocked(int grid[][COL], int row, int col);

// checks if destination cell was reached
bool isDest(int row, int col, Pair dest);

// calculate utility value 'h'
double calculateHVal(int row, int col, Pair dest);

// trace path from source to destination
void tracePath(Cell cellDetails[][COL], Pair dest);

// shortest path A* algorithm
void AStar(int grid[][COL], Pair src, Pair dest);

#endif //ASTAR_H