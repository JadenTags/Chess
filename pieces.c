#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "pieces.h"

void defPieces() {
    //PAWN
    //Moves
    Pawn.numMoves = 4;
    Pawn.moves = (move*) malloc(Pawn.numMoves * sizeof(move));
    Pawn.moves[0] = (move) {(coords) {}, &pawnMoveOne, &isValidPawnMoveOne};
    Pawn.moves[1] = (move) {(coords) {}, &pawnMoveTwo, &isValidPawnMoveTwo};
    Pawn.moves[2] = (move) {(coords) {}, &pawnTakesLeft, &isValidPawnTakesLeft};
    Pawn.moves[3] = (move) {(coords) {}, &pawnTakesRight, &isValidPawnTakesRight};
    Pawn.val = 1;

    //ROOK
    //MOVES
    Rook.numMoves = 28;
    Rook.moves = (move*) malloc(Rook.numMoves * sizeof(move));
    int s = 0;
    for (int i = 0; i <= 14; i++) {
        if (i-7 == 0) {
            s++;
            continue;
        }

        Rook.moves[i-s] = (move) {{i-7, 0}, &genMove, &isValidRookMove};
    }
    s = 0;
    for (int i = 0; i <= 14; i++) {
        if (i-7 == 0) {
            s++;
            continue;
        }

        Rook.moves[14 + i - s] = (move) {{0, i-7}, &genMove, &isValidRookMove};
    }
    Rook.val = 4;

    //KNIGHT
    Knight.numMoves = 8;
    Knight.moves = (move*) malloc(Knight.numMoves * sizeof(move));
    Knight.moves[0] = (move) {(coords) {-2, -1}, &genMove, &isValidGen};
    Knight.moves[1] = (move) {(coords) {-2, 1}, &genMove, &isValidGen};
    Knight.moves[2] = (move) {(coords) {-1, 2}, &genMove, &isValidGen};
    Knight.moves[3] = (move) {(coords) {1, 2}, &genMove, &isValidGen};
    Knight.moves[4] = (move) {(coords) {2, -1}, &genMove, &isValidGen};
    Knight.moves[5] = (move) {(coords) {2, 1}, &genMove, &isValidGen};
    Knight.moves[6] = (move) {(coords) {-1, -2}, &genMove, &isValidGen};
    Knight.moves[7] = (move) {(coords) {1, -2}, &genMove, &isValidGen};
    Knight.val = 3;

    //BISHOP
    Bishop.numMoves = 28;
    Bishop.moves = (move*) malloc(Bishop.numMoves * sizeof(move));
}

void createPieces() {
    // board[6][0] = (piece) {"White Pawn One", "♙", WHITE, Pawn.moves, (coords) {6, 0}, Pawn.val, false, false};
    // board[0][0] = (piece) {"White Rook One", "♖", WHITE, Rook.moves, Rook.numMoves, (coords) {0, 0}, Rook.val, false, false};
    // board[4][4] = (piece) {"White Knight One", "♖", WHITE, Knight.moves, Knight.numMoves, (coords) {4, 4}, Knight.val, false, false};


    board[4][6] = (piece) {"White Pawn One", "♙", WHITE, Pawn.moves, Rook.numMoves, (coords) {3, 4}, Pawn.val, false, false};
    board[5][2] = (piece) {"White Pawn One", "♙", BLACK, Pawn.moves, Rook.numMoves, (coords) {3, 4}, Pawn.val, false, false};
}

coords sumC(coords c1, coords c2) {
    return (coords) {c1.row + c2.row, c1.col + c2.col};
}

piece getPiece(coords pos) {
    return board[pos.row][pos.col];
}

int getDir(piece p) {
    return p.c == WHITE ? 1 : -1;
}

bool normValid(piece p, move m) {
    coords nextC = m.getPos(p, m);

    return (nextC.row >= 0 && nextC.row <= 7) && (nextC.col >= 0 && nextC.col <= 7);
}

