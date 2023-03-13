#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/init.h"
#include "../include/utils.h"

int parseSettingsFile(const char *fileName, struct Settings *pSettings) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file %s\n", fileName);
        return EXIT_FAILURE;
    }

    int r, g, b;
    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color floorColor = {r, g, b, 255};
        pSettings->floorColor = floorColor;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color skyColor = {r, g, b, 255};
        pSettings->skyColor = skyColor;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d", &pSettings->width, &pSettings->height);

    fclose(file);
    return EXIT_SUCCESS;
}