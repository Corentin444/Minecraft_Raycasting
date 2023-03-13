#ifndef CUB_3D_INIT_H
#define CUB_3D_INIT_H

#include "utils.h"

struct Settings {
    SDL_Color floorColor;
    SDL_Color skyColor;
    int width;
    int height;
    int nbLines;
    int nbColumns;
    int texWidth;
    int texHeight;
    int **map;
    Uint32 textures[8][64 * 64];
};

struct Compass {
    struct IVector pos;
    int size;
    SDL_Color line;
    SDL_Color background;
    SDL_Color outline;
};

int initWindowAndRenderer(struct Settings settings);

void initTextures(struct Settings *settings);

Uint32 getPixelFromSurface(SDL_Surface *surface, int x, int y);

#endif //CUB_3D_INIT_H
