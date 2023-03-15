#include <SDL2/SDL.h>
#include <time.h>

#include "init.h"
#include "display.h"
#include "player.h"

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player = {{5, 5}, {-1, 0}, {0, 0.66}, 0.1, 0.05};
    int size = 30;
    struct Compass compass = {{settings.width - size - 10, size + 9}, size, {255, 0, 0}, {120, 120, 120}, {45, 45, 45}};

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
                            move(&player, &settings, 1, frameTime);
                            break;
                        case SDLK_s:
                            move(&player, &settings, -1, frameTime);
                            break;
                        case SDLK_q:
                            rotate(&player, 1, frameTime);
                            break;
                        case SDLK_d:
                            rotate(&player, -1, frameTime);
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
        displayScreen(renderer, &settings, &player, &compass, screenBuffer, displayRays);
        SDL_RenderPresent(renderer);
    }
}