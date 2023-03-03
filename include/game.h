//
// Created by coren on 02/03/2023.
//

#ifndef CUB_3D_GAME_H
#define CUB_3D_GAME_H

struct Player {
    int x;
    int y;
    int angle;
};


int loop(SDL_Renderer *renderer, struct Settings settings);

#endif //CUB_3D_GAME_H
