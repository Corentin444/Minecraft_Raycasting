#include <math.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "display.h"
#include "game.h"
#include <time.h>
#include <stdio.h>

Uint32 getPixelFromSurface(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
    Uint32 pixel = p[0] | p[1] << 8 | p[2] << 16;
    Uint8 r, g, b;
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);
    return (r << 24) + (g << 16) + (b << 8);
}

void loop(SDL_Renderer *renderer, struct Settings settings) {
    struct Player player = {{5, 5}, {-1, 0}, {0, 0.66}, 0.1, 0.05};
    int size = 30;
    struct Compass compass = {{settings.width - size - 10, size + 9}, size, {255, 0, 0}, {120, 120, 120}, {45, 45, 45}};

    int n = 0;
    char *textures[8] = {"wall", "grass", "chiseled", "red",
                         "green", "blue", "plank", "wood"};

    char *fileName;
    fileName = malloc(strlen("textures/") + strlen(textures[n]) + strlen(".bmp") + 1);
    strcpy(fileName, "textures/");
    strcat(fileName, textures[n]);
    strcat(fileName, ".bmp");

    SDL_Surface *surface = SDL_LoadBMP(fileName);
    if (!surface) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    for (int x = 0; x < settings.texWidth; x++) {
        for (int y = 0; y < settings.texHeight; y++) {
            settings.textures[n][settings.texWidth * y + x] = getPixelFromSurface(surface, x, y);
        }
    }

    SDL_Surface *grass = SDL_LoadBMP("textures/grass.bmp");
    if (!wall) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Surface *chiseled = SDL_LoadBMP("textures/chiseled.bmp");
    if (!wall) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Surface *red = SDL_LoadBMP("textures/red.bmp");
    if (!red) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Surface *green = SDL_LoadBMP("textures/green.bmp");
    if (!green) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Surface *blue = SDL_LoadBMP("textures/blue.bmp");
    if (!blue) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Surface *plank = SDL_LoadBMP("textures/plank.bmp");
    if (!plank) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }
    SDL_Surface *wood = SDL_LoadBMP("textures/wood.bmp");
    if (!wood) {
        printf("Erreur de chargement de l'image : %s", SDL_GetError());
    }

    for (int x = 0; x < settings.texWidth; x++) {
        for (int y = 0; y < settings.texHeight; y++) {
            settings.textures[0][settings.texWidth * y + x] = getPixelFromSurface(wall, x, y);
            settings.textures[1][settings.texWidth * y + x] = getPixelFromSurface(grass, x, y);
            settings.textures[2][settings.texWidth * y + x] = getPixelFromSurface(chiseled, x, y);
            settings.textures[3][settings.texWidth * y + x] = getPixelFromSurface(red, x, y);
            settings.textures[4][settings.texWidth * y + x] = getPixelFromSurface(green, x, y);
            settings.textures[5][settings.texWidth * y + x] = getPixelFromSurface(blue, x, y);
            settings.textures[6][settings.texWidth * y + x] = getPixelFromSurface(plank, x, y);
            settings.textures[7][settings.texWidth * y + x] = getPixelFromSurface(wood, x, y);
        }
    }


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