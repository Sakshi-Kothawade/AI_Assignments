#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node {
    int x, y;       // Position
    int g, h, f;    // Costs
    Node* parent;   // Pointer to parent node
};

// Comparator for priority queue (lowest f first)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

// Heuristic: Manhattan Distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if position is inside grid and not blocked
bool isValid(int x, int y, vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    return (x >= 0 && y >= 0 && x < rows && y < cols && grid[x][y] == 0);
}

// A* Algorithm
vector<pair<int,int>> aStar(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<Node*, vector<Node*>, Compare> openList;
    vector<vector<bool>> closedList(rows, vector<bool>(cols, false));

    Node* startNode = new Node{start.first, start.second, 0, 0, 0, NULL};
    startNode->h = heuristic(start.first, start.second, goal.first, goal.second);
    startNode->f = startNode->g + startNode->h;
    openList.push(startNode);

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        int x = current->x;
        int y = current->y;
        closedList[x][y] = true;

        // Goal reached
        if (x == goal.first && y == goal.second) {
            vector<pair<int,int>> path;
            while (current != NULL) {
                path.push_back({current->x, current->y});
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny, grid) && !closedList[nx][ny]) {
                int gNew = current->g + 1;
                int hNew = heuristic(nx, ny, goal.first, goal.second);
                int fNew = gNew + hNew;

                Node* neighbor = new Node{nx, ny, gNew, hNew, fNew, current};
                openList.push(neighbor);
            }
        }
    }

    return {}; // No path found
}

// Main function
int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    pair<int,int> start = {0, 0};
    pair<int,int> goal = {4, 4};

    vector<pair<int,int>> path = aStar(grid, start, goal);

    if (path.empty()) {
        cout << "No path found!" << endl;
    } else {
        cout << "Path found: ";
        for (int i = 0; i < path.size(); i++) {
            cout << "(" << path[i].first << "," << path[i].second << ") ";
        }
        cout << endl;
    }

    return 0;
}
