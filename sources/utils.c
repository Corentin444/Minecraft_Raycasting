#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int checkRgbValues(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int digitToInt(char d) {
    char str[2];
    str[0] = d;
    str[1] = '\0';
    return (int) strtol(str, NULL, 10);
}

Uint32 getPixelFromSurface(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
    Uint32 pixel = p[0] | p[1] << 8 | p[2] << 16;
    Uint8 r, g, b;
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);
    return (r << 24) + (g << 16) + (b << 8);
}