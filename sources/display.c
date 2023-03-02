#include <SDL2/SDL.h>
#include "../include/display.h"

void display_map(SDL_Renderer *renderer, struct Settings *pSettings) {
    for (int i = 0; i < pSettings->nbLines; i++) {
        for (int j = 0; j < pSettings->nbColumns; j++) {
            char c = pSettings->map[j][i];
            switch (c) {
                case '0':
                    SDL_SetRenderDrawColor(renderer, pSettings->c0.r, pSettings->c0.g, pSettings->c0.b, 255);
                    break;
                case '1':
                    SDL_SetRenderDrawColor(renderer, pSettings->c1.r, pSettings->c1.g, pSettings->c1.b, 255);
                    break;
                case '2':
                    SDL_SetRenderDrawColor(renderer, pSettings->c2.r, pSettings->c2.g, pSettings->c2.b, 255);
                    break;
                default:
                    break;
            }
            SDL_Rect rect = {i * pSettings->cellWidth, j * pSettings->cellHeight, pSettings->cellWidth,
                             pSettings->cellHeight};
            SDL_RenderFillRects(renderer, &rect, 1);
            SDL_RenderPresent(renderer);
        }
    }
}