#include "../util/util.h"
#include "../game/game.h"
#include "graphics.h"
#include "../event/event.h"

SDL_Texture *Alive(SDL_Renderer *renderer)
{
    SDL_Texture *alive = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1);

    if (alive == NULL)
    {
        fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
        return NULL;
    }

    if (SDL_SetRenderTarget(renderer, alive) != 0)
    {
        fprintf(stderr, "Failed to set render target: %s\n", SDL_GetError());
        SDL_DestroyTexture(alive);
        return NULL;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderTarget(renderer, NULL);

    return alive;
}

SDL_Texture *Dead(SDL_Renderer *renderer)
{
    SDL_Texture *dead = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1, 1);

    if (dead == NULL)
    {
        fprintf(stderr, "Failed to create texture: %s\n", SDL_GetError());
        return NULL;
    }

    if (SDL_SetRenderTarget(renderer, dead) != 0)
    {
        fprintf(stderr, "Failed to set render target: %s\n", SDL_GetError());
        SDL_DestroyTexture(dead);
        return NULL;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetRenderTarget(renderer, NULL);

    return dead;
}

void Draw_Board(SDL_Renderer *renderer, Game game)
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    SDL_Texture *alive = Alive(renderer);
    SDL_Texture *dead = Dead(renderer);
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {

            if (game->board[i][j] == 0)
            {
                SDL_Rect rect = {i * 20, j * 20, 18, 18};
                SDL_RenderCopy(renderer, dead, NULL, &rect);
            }
            if (game->board[i][j] == 1)
            {
                SDL_Rect rect = {i * 20, j * 20, 18, 18};
                SDL_RenderCopy(renderer, alive, NULL, &rect);
            }
        }
    }
    SDL_DestroyTexture(alive);
    SDL_DestroyTexture(dead);
}

void Init_Window()
{
    Game game = Init_Board();
    game->board[0][0] = 1;
    game->board[0][2] = 1;
    game->board[1][1] = 1;
    game->board[1][2] = 1;
    game->board[2][1] = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 1000, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return;
    }

    int run = 0;
    int edit = 0;
    int key_already_pressed = 0;
    while (!run)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                run = 1;
                break;
            case SDL_KEYDOWN:
                if (ev.key.keysym.scancode == SDL_SCANCODE_E)
                {
                    if (key_already_pressed == 0)
                    {
                        if (edit == 1)
                        {
                            edit = 0;
                        }
                        else
                            edit = 1;
                        key_already_pressed = 1;
                    }
                }
                break;

            case SDL_KEYUP:

                key_already_pressed = 0;
                break;

            case SDL_BUTTON_LEFT:

                break;
            }
        }

        Draw_Board(renderer, game);
        if (edit == 0)
        {
            Next_Move(game);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(75);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    free(game);
}
