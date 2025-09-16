#include <iostream>
#include <vector>
#include <limits>
using namespace std;

char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void printBoard() {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0) cout << "\n";
    }
    cout << "\n";
}

bool checkWinner(char b[9], char player) {
    int winCombos[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, 
        {0,3,6}, {1,4,7}, {2,5,8}, 
        {0,4,8}, {2,4,6}           
    };
    for (auto &combo : winCombos) {
        if (b[combo[0]] == player && b[combo[1]] == player && b[combo[2]] == player)
            return true;
    }
    return false;
}

bool isFull(char b[9]) {
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ') return false;
    return true;
}

int minimax(char b[9], bool isMaximizing) {
    if (checkWinner(b, 'O')) return 1;   
    if (checkWinner(b, 'X')) return -1;  
    if (isFull(b)) return 0;             

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'O';
                int score = minimax(b, false);
                b[i] = ' ';
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; i++) {
            if (b[i] == ' ') {
                b[i] = 'X';
                int score = minimax(b, true);
                b[i] = ' ';
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

void aiMove() {
    int bestScore = numeric_limits<int>::min();
    int move = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(board, false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    if (move != -1) board[move] = 'O';
}

int main() {
    cout << "Tic Tac Toe! You are X, AI is O\n";
    printBoard();

    while (true) {
        int move;
        cout << "Enter your move (0-8): ";
        cin >> move;
        if (move < 0 || move > 8 || board[move] != ' ') {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[move] = 'X';
        printBoard();
        if (checkWinner(board, 'X')) {
            cout << "You win!\n";
            break;
        }
        if (isFull(board)) {
            cout << "It's a draw!\n";
            break;
        }

        aiMove();
        printBoard();
        if (checkWinner(board, 'O')) {
            cout << "AI wins!\n";
            break;
        }
        if (isFull(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}
