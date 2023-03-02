//
// Created by coren on 01/03/2023.
//

#ifndef CUB_3D_MAIN_H
#define CUB_3D_MAIN_H

struct Settings {
    SDL_Color c0;
    SDL_Color c1;
    SDL_Color c2;
    int width;
    int height;
    int nbLines;
    int nbColumns;
    int cellWidth;
    int cellHeight;
    char **map;
};

#endif //CUB_3D_MAIN_H
