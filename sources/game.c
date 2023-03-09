#include <math.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "display.h"
#include "game.h"
#include <time.h>

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player = {{5, 5}, {-1, 0}, {0, 0.66}, 0.1, 0.05};
    int size = 30;
    struct Compass compass = {{settings.width - size - 10, size + 9}, size, {255, 0, 0}, {120, 120, 120}, {45, 45, 45}};

    for (int x = 0; x < settings.texWidth; x++) {
        for (int y = 0; y < settings.texHeight; y++) {
            int xorcolor = (x * 256 / settings.texWidth) ^ (y * 256 / settings.texHeight);
            //int xcolor = x * 256 / texWidth;
            int ycolor = y * 256 / settings.texHeight;
            int xycolor = y * 128 / settings.texHeight + x * 128 / settings.texWidth;
            settings.textures[0][settings.texWidth * y + x] = 65536 * 254 * (x != y && x != settings.texWidth - y); //flat red texture with black cross
            settings.textures[1][settings.texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
            settings.textures[2][settings.texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
            settings.textures[3][settings.texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
            settings.textures[4][settings.texWidth * y + x] = 256 * xorcolor; //xor green
            settings.textures[5][settings.texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
            settings.textures[6][settings.texWidth * y + x] = 65536 * ycolor; //red gradient
            settings.textures[7][settings.texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
        }
    }


    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, settings.width,
                                             settings.height);

    double time = 0; //time of current frame
    double oldTime; //time of previous frame

    int quit = 0;
    SDL_Event event;

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
        displayScreen(renderer, &settings, &player, &compass, texture);
        SDL_RenderPresent(renderer);
    }
}