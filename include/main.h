#ifndef CUB_3D_MAIN_H
#define CUB_3D_MAIN_H

#include "parser.h"

int initWindowAndRenderer(struct Settings settings);

SDL_Color GetPixelColor(const SDL_Surface *pSurface, int X, int Y);

#endif //CUB_3D_MAIN_H
