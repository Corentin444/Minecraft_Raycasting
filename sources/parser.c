#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/main.h"
#include "../include/parser.h"

int parse_config_file(const char *fileName, struct Settings *pSettings) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file config.txt\n");
        return EXIT_FAILURE;
    }

    int r, g, b;
    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color c0 = {r, g, b, 255};
        pSettings->c0 = c0;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color c1 = {r, g, b, 255};
        pSettings->c1 = c1;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color c2 = {r, g, b, 255};
        pSettings->c2 = c2;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d", &pSettings->width, &pSettings->height);
    fscanf(file, "%*s %*s %d %d", &pSettings->nbColumns, &pSettings->nbLines);

    fgetc(file);
    fgetc(file);

    char **map = malloc(pSettings->nbLines * sizeof(char *));
    for (int i = 0; i < pSettings->nbLines; i++) {
        map[i] = malloc(pSettings->nbColumns * sizeof(char));
    }

    for (int i = 0; i < pSettings->nbLines; i++) {
        for (int j = 0; j < pSettings->nbColumns; j++) {
            char c = fgetc(file);
            map[i][j] = c;
        }
        fgetc(file);
    }
    pSettings->map = map;

    fclose(file);
    return EXIT_SUCCESS;
}

int checkRgbValues(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}