#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/main.h"
#include "../include/parser.h"
#include "game.h"

SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char *argv[]) {
    struct Settings settings;
    if (parse_config_file("config.txt", &settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the config file\n");
        return -1;
    }

    if (initWindowAndRenderer(settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot init the window and the renderer\n");
        return -1;
    }

    loop(renderer, settings);

    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

int initWindowAndRenderer(struct Settings settings){
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