#include <bits/stdc++.h>
using namespace std;

#define N 3

struct Node {
    int mat[N][N];
    int x, y; // blank tile coordinates
    Node* parent;
};

// Function to print matrix
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

// Check if coordinates are valid
bool isSafe(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

// Check if two matrices are equal
bool isGoal(int mat[N][N], int goal[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] != goal[i][j])
                return false;
    return true;
}

// Print path from root to current node
void printPath(Node* node) {
    if (!node) return;
    printPath(node->parent);
    printMatrix(node->mat);
}

// Convert matrix to string for visited set
string matToString(int mat[N][N]) {
    string s;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            s += to_string(mat[i][j]) + ",";
    return s;
}

// Directions: down, left, up, right
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// BFS function
void BFS(int initial[N][N], int x, int y, int goal[N][N]) {
    queue<Node*> q;
    Node* root = new Node;
    memcpy(root->mat, initial, sizeof(int)*N*N);
    root->x = x;
    root->y = y;
    root->parent = nullptr;

    q.push(root);

    set<string> visited;
    visited.insert(matToString(root->mat));

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        if (isGoal(node->mat, goal)) {
            cout << "Solution using BFS:\n";
            printPath(node);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = node->x + row[i];
            int newY = node->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = new Node;
                memcpy(child->mat, node->mat, sizeof(int)*N*N);
                swap(child->mat[node->x][node->y], child->mat[newX][newY]);
                child->x = newX;
                child->y = newY;
                child->parent = node;

                string s = matToString(child->mat);
                if (visited.find(s) == visited.end()) {
                    visited.insert(s);
                    q.push(child);
                }
            }
        }
    }
}

// DFS function (uses stack)
void DFS(int initial[N][N], int x, int y, int goal[N][N]) {
    stack<Node*> s;
    Node* root = new Node;
    memcpy(root->mat, initial, sizeof(int)*N*N);
    root->x = x;
    root->y = y;
    root->parent = nullptr;

    s.push(root);

    set<string> visited;
    visited.insert(matToString(root->mat));

    while (!s.empty()) {
        Node* node = s.top();
        s.pop();

        if (isGoal(node->mat, goal)) {
            cout << "Solution using DFS:\n";
            printPath(node);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = node->x + row[i];
            int newY = node->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = new Node;
                memcpy(child->mat, node->mat, sizeof(int)*N*N);
                swap(child->mat[node->x][node->y], child->mat[newX][newY]);
                child->x = newX;
                child->y = newY;
                child->parent = node;

                string sMat = matToString(child->mat);
                if (visited.find(sMat) == visited.end()) {
                    visited.insert(sMat);
                    s.push(child);
                }
            }
        }
    }
}

int main() {
    int initial[N][N] = {
        {1, 2, 0},
        {3, 4, 5},
        {6, 7, 8}
    };

    int goal[N][N] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}
    };

    int x = 0, y = 2; // blank tile coordinates

    BFS(initial, x, y, goal);
    DFS(initial, x, y, goal);

    return 0;
}
