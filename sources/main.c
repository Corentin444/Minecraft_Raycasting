#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/main.h"
#include "../include/parser.h"
#include "../include/display.h"

int main(int argc, char *argv[]) {
    struct Settings settings;
    if (parse_config_file("config.txt", &settings) == -1) {
        fprintf(stderr, "Error: cannot parse the config file\n");
        return -1;
    } else {
        printf("Config file parsed\n");
    }
    printf("Init window\n");

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;

    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("CUB_3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              settings.width, settings.height, SDL_WINDOW_SHOWN);
    if (NULL == window) {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
        goto Quit;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur de creation du renderer : %s\n", SDL_GetError());
        goto Quit;
    }
    statut = EXIT_SUCCESS;
    display_map(renderer, &settings);
    SDL_Delay(5000);

    Quit:
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}