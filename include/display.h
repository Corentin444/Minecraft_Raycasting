#ifndef CUB_3D_DISPLAY_H
#define CUB_3D_DISPLAY_H

#include "../include/init.h"
#include "../include/player.h"
#include "SDL2/SDL.h"

struct DDAResult {
    struct IVector mapPos;
    double perpWallDist;
    int side;
};

void displayMinimap(SDL_Renderer *renderer, struct Settings *settings);

void displayPlayerOnMinimap(SDL_Renderer *renderer, struct Player *player);

void displayScreen(SDL_Renderer *renderer, struct Settings *settings, struct Player *player, struct Compass *compass,
                   SDL_Texture *screenBuffer);

void displayCompass(SDL_Renderer *renderer, struct Player *player, struct Compass *compass, SDL_Texture *screenBuffer);

void drawCircle(SDL_Renderer *renderer, SDL_Color color, int x, int y, int radius, int scale);

void displayRaysWithTexture(SDL_Renderer *renderer, struct Settings *settings, struct Player *player,
                            SDL_Texture *screenBuffer);

struct DDAResult
dda(struct DVector deltaDist, struct DVector rayDir, struct Player *player, struct Settings *settings);

struct IVector getStep(struct DVector rayDir);

struct DVector geDist(struct Player *player, struct DVector rayDir, struct DVector deltaDist);

#endif //CUB_3D_DISPLAY_H
