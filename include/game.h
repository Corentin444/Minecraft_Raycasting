#ifndef CUB_3D_GAME_H
#define CUB_3D_GAME_H

struct Player {
    double x;
    double y;
    double angle;
    double speed;
    double rotationSpeed;
};

struct Compass {
    int x;
    int y;
    int size;
    SDL_Color line;
    SDL_Color background;
    SDL_Color outline;
};

void loop(SDL_Renderer *renderer, struct Settings settings);

void movePlayer(struct Player *player, struct Settings settings, int direction);

#endif //CUB_3D_GAME_H
