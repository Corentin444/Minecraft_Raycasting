#include <math.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "display.h"
#include "game.h"

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player = {5, 5, 0, 0.1, 0.05};
    int size = 30;
    struct Compass compass = {settings.width - size - 10, size + 9, size, {255, 0, 0}, {120, 120, 120}, {45, 45, 45}};

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                            movePlayer(&player, settings, 1);
                            break;
                        case SDLK_s:
                            movePlayer(&player, settings, -1);
                            break;
                        case SDLK_q:
                            player.angle -= player.rotationSpeed;
                            break;
                        case SDLK_d:
                            player.angle += player.rotationSpeed;
                            break;
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(17);
        displayScreen(renderer, settings, player, compass);
        SDL_RenderPresent(renderer);
    }
}

void movePlayer(struct Player *player, struct Settings settings, int direction) {
    double tmpX = player->x + (cos(player->angle) * player->speed) * direction;
    if (settings.map[(int) player->y][(int) tmpX] == '0' || settings.map[(int) player->y][(int) tmpX] == '2') {
        player->x = tmpX;
    }
    double tmpY = player->y + (sin(player->angle) * player->speed) * direction;
    if (settings.map[(int) tmpY][(int) player->x] == '0' || settings.map[(int) tmpY][(int) player->x] == '2') {
        player->y = tmpY;
    }
}