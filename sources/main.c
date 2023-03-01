#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/main.h"
#include "../include/parser.h"

int main(int argc, char *argv[]) {;
    struct Settings settings;
    if(parse_config_file("config.txt", &settings) == -1) {
        fprintf(stderr, "Error: cannot parse the config file\n");
        return -1;
    } else {
        printf("Config file parsed\n");
    }

    SDL_Window *window = NULL;
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              settings.width, settings.height, SDL_WINDOW_SHOWN);
    if(NULL == window)
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
    else
    {
        SDL_Delay(5000);
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return 0;
}