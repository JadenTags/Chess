#ifndef CHESS
#define CHESS

typedef enum {
    BLACK,
    WHITE
} color;

typedef struct {
    int row;
    int col;
} coords;

typedef struct {
    char* name;
    color c;
    int val;
} player;

#endif