#include <stdio.h>
#include <SDL2/SDL.h>

#include "init.h"

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
                map[i][j] = digitToInt(c);
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
