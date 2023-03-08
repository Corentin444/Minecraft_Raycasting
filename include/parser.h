#ifndef CUB_3D_PARSER_H
#define CUB_3D_PARSER_H

#include "main.h"
#include "SDL2/SDL.h"

struct Settings {
    SDL_Color groundColor;
    SDL_Color skyColor;
    SDL_Color c1Color;
    SDL_Color c2Color;
    int width;
    int height;
    int nbLines;
    int nbColumns;
    char **map;
};

int parseSettingsFile(const char *fileName, struct Settings *pSettings);

int parseMapFile(const char *fileName, struct Settings *pSettings);

int checkRgbValues(int r, int g, int b);

int setNbLinesAndNbColumns(const char *fileName, struct Settings *pSettings);

#endif //CUB_3D_PARSER_H
