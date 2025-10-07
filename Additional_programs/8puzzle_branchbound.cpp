#include <bits/stdc++.h>
using namespace std;

#define N 3

// State space tree node
struct Node {
    Node* parent;
    int mat[N][N];
    int x, y;     // Coordinates of blank tile (0)
    int cost;     // Number of misplaced tiles
    int level;    // Number of moves made from root
};

// Function to print N x N matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

// Function to allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = new Node;
    memcpy(node->mat, mat, sizeof node->mat);

    // Move the blank tile
    swap(node->mat[x][y], node->mat[newX][newY]);

    node->parent = parent;
    node->x = newX;
    node->y = newY;
    node->level = level;
    node->cost = INT_MAX; // will be set later

    return node;
}

// Directions for movement: down, left, up, right
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Function to calculate number of misplaced tiles
int calculateCost(int initial[N][N], int final[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] != 0 && initial[i][j] != final[i][j])
                count++;
    return count;
}

// Check if position is inside grid
bool isSafe(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// Print path from root to current node
void printPath(Node* root) {
    if (root == nullptr)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    cout << endl;
}

// Custom comparator for priority queue
struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

// Solves the puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y, int final[N][N]) {
    priority_queue<Node*, vector<Node*>, comp> pq;

    Node* root = newNode(initial, x, y, x, y, 0, nullptr);
    root->cost = calculateCost(initial, final);
    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        // If goal is reached
        if (min->cost == 0) {
            cout << "Solution steps:\n";
            printPath(min);
            return;
        }

        // Try all 4 possible movements of blank tile
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }

        // No need to delete min; handled by OS after program exits
    }
}

// Driver code
int main() {
    int initial[N][N] = {
        {1, 0, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    int final[N][N] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    // Blank tile is at position (0, 1)
    int x = 0, y = 1;

    solve(initial, x, y, final);

    return 0;
}
