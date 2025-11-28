#include <stdlib.h>
#include <stdbool.h>

#ifndef PIECES
#define PIECES
#include "chess.h"

typedef struct move move;
typedef struct piece piece;

struct move {
    coords change; //CHANGE TO COORDS
    coords (*getPos)(piece, move); //WHERE TO MOVE
    bool (*isValid)(piece, move); //CAN MOVE
};

struct piece {
    char* name;
    char* symbol;
    color c;
    move* moves;
    int numMoves;
    coords pos;
    int val;
    bool moved;
    bool empty;
};

void defPieces();
void createPieces();

void printBoard();
void showValidMoves(piece p, coords* moves, int len);
bool moveIn(piece p, coords* moves, int len, coords m);
void fillBoard();

coords sumC(coords c1, coords c2);
piece getPiece(coords pos);
int getDir(piece p);
bool normValid(piece p, move m);
coords* getValidMoves(piece p, int* l);
bool movePiece(piece *p, move m);

coords genMove(piece p, move m);
bool isValidGen(piece p, move m);

//PAWN MOVES
coords pawnMoveOne(piece p, move m);
bool isValidPawnMoveOne(piece p, move m);
coords pawnMoveTwo(piece p, move m);
bool isValidPawnMoveTwo(piece p, move m);
coords pawnTakesLeft(piece p, move m);
bool isValidPawnTakesLeft(piece p, move m);
coords pawnTakesRight(piece p, move m);
bool isValidPawnTakesRight(piece p, move m);

//ROOK MOVES
bool isValidRookMove(piece p, move m) ;

piece Pawn;
piece Bishop;
piece Knight;
piece Rook;
piece Queen;
piece Rook;

piece board[8][8];

#endif