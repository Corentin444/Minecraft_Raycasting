#ifndef CUB_3D_PLAYER_H
#define CUB_3D_PLAYER_H

#include "utils.h"

struct Player {
    struct DVector pos;
    struct DVector dir;
    struct DVector plane;
    double speed;
    double rotationSpeed;
};

#endif //CUB_3D_PLAYER_H
