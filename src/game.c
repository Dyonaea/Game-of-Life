#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 50

typedef struct Game_s
{
    int board[SIZE][SIZE];
    int next_board[SIZE][SIZE];
} *Game;

Game Init_Board()
{
    Game new_Game = malloc(sizeof(struct Game_s));
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            new_Game->board[i][j] = rand() % 2;
            new_Game->next_board[i][j] = 0;
        }
    }
    return new_Game;
}

void Update(Game game)
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
        {
            game->board[i][j] = game->next_board[i][j];
        }
    }
}

int X_Not_Outside(int x)
{
    if (x == -1)
    {
        return SIZE - 1;
    }
    else if (x == SIZE)
    {
        return 0;
    }
    return x;
}

int Y_Not_Outside(int y)
{
    if (y == -1)
    {
        return SIZE - 1;
    }
    else if (y == SIZE)
    {
        return 0;
    }
    return y;
}

int Tile_Alive(Game game, int x, int y)
{
    int count = 0;
    for (int i = x - 1; i < x + 2; i++)
    {
        for (int j = y - 1; j < y + 2; j++)
        {
            if (i != x || j != y)
            {
                
                if (game->board[X_Not_Outside(i)][Y_Not_Outside(j)] == 1)
                {
                    count++;
                }
            }
        }
    }
    if (game->board[x][y] == 0)
    {
        if (count == 3)
            return 1;
        return 0;
    }
    if (count == 2 || count == 3)
        return 1;
    return 0;
}

void Next_Move(Game game)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (Tile_Alive(game, i, j))
            {
                game->next_board[i][j] = 1;
            }
            else
            {
                game->next_board[i][j] = 0;
            }
        }
    }
    Update(game);
}


