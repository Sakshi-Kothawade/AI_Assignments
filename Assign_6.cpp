#include <bits/stdc++.h>
using namespace std;

/* 
   Representation:
   - Board is represented as a vector<int> where index = row, value = column of queen.
   - Example: board[0] = 3 means row 0 has a queen in column 3.
*/

/* Utility function to print the chessboard */
void printBoard(const vector<int>& board) {
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << "\n";
    }
    cout << "-----------------\n";
}

/* Check if placing queen at (row, col) is safe */
bool isSafe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        int qCol = board[i];
        if (qCol == col || abs(i - row) == abs(qCol - col)) {
            return false;
        }
    }
    return true;
}

/* Depth-First Search (Backtracking) */
bool solveDFS(vector<int>& board, int row) {
    int n = board.size();
    if (row == n) {
        printBoard(board); // Found a solution
        return true;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            if (solveDFS(board, row + 1)) return true; // return after first solution
        }
    }
    return false;
}

/* Heuristic: number of attacking pairs */
int heuristic(const vector<int>& board) {
    int h = 0;
    int n = board.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (board[i] == board[j] || abs(i - j) == abs(board[i] - board[j])) {
                h++;
            }
        }
    }
    return h;
}

/* A* Search for 8-Queens */
void solveAStar(int n) {
    struct Node {
        vector<int> board;
        int g, h;
        bool operator>(const Node& other) const {
            return g + h > other.g + other.h;
        }
    };

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({vector<int>(n, -1), 0, 0});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int row = current.g; // next row to place
        if (row == n) {
            cout << "Solution found using A*:\n";
            printBoard(current.board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(current.board, row, col)) {
                vector<int> newBoard = current.board;
                newBoard[row] = col;
                int h = heuristic(newBoard);
                pq.push({newBoard, row + 1, h});
            }
        }
    }
}

int main() {
    int n = 8;
    vector<int> board(n, -1);

    cout << "Solving 8-Queens using DFS:\n";
    if (!solveDFS(board, 0)) {
        cout << "No solution found with DFS\n";
    }

    cout << "\nSolving 8-Queens using A*:\n";
    solveAStar(n);

    return 0;
}
