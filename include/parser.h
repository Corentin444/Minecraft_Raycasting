#ifndef CUB_3D_PARSER_H
#define CUB_3D_PARSER_H

#include "main.h"
#include "SDL2/SDL.h"

struct Settings {
    SDL_Color floorColor;
    SDL_Color skyColor;
    SDL_Color c1Color;
    SDL_Color c2Color;
    int width;
    int height;
    int nbLines;
    int nbColumns;
    int texWidth;
    int texHeight;
    int **map;
    Uint32 textures[8][64 * 64];
};

int parseSettingsFile(const char *fileName, struct Settings *pSettings);

int parseMapFile(const char *fileName, struct Settings *pSettings);

int checkRgbValues(int r, int g, int b);

int setNbLinesAndNbColumns(const char *fileName, struct Settings *pSettings);

int digit_to_int(char d);

#endif //CUB_3D_PARSER_H
