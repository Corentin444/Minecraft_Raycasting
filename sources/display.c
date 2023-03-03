#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/display.h"

void displayMinimap(SDL_Renderer *renderer, struct Settings settings, struct Player player) {
    for (int y = 0; y < settings.nbLines; y++) {
        for (int x = 0; x < settings.nbColumns; x++) {
            char c = settings.map[y][x];
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
            SDL_Rect rect = {x * 10, y * 10, 10, 10};
            if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
                printf("Error: %s\n", SDL_GetError());
            }
        }
    }
    displayPlayerOnMinimap(renderer, settings, player);
}

void displayPlayerOnMinimap(SDL_Renderer *renderer, struct Settings settings, struct Player player) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {player.x*10, player.y*10, 10, 10};
    if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
        printf("Error: %s\n", SDL_GetError());
    }
}

void displayScreen(SDL_Renderer *renderer, struct Settings settings, struct Player player) {
    SDL_SetRenderDrawColor(renderer, settings.c0.r, settings.c0.g, settings.c0.b, 255);
    SDL_Rect rect = {0, 0, settings.width, settings.height};
    if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
        printf("Error: %s\n", SDL_GetError());
    }
    displayMinimap(renderer, settings, player);
}