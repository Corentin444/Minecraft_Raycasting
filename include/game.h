#ifndef CUB_3D_GAME_H
#define CUB_3D_GAME_H

#include "main.h"
#include "utils.h"
#include "SDL2/SDL.h"

struct Compass {
    struct IVector pos;
    int size;
    SDL_Color line;
    SDL_Color background;
    SDL_Color outline;
};

void loop(SDL_Renderer *renderer, struct Settings settings);

SDL_Texture *loadTexture(const char path[], SDL_Renderer *renderer);

#endif //CUB_3D_GAME_H
