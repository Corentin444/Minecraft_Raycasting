#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
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
    displayPlayerOnMinimap(renderer, player);
}

void displayCompass(SDL_Renderer *renderer, struct Player player, struct Compass compass) {
    drawCircle(renderer, compass.outline, compass.x, compass.y, compass.size + 5);
    drawCircle(renderer, compass.background, compass.x, compass.y, compass.size);
    SDL_SetRenderDrawColor(renderer, compass.line.r, compass.line.g, compass.line.b, 255);
    int x1 = compass.x;
    int y1 = compass.y;
    double x2 = x1 + (cos(player.angle) * compass.size);
    double y2 = y1 + (sin(player.angle) * compass.size);
    SDL_RenderDrawLine(renderer, x1, y1, (int) x2, (int) y2);

}

void displayPlayerOnMinimap(SDL_Renderer *renderer, struct Player player) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {(int) player.x * 10, (int) player.y * 10, 10, 10};
    if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
        printf("Error: %s\n", SDL_GetError());
    }
}

void displayScreen(SDL_Renderer *renderer, struct Settings settings, struct Player player, struct Compass compass) {
    SDL_SetRenderDrawColor(renderer, settings.c0.r, settings.c0.g, settings.c0.b, 255);
    SDL_Rect rect = {0, 0, settings.width, settings.height};
    if (SDL_RenderFillRects(renderer, &rect, 1) != 0) {
        printf("Error: %s\n", SDL_GetError());
    }
    displayMinimap(renderer, settings, player);
    displayCompass(renderer, player, compass);
}

void drawCircle(SDL_Renderer *renderer, SDL_Color color, int x, int y, int radius) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}