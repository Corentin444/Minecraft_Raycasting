#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

#include "init.h"
#include "game.h"
#include "configParser.h"

SDL_Window *window;
SDL_Renderer *renderer;

int parseMapFile(const char *fileName, struct Settings *pSettings);

int setNbLinesAndNbColumns(const char *fileName, struct Settings *pSettings);

int main(int argc, char *argv[]) {
    struct Settings settings;
    if (parseSettingsFile("./settings.txt", &settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the config file\n");
        return -1;
    }
    if (parseMapFile("./data/map2.txt", &settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot parse the map file\n");
        return -1;
    }
    printf("with: %d, height: %d", settings.width, settings.height);

    initTextures(&settings);

    if (initWindowAndRenderer(settings) == EXIT_FAILURE) {
        fprintf(stderr, "Error: cannot init the window and the renderer\n");
        return -1;
    }

    loop(renderer, settings);

    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);

    SDL_Quit();

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

int initWindowAndRenderer(struct Settings settings) {
    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("CUB_3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              settings.width, settings.height, SDL_WINDOW_SHOWN);
    if (NULL == window) {
        fprintf(stderr, "Erreur de creation de la fenetre : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    renderer = SDL_CreateRenderer((SDL_Window *) window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur de creation du renderer : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

Uint32 getPixelFromSurface(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
    Uint32 pixel = p[0] | p[1] << 8 | p[2] << 16;
    Uint8 r, g, b;
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);
    return (r << 24) + (g << 16) + (b << 8);
}

void initTextures(struct Settings *settings) {
    int n = 8;
    char *textures[8] = {"wall", "grass", "chiseled", "red",
                         "green", "blue", "plank", "wood"};

    for (int i = 0; i < n; i++) {
        char *fileName;
        fileName = malloc(strlen("textures/") + strlen(textures[i]) + strlen(".bmp") + 1);
        strcpy(fileName, "textures/");
        strcat(fileName, textures[i]);
        strcat(fileName, ".bmp");

        SDL_Surface *surface = SDL_LoadBMP(fileName);
        if (!surface) {
            printf("Erreur de chargement de l'image : %s", SDL_GetError());
        }
        for (int x = 0; x < settings->texWidth; x++) {
            for (int y = 0; y < settings->texHeight; y++) {
                settings->textures[i][settings->texWidth * y + x] = getPixelFromSurface(surface, x, y);
            }
        }
    }
}