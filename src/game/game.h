#include "../util/util.h"
#define SIZE 50


typedef struct Game_s
{
    int board[SIZE][SIZE];
    int next_board[SIZE][SIZE];
} *Game;

Game Init_Board();

void Update(Game game);

void Next_Move(Game game);
