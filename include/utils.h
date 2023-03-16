#ifndef CUB_3D_UTILS_H
#define CUB_3D_UTILS_H

#include "SDL2/SDL.h"
#include <stdio.h>

struct DVector {
    double x;
    double y;
};

struct IVector {
    int x;
    int y;
};

int checkRgbValues(int r, int g, int b);

int digitToInt(char d);

Uint32 getPixelFromSurface(SDL_Surface *surface, int x, int y);

#endif //CUB_3D_UTILS_H
