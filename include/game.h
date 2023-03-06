#ifndef CUB_3D_GAME_H
#define CUB_3D_GAME_H

#include "main.h"
#include "SDL2/SDL.h"

struct DVector {
    double x;
    double y;
};

struct IVector {
    int x;
    int y;
};

struct Player {
    struct DVector pos;
    struct DVector dir;
    struct DVector plane;
    double speed;
    double rotationSpeed;
};

struct Compass {
    struct IVector pos;
    int size;
    SDL_Color line;
    SDL_Color background;
    SDL_Color outline;
};

void loop(SDL_Renderer *renderer, struct Settings settings);

#endif //CUB_3D_GAME_H
