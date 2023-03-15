#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>

#include "init.h"
#include "display.h"
#include "player.h"

struct Player *initPlayer(struct Settings *settings) {
    struct Player *player = malloc(sizeof(struct Player));
    // TODO find a free position to spawn the player
    player->pos.x = 5;
    player->pos.y = 5;
    player->dir.x = -1;
    player->dir.y = 0;
    player->plane.x = 0;
    player->plane.y = 0.66;
    player->moveSpeed = 0.1;
    player->rotSpeed = 0.05;
    return player;
}

struct Compass *initCompass(struct Settings *settings) {
    struct Compass *compass = malloc(sizeof(struct Compass));
    int size = settings->width / 20;
    compass->pos.x = settings->width - size - size / 3;
    compass->pos.y = size + size / 3;
    compass->size = size;
    compass->color = (SDL_Color) {255, 0, 0};
    compass->bgColor = (SDL_Color) {120, 120, 120};
    compass->borderColor = (SDL_Color) {45, 45, 45};
    return compass;
}

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player *player = initPlayer(&settings);
    struct Compass *compass = initCompass(&settings);
    SDL_Texture *screenBuffer = SDL_CreateTexture(renderer,
                                                  SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, settings.width,
                                                  settings.height);

    double time = 0; //time of current frame
    double oldTime; //time of previous frame

    int quit = 0;
    SDL_Event event;
    int displayRays = 1;

    while (!quit) {
        //timing for input and FPS counter
        oldTime = time;
        time = clock();
        double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
        //printf("%d FPS\n", (int) (1.0 / frameTime)); //FPS counter

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                            move(player, &settings, 1, frameTime);
                            break;
                        case SDLK_s:
                            move(player, &settings, -1, frameTime);
                            break;
                        case SDLK_q:
                            rotate(player, 1, frameTime);
                            break;
                        case SDLK_d:
                            rotate(player, -1, frameTime);
                            break;
                        case SDLK_m:
                            displayRays = !displayRays;
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
        displayScreen(renderer, &settings, player, compass, screenBuffer, displayRays);
        SDL_RenderPresent(renderer);
    }
}