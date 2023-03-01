#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/parser.h"

int parse_config_file(const char *fileName, struct Settings *pSettings) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file config.txt\n");
        return -1;
    }
    printf("File opened\n");

    char c;
    int nbLines = 0;
    while (c != EOF) {
        c = fgetc(file);
        if (c == '\n') {
            nbLines++;
        }
    }
    rewind(file);


    struct Color c1;
    fscanf(file, "%*s %*s %d %d %d", &c1.r, &c1.g, &c1.b);
    if (checkRgbValues(c1.r, c1.g, c1.b) == 0) {
        pSettings->c1 = c1;
    } else {
        return -1;
    }

    struct Color c2;
    fscanf(file, "%*s %*s %d %d %d", &c2.r, &c2.g, &c2.b);
    if (checkRgbValues(c2.r, c2.g, c2.b) == 0) {
        pSettings->c2 = c2;
    } else {
        return -1;
    }

    struct Color c3;
    fscanf(file, "%*s %*s %d %d %d", &c3.r, &c3.g, &c3.b);
    if (checkRgbValues(c3.r, c3.g, c3.b) == 0) {
        pSettings->c3 = c3;
    } else {
        return -1;
    }

    fscanf(file, "%*s %*s %d %d", &pSettings->width, &pSettings->height);
    printf("width = %d height = %d\n", pSettings->width, pSettings->height);

    char line[256];
    int i = 0;
    char **map = malloc(sizeof(char *) * nbLines);
    while (fgets(line, sizeof(line), file)) {
        map[i] = line;
        i++;
    }

    pSettings->map = map;
    for (i = 0; i < nbLines; i++) {
        for (int j = 0; j < nbLines; j++) {
            printf("%c ", map[i][j]);
        }
        printf(" \n");
    }


    fclose(file);
    return 0;
}

int checkRgbValues(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return -1;
    }
    return 0;
}