#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/main.h"

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

    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color c1Color = {r, g, b, 255};
        pSettings->c1Color = c1Color;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (checkRgbValues(r, g, b) == EXIT_SUCCESS) {
        SDL_Color c2Color = {r, g, b, 255};
        pSettings->c2Color = c2Color;
    } else {
        return EXIT_FAILURE;
    }

    fscanf(file, "%*s %*s %d %d", &pSettings->width, &pSettings->height);

    fclose(file);
    return EXIT_SUCCESS;
}

int parseMapFile(const char *fileName, struct Settings *pSettings) {
    if (setNbLinesAndNbColumns(fileName, pSettings) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file %s\n", fileName);
        return EXIT_FAILURE;
    }

    int **map = malloc(pSettings->nbLines * sizeof(int *));
    for (int i = 0; i < pSettings->nbLines; i++) {
        map[i] = malloc(pSettings->nbColumns * sizeof(int));
    }

    for (int i = 0; i < pSettings->nbLines; i++) {
        int j = 0;
        char c = fgetc(file);
        while (j < pSettings->nbColumns) {
            if (c == '\n') {
                map[i][j] = 1;
            } else {
                map[i][j] = digit_to_int(c);
                c = fgetc(file);
            }
            j++;
        }
    }
    pSettings->map = map;
    pSettings->texWidth = 64;
    pSettings->texHeight = 64;

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

int setNbLinesAndNbColumns(const char *fileName, struct Settings *pSettings) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file %s\n", fileName);
        return EXIT_FAILURE;
    }

    int nbLines = 1;
    int nbColumns = 0;
    int i = 0;

    // count the nb of lines and columns in the file
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            nbLines++;
            if (i > nbColumns) {
                nbColumns = i;
            }
            i = 0;
        } else {
            i++;
        }
    }

    pSettings->nbLines = nbLines;
    pSettings->nbColumns = nbColumns;

    // reset the file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    fclose(file);
    return EXIT_SUCCESS;
}

int digit_to_int(char d) {
    char str[2];

    str[0] = d;
    str[1] = '\0';
    return (int) strtol(str, NULL, 10);
}