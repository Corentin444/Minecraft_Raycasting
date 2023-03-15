#ifndef CUB_3D_PLAYER_H
#define CUB_3D_PLAYER_H

#include "utils.h"
#include "init.h"

struct Player {
    struct DVector pos;
    struct DVector dir;
    struct DVector plane;
    double moveSpeed;
    double rotSpeed;
};

void move(struct Player *player, struct Settings *settings, int direction, double frameTime);

void rotate(struct Player *player, int direction, double frameTime);

#endif //CUB_3D_PLAYER_H
