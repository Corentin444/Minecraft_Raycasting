#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

#include "init.h"
#include "game.h"
#include "configParser.h"
#include "mapParser.h"

int main(int argc, char *argv[]) {
    struct Settings *settings = initSetting();
    if (NULL == settings) return EXIT_FAILURE;

    initTextures(settings);

    SDL_Window *window = initWindow(settings);
    if (NULL == window) return EXIT_FAILURE;
    SDL_Renderer *renderer = initRenderer(window);
    if (NULL == renderer) return EXIT_FAILURE;

    loop(renderer, settings);

    if (NULL != renderer) SDL_DestroyRenderer(renderer);
    if (NULL != window) SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

struct Settings *initSetting() {
    struct Settings *settings = malloc(sizeof(struct Settings));
    if (parseSettingsFile("./settings.txt", settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the config file\n");
        return NULL;
    }
    if (parseMapFile("./data/map2.txt", settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the map file\n");
        return NULL;
    }
    return settings;
}

SDL_Window *initWindow(struct Settings *settings) {
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Window *window = SDL_CreateWindow("CUB_3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          settings->width, settings->height, SDL_WINDOW_SHOWN);
    if (NULL == window) {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
        return NULL;
    }
    return window;
}

SDL_Renderer *initRenderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur de creation du renderer : %s\n", SDL_GetError());
        return NULL;
    }
    return renderer;
}

void initTextures(struct Settings *settings) {
    int n = 8;
    char *textures[8] = {"wall", "grass", "chiseled", "red",
                         "green", "blue", "plank", "wood"};

    for (int i = 0; i < n; i++) {
        char *fileName;
        fileName = malloc(strlen("textures/") + strlen(textures[i]) + strlen(".bmp") + 1);
        strcpy(fileName, "textures/");
        strcat(fileName, textures[i]);
        strcat(fileName, ".bmp");

        SDL_Surface *surface = SDL_LoadBMP(fileName);
        if (!surface) {
            printf("Erreur de chargement de l'image : %s", SDL_GetError());
        }
        for (int x = 0; x < settings->texWidth; x++) {
            for (int y = 0; y < settings->texHeight; y++) {
                settings->textures[i][settings->texWidth * y + x] = getPixelFromSurface(surface, x, y);
            }
        }
    }
}