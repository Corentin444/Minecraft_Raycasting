#ifndef CUB_3D_INIT_H
#define CUB_3D_INIT_H

#include "utils.h"
#include "SDL2/SDL.h"

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
    SDL_Color color;
    SDL_Color bgColor;
    SDL_Color borderColor;
};

int initWindowAndRenderer(struct Settings settings);

void initTextures(struct Settings *settings);

Uint32 getPixelFromSurface(SDL_Surface *surface, int x, int y);

int parseMapFile(const char *fileName, struct Settings *pSettings);

#endif //CUB_3D_INIT_H