coords* getValidMoves(piece p, int* l) {
    coords* validMoves = (coords*) malloc(0);
    int len = 0;

    for (int i = 0; i < p.numMoves; i++) {
        move m = p.moves[i];

        if (m.isValid(p, m) && normValid(p, m)) {
            validMoves = realloc(validMoves, ++len * sizeof(coords));
            validMoves[len-1] = m.getPos(p, m);
        }
    }

    *l = len;
    return validMoves;
}

bool movePiece(piece *p, move m) {
    coords nextC = m.getPos(*p, m);

    if (m.isValid(*p, m) && (nextC.row >= 0 && nextC.row <= 7) && (nextC.col >= 0 && nextC.col <= 7)) {//TODO: ADD PIN MOVE PREVENTION AND IN CHECK
        board[nextC.row][nextC.col] = *p;
        board[(*p).pos.row][(*p).pos.col] = (piece) {.empty = true};
        (*p).pos = nextC;
        (*p).moved = true;

        return true;
    }

    return false;
}


//TODO: CHECKS FOR PROMOTION AFTER
//GENERALMOVE
coords genMove(piece p, move m) {
    return sumC(p.pos, m.change);
}
bool isValidGen(piece p, move m) {
    return getPiece(m.getPos(p, m)).empty || getPiece(m.getPos(p, m)).c != p.c;
}

//PAWN MOVES
//UP ONE
coords pawnMoveOne(piece p, move m) {
    return sumC(p.pos, (coords) {1 * getDir(p), 0});
}
bool isValidPawnMoveOne(piece p, move m) {
    return getPiece(m.getPos(p, m)).empty;
}
//UP TWO
coords pawnMoveTwo(piece p, move m) {
    return sumC(p.pos, (coords) {2 * getDir(p), 0});
}
bool isValidPawnMoveTwo(piece p, move m) {
    return getPiece(pawnMoveOne(p, m)).empty && getPiece(m.getPos(p, m)).empty && !p.moved;
}
//TAKES LEFT
coords pawnTakesLeft(piece p, move m) {
    return sumC(p.pos, (coords) {1 * getDir(p), -1});
}
bool isValidPawnTakesLeft(piece p, move m) {
    piece temp = getPiece(m.getPos(p, m));
    return !temp.empty && temp.c != p.c;
}
//TAKES RIGHT
coords pawnTakesRight(piece p, move m) {
    return sumC(p.pos, (coords) {1 * getDir(p), 1});
}
bool isValidPawnTakesRight(piece p, move m) {
    piece temp = getPiece(m.getPos(p, m));
    return !temp.empty && temp.c != p.c;
}

//ROOK MOVES
bool isValidRookMove(piece p, move m) {
    coords nextC = m.getPos(p, m);

    if (nextC.row < p.pos.row) { //UP
        coords temp = p.pos;

        while (nextC.row+1 != temp.row) {
            temp = sumC(temp, (coords) {-1, 0});
            
            if (!getPiece(temp).empty) {
                return false;
            }
        }
    } else if (nextC.row > p.pos.row) { //DOWN
        coords temp = p.pos;

        while (nextC.row-1 != temp.row) {
            temp = sumC(temp, (coords) {1, 0});

            if (!getPiece(temp).empty) {
                return false;
            }
        }
    } else if (nextC.col < p.pos.col) { //LEFT
        coords temp = p.pos;

        while (nextC.col+1 != temp.col) {
            temp = sumC(temp, (coords) {0, -1});

            if (!getPiece(temp).empty) {
                return false;
            }
        }
    } else if (nextC.col > p.pos.col) { //RIGHT
        coords temp = p.pos;

        while (nextC.col-1 != temp.col) {
            temp = sumC(temp, (coords) {0, 1});

            if (!getPiece(temp).empty) {
                return false;
            }
        }
    }

    piece temp = getPiece(nextC);
    return temp.empty || temp.c != p.c;
}

//BISHOP MOVES
bool isValidBishopMove(piece p, move m) {
    coords nextC = m.getPos(p, m);

    if (nextC.row < p.pos.row && nextC.col < p.pos.col) { //TOP LEFT

    }
}