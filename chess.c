#include <stdio.h>
#include <stdlib.h>

#include "chess.h"
#include "pieces.h"

int main() {
    fillBoard();
    defPieces();
    createPieces();


    printBoard();
    piece p = board[4][4];
    // movePiece(&p, p.moves[0]);
    // printBoard();

    int len;
    coords* moves = getValidMoves(p, &len);
    
    showValidMoves(p, moves, len);
}

void printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].symbol) {
                printf("%s", board[i][j].symbol);
            } else {
                printf("%s", ((i + j) % 2 == 0 ? "■" : "□"));
            }
        }
        printf("\n");
    }

    printf("--------\n");
}

void showValidMoves(piece p, coords* moves, int len) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (moveIn(p, moves, len, (coords) {i, j})) {
                printf("%s", (board[i][j].empty ? "◇" : "x"));
            } else if (board[i][j].symbol) {
                printf("%s", board[i][j].symbol);
            } else {
                printf("%s", ((i + j) % 2 == 0 ? "■" : "□"));
            }
        }
        printf("\n");
    }

    printf("--------\n");
}

bool moveIn(piece p, coords* moves, int len, coords m) {
    for (int i = 0; i < len; i++) {
        if (moves[i].row == m.row && moves[i].col == m.col) {
            return true;
        }
    }

    return false;
}

void fillBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = (piece) {.empty = true};
        }
    }
}