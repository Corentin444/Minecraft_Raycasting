#include <math.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "init.h"
#include "display.h"

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player = {{5, 5}, {-1, 0}, {0, 0.66}, 0.1, 0.05};
    int size = 30;
    struct Compass compass = {{settings.width - size - 10, size + 9}, size, {255, 0, 0}, {120, 120, 120}, {45, 45, 45}};

    SDL_Texture *texture = SDL_CreateTexture(renderer,
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

        //speed modifiers
        double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
        double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

        int oldX;
        int newX;
        int oldY;
        int newY;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                            oldX = (int) (player.pos.x);
                            oldY = (int) (player.pos.y);
                            newX = (int) (player.pos.x + player.dir.x * moveSpeed);
                            newY = (int) (player.pos.y + player.dir.y * moveSpeed);
                            if (settings.map[oldY][newX] == 0)
                                player.pos.x += player.dir.x * moveSpeed;
                            if (settings.map[newY][oldX] == 0)
                                player.pos.y += player.dir.y * moveSpeed;
                            break;
                        case SDLK_s:
                            oldX = (int) (player.pos.x);
                            oldY = (int) (player.pos.y);
                            newX = (int) (player.pos.x - player.dir.x * moveSpeed);
                            newY = (int) (player.pos.y - player.dir.y * moveSpeed);
                            if (settings.map[oldY][newX] == 0)
                                player.pos.x -= player.dir.x * moveSpeed;
                            if (settings.map[newY][oldX] == 0)
                                player.pos.y -= player.dir.y * moveSpeed;
                            break;
                        case SDLK_q:;
                            double oldDirX = player.dir.x;
                            player.dir.x = player.dir.x * cos(-rotSpeed) - player.dir.y * sin(-rotSpeed);
                            player.dir.y = oldDirX * sin(-rotSpeed) + player.dir.y * cos(-rotSpeed);
                            double oldPlaneX = player.plane.x;
                            player.plane.x = player.plane.x * cos(-rotSpeed) - player.plane.y * sin(-rotSpeed);
                            player.plane.y = oldPlaneX * sin(-rotSpeed) + player.plane.y * cos(-rotSpeed);
                            break;
                        case SDLK_d:;
                            double oldDirX2 = player.dir.x;
                            player.dir.x = player.dir.x * cos(rotSpeed) - player.dir.y * sin(rotSpeed);
                            player.dir.y = oldDirX2 * sin(rotSpeed) + player.dir.y * cos(rotSpeed);
                            double oldPlaneX2 = player.plane.x;
                            player.plane.x = player.plane.x * cos(rotSpeed) - player.plane.y * sin(rotSpeed);
                            player.plane.y = oldPlaneX2 * sin(rotSpeed) + player.plane.y * cos(rotSpeed);
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
        SDL_Delay(16);
        displayScreen(renderer, &settings, &player, &compass, texture, displayRays);
        SDL_RenderPresent(renderer);
    }
}