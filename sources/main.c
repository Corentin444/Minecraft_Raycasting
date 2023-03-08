#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include "../include/main.h"
#include "game.h"
#include "SDL2/SDL_image.h"

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    struct Settings settings;
    if (parseSettingsFile("settings.txt", &settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the config file\n");
        return -1;
    }
    if (parseMapFile("./data/map2.txt", &settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the map file\n");
        return -1;
    }

    if (initWindowAndRenderer(settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot init the window and the renderer\n");
        return -1;
    }

    SDL_Surface *wallSurface = IMG_Load("./textures/wall.bmp");
    SDL_Color color = GetPixelColor(wallSurface, 0, 0);
    printf("r: %d, g: %d, b: %d, a: %d\n", color.r, color.g, color.b, color.a);

    //loop(renderer, settings);

    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

int initWindowAndRenderer(struct Settings settings) {
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("CUB_3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              settings.width, settings.height, SDL_WINDOW_SHOWN);
    if (NULL == window) {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    renderer = SDL_CreateRenderer((SDL_Window *) window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur de creation du renderer : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

SDL_Color GetPixelColor(const SDL_Surface *pSurface, int X, int Y) {
    // Bytes per pixel
    const Uint8 Bpp = pSurface->format->BytesPerPixel;

    /*
    Retrieve the address to a specific pixel
    pSurface->pixels	= an array containing the SDL_Surface' pixels
    pSurface->pitch		= the length of a row of pixels (in bytes)
    X and Y				= the offset on where on the image to retrieve the pixel, (0, 0) is in the upper left corner of the image
    */
    Uint8 *pPixel = (Uint8 *) pSurface->pixels + Y * pSurface->pitch + X * Bpp;

    Uint32 PixelData = *(Uint32 *) pPixel;

    SDL_Color Color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};

    // Retrieve the RGB values of the specific pixel
    SDL_GetRGB(PixelData, pSurface->format, &Color.r, &Color.g, &Color.b);

    return Color;
}
