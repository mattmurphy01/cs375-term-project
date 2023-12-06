#include "aStar.h"
#include "graph.h"
using namespace std;

bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnblocked(int grid[][COL], int row, int col) {
    if(grid[row][col] == 1) 
        return true;
    else
        return false;
}

bool isDest(int row, int col, Pair dest) {
    if(row == dest.first && col == dest.second)
        return true;
    else
        return false;
}

double calculateHVal(int row, int col, Pair dest) {
    return ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

void tracePath(Cell currCell[][COL], Pair dest) {
    cout << "Path: ";
    int row = dest.first;
    int col = dest.second;

    stack<Pair> Path;

    while (!(currCell[row][col].parent_i == row && currCell[row][col].parent_j == col)) {
        Path.push(make_pair(row, col));
        int temp_row = currCell[row][col].parent_i;
        int temp_col = currCell[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push(make_pair(row, col));
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        cout << "-> (" << p.first << ", " << p.second << ") ";
    }
    cout << endl;
    return;
}

void AStar(int grid[][COL], Pair src, Pair dest) {
    // check if source or destination are out of range
    if(isValid(src.first, src.second) == false) {
        cout << "Invalid Source Vertex" << endl;
        return;
    }
    if(isValid(src.first, src.second) == false) {
        cout << "Invalid Destination Vertex" << endl;
        return;
    }
    // check if source or destination is blocked
    if(isUnblocked(grid, src.first, src.second) == false || isUnblocked(grid, dest.first, dest.second) == false) {
        cout << "Soruce or destination node is blocked" << endl;
        return;
    }
    // check if destination is same as source
    if (isDest(src.first, src.second, dest) == true) {
        cout << "Already at destination node" << endl;
    }

    // initialize 2D array for the closed list to false values 
    bool closed[ROW][COL];
    memset(closed, false, sizeof(closed));

    // 2D array to hold details of each cell
    Cell cellDetails[ROW][COL];
    
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    //initialize start node
    int i = src.first;
    int j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    // initialize open list where each entry is <f, <i, j>>, f=g+h, i = row, j = column
    set<doublePair> open;
    // add starting cell to open list with f=0
    open.insert(make_pair(0.0, make_pair(i, j)));
    bool found = false;

    while(!open.empty()) {
        doublePair p = *open.begin();
        open.erase(open.begin());

        // add current vertex to closed list
        i = p.second.first;
        j = p.second.second;
        closed[i][j] = true;

        // new values of succesor cells
        double gNew, hNew, fNew;
        
        // first succesor (north)
        if(isValid(i - 1, j) == true) { // only process a valid cell
            if(isDest(i - 1, j, dest) == true) { // if dest == current successor
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i-1][j] == false && isUnblocked(grid, i-1, j) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHVal(i-1, j, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i-1, j)));
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        // 2nd succesor (south)
        if(isValid(i+1, j) == true) { // only process a valid cell
            if(isDest(i+1, j, dest) == true) { // if dest == current successor
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i+1][j] == false && isUnblocked(grid, i+1, j) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHVal(i+1, j, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i+1, j)));
                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }

        // 3rd succesor (east)
        if(isValid(i, j+1) == true) { // only process a valid cell
            if(isDest(i, j+1, dest) == true) { // if dest == current successor
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i][j+1] == false && isUnblocked(grid, i, j+1) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHVal(i, j+1, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i][j+1].f == FLT_MAX || cellDetails[i][j+1].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i, j+1)));
                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }

        // 4th succesor (west)
        if(isValid(i, j-1) == true) { // only process a valid cell
            if(isDest(i, j-1, dest) == true) { // if dest == current successor
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i][j-1] == false && isUnblocked(grid, i, j-1) == true) {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHVal(i, j-1, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i, j-1)));
                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }

        // 5th succesor (north east)
        if(isValid(i-1, j+1) == true) { // only process a valid cell
            if(isDest(i-1, j+1, dest) == true) { // if dest == current successor
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i-1][j+1] == false && isUnblocked(grid, i-1, j+1) == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHVal(i-1, j+1, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i-1][j+1].f == FLT_MAX || cellDetails[i-1][j+1].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i-1, j+1)));
                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                }
            }
        }

        // 6th succesor (north west)
        if(isValid(i-1, j-1) == true) { // only process a valid cell
            if(isDest(i-1, j-1, dest) == true) { // if dest == current successor
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i-1][j-1] == false && isUnblocked(grid, i-1, j-1) == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHVal(i-1, j-1, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i-1][j-1].f == FLT_MAX || cellDetails[i-1][j-1].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i-1, j-1)));
                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }

        // 7th succesor (south east)
        if(isValid(i+1, j+1) == true) { // only process a valid cell
            if(isDest(i+1, j+1, dest) == true) { // if dest == current successor
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i+1][j+1] == false && isUnblocked(grid, i+1, j+1) == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHVal(i+1, j+1, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i+1][j+1].f == FLT_MAX || cellDetails[i+1][j+1].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i+1, j+1)));
                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }

        // 8th succesor (south west)
        if(isValid(i+1, j-1) == true) { // only process a valid cell
            if(isDest(i+1, j-1, dest) == true) { // if dest == current successor
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                cout << "The destination is found" << endl;
                tracePath(cellDetails, dest);
                found = true;
                return;
            }
            // if successor is already on closed list or if its blocked ignore it, else do the following
            else if(closed[i+1][j-1] == false && isUnblocked(grid, i+1, j-1) == true) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculateHVal(i+1, j-1, dest);
                fNew = gNew + hNew;
                // if it isn't on open list add it, make current cell the parent cell of this cell and record f, g, h OR
                // if it is on open list, check if this paths f cost is better
                if(cellDetails[i+1][j-1].f == FLT_MAX || cellDetails[i+1][j-1].f > fNew) {
                    open.insert(make_pair(fNew, make_pair(i+1, j-1)));
                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    } // end while(!open.empty())

    // dest cell not found and open list is empty means no way to reach destination
    if(found == false) {
        cout << "Failed to reach destination" << endl;
    }
    return;
}