#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    printf("Hello, World!\n");
    SDL_Window *window = NULL;
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              500, 500, SDL_WINDOW_SHOWN);
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