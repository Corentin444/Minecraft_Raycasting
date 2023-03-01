#include <stdio.h>
#include "../include/main.h"

int parse_config_file(const char *fileName, struct Settings *pSettings) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file config.txt\n");
        return -1;
    }
    printf("File opened\n");

    struct Color c1;
// extract the rgb values from the line "C1 = 255 255 255"
    fscanf(file, "%*s %*s %d %d %d", &c1.r, &c1.g, &c1.b);
    if (c1.r < 0 || c1.r > 255 || c1.g < 0 || c1.g > 255 || c1.b < 0 || c1.b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return -1;
    } else {
        pSettings->c1 = c1;
    }
    printf("C1 = (%d,%d,%d)\n", c1.r, c1.g, c1.b);

    struct Color c2;
// extract the rgb values from the line "C1 = 255 255 255"
    fscanf(file, "%*s %*s %d %d %d", &c2.r, &c2.g, &c2.b);
    if (c2.r < 0 || c2.r > 255 || c2.g < 0 || c2.g > 255 || c2.b < 0 || c2.b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return -1;
    } else {
        pSettings->c2 = c2;
    }
    printf("C1 = (%d,%d,%d)\n", c2.r, c2.g, c2.b);

    struct Color c3;
// extract the rgb values from the line "C1 = 255 255 255"
    fscanf(file, "%*s %*s %d %d %d", &c3.r, &c3.g, &c3.b);
    if (c3.r < 0 || c3.r > 255 || c3.g < 0 || c3.g > 255 || c3.b < 0 || c3.b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return -1;
    } else {
        pSettings->c3 = c3;
    }
    printf("C1 = (%d,%d,%d)\n", c3.r, c3.g, c3.b);

// extract the width and the height from the line "R = 1920 1080"
    fscanf(file, "%*s %*s %d %d", &pSettings->width, &pSettings->height);
    printf("width = %d height = %d\n", pSettings->width, pSettings->height);

    fclose(file);
    return 0;
}