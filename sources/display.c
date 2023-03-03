#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/display.h"
#include "../include/main.h"

void display_map(SDL_Renderer *renderer, struct Settings settings, struct Player player) {
    for (int i = 0; i < settings.nbLines; i++) {
        for (int j = 0; j < settings.nbColumns; j++) {
            char c = settings.map[j][i];
            switch (c) {
                case '0':
                    SDL_SetRenderDrawColor(renderer, settings.c0.r, settings.c0.g, settings.c0.b, 255);
                    break;
                case '1':
                    SDL_SetRenderDrawColor(renderer, settings.c1.r, settings.c1.g, settings.c1.b, 255);
                    break;
                case '2':
                    SDL_SetRenderDrawColor(renderer, settings.c2.r, settings.c2.g, settings.c2.b, 255);
                    break;
                default:
                    break;
            }
            SDL_Rect rect = {i * settings.cellWidth, j * settings.cellHeight, settings.cellWidth,
                             settings.cellHeight};
            if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
                printf("Error: %s\n", SDL_GetError());
            }
        }
    }
    // draw the player with a cercle
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {player.x, player.y, 10, 10};
    if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
        printf("Error: %s\n", SDL_GetError());
    }
    SDL_RenderPresent(renderer);
}