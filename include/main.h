//
// Created by coren on 01/03/2023.
//

#ifndef CUB_3D_MAIN_H
#define CUB_3D_MAIN_H

struct Color {
    int r;
    int g;
    int b;
};

struct Settings {
    struct Color c1;
    struct Color c2;
    struct Color c3;
    int width;
    int height;
    char **map;
};

#endif //CUB_3D_MAIN_H
