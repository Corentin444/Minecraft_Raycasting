#include <SDL2/SDL.h>
#include <time.h>

#include "init.h"
#include "display.h"
#include "player.h"

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

void loop(SDL_Renderer *renderer, struct Settings *settings) {
    struct Player *player = initPlayer();
    struct Compass *compass = initCompass(settings);
    SDL_Texture *screenBuffer = SDL_CreateTexture(renderer,
                                                  SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, settings->width,
                                                  settings->height);

    double time = 0;
    double oldTime;

    int quit = 0;
    SDL_Event event;

    while (!quit) {
        oldTime = time;
        time = clock();
        double frameTime = (time - oldTime) / 1000.0;
        //printf("%d FPS\n", (int) (1.0 / frameTime))

        const Uint8 *state = SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&event)) {
            if (state[SDL_SCANCODE_W]) move(player, settings, 1, frameTime);
            if (state[SDL_SCANCODE_S]) move(player, settings, -1, frameTime);
            if (state[SDL_SCANCODE_A]) rotate(player, 1, frameTime);
            if (state[SDL_SCANCODE_D]) rotate(player, -1, frameTime);
            if (state[SDL_SCANCODE_ESCAPE]) quit = 1;
        }

        displayScreen(renderer, settings, player, compass, screenBuffer);
        SDL_RenderPresent(renderer);
    }
}