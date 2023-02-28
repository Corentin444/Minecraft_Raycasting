#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"

int main(int argc, char *argv[]) {
    struct Settings settings;

    // read the file config.txt char by char
    FILE *file = fopen("../config.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open the file config.txt\n");
        return -1;
    }
    printf("File opened\n");

    int r, g, b;

    // extract the rgb values from the line "C1 = 255 255 255"
    fscanf(file, "%d %d %d", &r, &g, &b);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb value in config.txt\n");
        return -1;
    } else {
        settings.c1r = r;
        settings.c1g = g;
        settings.c1b = b;
    }
    printf("C1 = (%d,%d,%d)\n", settings.c1r, settings.c1g, settings.c1b);

    // extract the rgb values from the line "C2 = 255 255 255"
    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb value in config.txt\n");
        return -1;
    } else {
        settings.c2r = r;
        settings.c2g = g;
        settings.c2b = b;
    }
    printf("C2 = (%d,%d,%d)\n", settings.c2r, settings.c2g, settings.c2b);

    // extract the rgb values from the line "C3 = 255 255 255"
    fscanf(file, "%*s %*s %d %d %d", &r, &g, &b);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb value in config.txt\n");
        return -1;
    } else {
        settings.c3r = r;
        settings.c3g = g;
        settings.c3b = b;
    }
    printf("C3 = (%d,%d,%d)\n", settings.c3r, settings.c3g, settings.c3b);

    // extract the width and the height from the line "R = 1920 1080"
    fscanf(file, "%*s %*s %d %d", &settings.width, &settings.height);
    printf("width=%d height=%d\n", settings.width, settings.height);

    // extract the map from the file
    char **map = malloc(100 * sizeof(char *));
    char c;
    int i = 0;
    int j = 0;
    while ((c = (char) fgetc((file))) != EOF) {
        j++;
        if (c == '\n') {
            i++;
            j = 0;
        }
        map[i][j] = c;
    }

    settings.map = map;
    fclose(file);
    return 0;
}