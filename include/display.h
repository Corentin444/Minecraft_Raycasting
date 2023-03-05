#ifndef CUB_3D_DISPLAY_H
#define CUB_3D_DISPLAY_H

#include "main.h"
#include "game.h"

void displayMinimap(SDL_Renderer *renderer, struct Settings settings);

void displayPlayerOnMinimap(SDL_Renderer *renderer, struct Player player);

void displayScreen(SDL_Renderer *renderer, struct Settings settings, struct Player player, struct Compass compass);

void displayCompass(SDL_Renderer *renderer, struct Player player, struct Compass compass);

void drawCircle(SDL_Renderer *renderer, SDL_Color color, int x, int y, int radius);

#endif //CUB_3D_DISPLAY_H
