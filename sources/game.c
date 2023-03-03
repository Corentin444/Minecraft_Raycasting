#include <SDL2/SDL.h>
#include "main.h"
#include "display.h"
#include "game.h"

int loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player;
    player.x = 0;
    player.y = 0;
    player.angle = 0;

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
                            player.y -= 1;
                            break;
                        case SDLK_s:
                            player.y += 1;
                            break;
                        case SDLK_q:
                            player.x -= 1;
                            break;
                        case SDLK_d:
                            player.x += 1;
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
        displayScreen(renderer, settings, player);
        SDL_RenderPresent(renderer);
    }
    return 0;
}