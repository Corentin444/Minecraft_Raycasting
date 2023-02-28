#include <stdio.h>
#include "../include/SDL2/SDL.h"

int main(int argc, char *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_SUCCESS;
    SDL_Color orange = {255, 127, 40, 255};

    if (0 != SDL_CreateWindowAndRenderer(500, 500, SDL_WINDOW_SHOWN, &window, &renderer)) {
        fprintf(stderr, "Erreur de creation de la fenetre et du renderer : %s\n", SDL_GetError());
        statut = EXIT_FAILURE;
        goto Quit;
    }
    SDL_Delay(2000);
    SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, 250, 250);
    SDL_Point point = {250, 250};
    SDL_Rect rect = {point.x - 50, point.y - 50, 100, 100};
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawLine(renderer, 100, 0, 500, 500);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);
    Quit:
    if(renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if(window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    return statut;
}