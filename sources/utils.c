#include <stdio.h>
#include <stdlib.h>

int checkRgbValues(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        fprintf(stderr, "Error: invalid rgb for C1 value in config.txt\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int digitToInt(char d) {
    char str[2];
    str[0] = d;
    str[1] = '\0';
    return (int) strtol(str, NULL, 10);
}