#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "display.h"
#include "game.h"
#include <time.h>

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player = {{5, 5}, {-1, 0}, {0, 0.66}, 0.1, 0.05};
    int size = 30;
    struct Compass compass = {{settings.width - size - 10, size + 9}, size, {255, 0, 0}, {120, 120, 120}, {45, 45, 45}};

    double time = 0; //time of current frame
    double oldTime; //time of previous frame

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        //timing for input and FPS counter
        oldTime = time;
        time = clock();
        double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
        printf("%d FPS\n", (int) (1.0 / frameTime)); //FPS counter

        //speed modifiers
        double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
        double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_z:
                            if(settings.map[(int) (player.pos.x + player.dir.x * moveSpeed)][(int) (player.pos.y)] == 0) player.pos.x += player.dir.x * moveSpeed;
                            if(settings.map[(int) (player.pos.x)][(int) (player.pos.y + player.dir.y * moveSpeed)] == 0) player.pos.y += player.dir.y * moveSpeed;
                            break;
                        case SDLK_s:
                            if(settings.map[(int) (player.pos.x - player.dir.x * moveSpeed)][(int) (player.pos.y)] == 0) player.pos.x -= player.dir.x * moveSpeed;
                            if(settings.map[(int) (player.pos.x)][(int) (player.pos.y - player.dir.y * moveSpeed)] == 0) player.pos.y -= player.dir.y * moveSpeed;
                            break;
                        case SDLK_q:
                            printf("q");
                            //both camera direction and camera plane must be rotated
                            double oldDirX = player.dir.x;
                            player.dir.x =  player.dir.x * cos(-rotSpeed) -  player.dir.y * sin(-rotSpeed);
                            player.dir.y =  oldDirX * sin(-rotSpeed) +  player.dir.y * cos(-rotSpeed);
                            double oldPlaneX =  player.plane.x;
                            player.plane.x = player.plane.x * cos(-rotSpeed) - player.plane.y * sin(-rotSpeed);
                            player.plane.y = oldPlaneX * sin(-rotSpeed) + player.plane.y * cos(-rotSpeed);
                            break;
                        case SDLK_d:
                            printf("d");
                            //both camera direction and camera plane must be rotated
                            double oldDirX2 = player.dir.x;
                            player.dir.x =  player.dir.x * cos(rotSpeed) -  player.dir.y * sin(rotSpeed);
                            player.dir.y =  oldDirX2 * sin(rotSpeed) +  player.dir.y * cos(rotSpeed);
                            double oldPlaneX2 =  player.plane.x;
                            player.plane.x = player.plane.x * cos(rotSpeed) - player.plane.y * sin(rotSpeed);
                            player.plane.y = oldPlaneX2 * sin(rotSpeed) + player.plane.y * cos(rotSpeed);
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