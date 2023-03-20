#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <string.h>
#include "../include/display.h"

SDL_Color RGB_Black = {0, 0, 0, 255};
SDL_Color RGB_Red = {255, 0, 0, 255};

void displayScreen(SDL_Renderer *renderer, struct Settings *settings, struct Player *player, struct Compass *compass,
                   SDL_Texture *screenBuffer) {
    SDL_RenderClear(renderer);

    Uint32 (*pixels)[settings->width] = malloc(sizeof(int[settings->height][settings->width]));
    memset(pixels, 255, settings->width * settings->height * sizeof(Uint32));
    displayFloor(settings, player, pixels);
    displayWall(settings, player, pixels);
    SDL_UpdateTexture(screenBuffer, NULL, pixels, (int) (settings->width * sizeof(Uint32)));
    SDL_RenderCopy(renderer, screenBuffer, NULL, NULL);
    free(pixels);

    displayMinimap(renderer, settings);
    displayPlayerOnMinimap(renderer, player);
    displayCompass(renderer, player, compass, screenBuffer);
}

void displayWall(struct Settings *settings, struct Player *player, Uint32 (*pixels)[settings->width]) {
    for (int x = 0; x < settings->width; x++) {
        double cameraX = 2 * x / (double) settings->width - 1;
        struct DVector rayDir = {player->dir.x + player->plane.x * cameraX, player->dir.y + player->plane.y * cameraX};

        //length of ray from one x or y-side to next x or y-side
        struct DVector deltaDist = {(rayDir.x == 0) ? 1e30 : fabs(1 / rayDir.x),
                                    (rayDir.y == 0) ? 1e30 : fabs(1 / rayDir.y)};

        // If rayDirX or rayDirY are 0, the division through zero is avoided by setting it to a very high value 1e30
        struct DDAResult ddaResult = dda(deltaDist, rayDir, player, settings);
        double perpWallDist = ddaResult.perpWallDist;

        //Calculate height of line to draw on screen
        int lineHeight = (int) (settings->height / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + settings->height / 2;
        if (drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + settings->height / 2;
        if (drawEnd >= settings->height)drawEnd = settings->height - 1;

        //texturing calculations
        int texNum = settings->map[ddaResult.mapPos.y][ddaResult.mapPos.x] - 1;

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (ddaResult.side == 0) wallX = player->pos.y + perpWallDist * rayDir.y;
        else wallX = player->pos.x + perpWallDist * rayDir.x;
        wallX -= floor((wallX));

        //x coordinate on the texture
        int texX = (int) (wallX * (double) settings->texWidth);
        if (ddaResult.side == 0 && rayDir.x > 0) texX = settings->texWidth - texX - 1;
        if (ddaResult.side == 1 && rayDir.y < 0) texX = settings->texWidth - texX - 1;

        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * settings->texHeight / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - (double) settings->height / 2 + (double) lineHeight / 2) * step;

        for (int y = drawStart; y < drawEnd; y++) {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int) texPos & (settings->texHeight - 1);
            texPos += step;
            Uint32 color = settings->textures[texNum][settings->texHeight * texY + texX];
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if (ddaResult.side == 1) color = (color >> 1) & 2139062016;
            pixels[y][settings->width - x - 1] = color;
        }
    }
}

void displayFloor(struct Settings *settings, struct Player *player, Uint32 (*pixels)[settings->width]) {
    for (int y = 0; y < settings->height; y++) {
        struct DVector rayDir0 = {player->dir.x - player->plane.x, player->dir.y - player->plane.y};
        struct DVector rayDir1 = {player->dir.x + player->plane.x, player->dir.y + player->plane.y};

        int p = y - settings->height / 2;
        double posZ = 0.5 * settings->height;
        double rowDistance = posZ / p;
        struct DVector floorStep = {rowDistance * (rayDir1.x - rayDir0.x) / settings->width,
                                    rowDistance * (rayDir1.y - rayDir0.y) / settings->width};
        struct DVector floorPos = {player->pos.x + rowDistance * rayDir0.x,
                                   player->pos.y + rowDistance * rayDir0.y};
        for (int x = 0; x < settings->width; x++) {
            struct IVector cell = {(int) floorPos.x, (int) floorPos.y};
            struct IVector t = {(int) (settings->texWidth * (floorPos.x - cell.x)) & (settings->texWidth - 1),
                                (int) (settings->texHeight * (floorPos.y - cell.y)) & (settings->texHeight - 1)};
            floorPos.x += floorStep.x;
            floorPos.y += floorStep.y;
            int floorTex = 3;
            int ceilingTex = 4;
            Uint32 color;

            //floor
            color = settings->textures[floorTex][settings->texWidth * t.y + t.x];
            pixels[y][x] = color;

            //ceiling (symmetrical!)
            color = settings->textures[ceilingTex][settings->texWidth * t.y + t.x];
            pixels[settings->height - y - 1][x] = color;
        }

    }
}

struct IVector getStep(struct DVector rayDir) {
    //what direction to step in x or y-direction (either +1 or -1)
    struct IVector step;

    if (rayDir.x < 0) {
        step.x = -1;
    } else {
        step.x = 1;
    }
    if (rayDir.y < 0) {
        step.y = -1;
    } else {
        step.y = 1;
    }

    return step;
}

struct DVector geDist(struct Player *player, struct DVector rayDir, struct DVector deltaDist) {
    struct DVector sideDist;

    //which box of the map we're in
    struct IVector map = {(int) player->pos.x, (int) player->pos.y};

    //calculate step and initial sideDist
    if (rayDir.x < 0) {
        sideDist.x = (player->pos.x - map.x) * deltaDist.x;
    } else {
        sideDist.x = (map.x + 1.0 - player->pos.x) * deltaDist.x;
    }
    if (rayDir.y < 0) {
        sideDist.y = (player->pos.y - map.y) * deltaDist.y;
    } else {
        sideDist.y = (map.y + 1.0 - player->pos.y) * deltaDist.y;
    }

    return sideDist;
}

struct DDAResult dda(struct DVector deltaDist, struct DVector rayDir, struct Player *player,
                     struct Settings *settings) {
    //which box of the map we're in
    struct IVector mapPos = {(int) player->pos.x, (int) player->pos.y};

    //length of ray from current position to next x or y-side
    struct DVector sideDist = geDist(player, rayDir, deltaDist);

    //what direction to step in x or y-direction (either +1 or -1)
    struct IVector step = getStep(rayDir);

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?

    //perform DDA
    while (hit == 0) {
        //jump to next mapPos square, either in x-direction, or in y-direction
        if (sideDist.x < sideDist.y) {
            sideDist.x += deltaDist.x;
            mapPos.x += step.x;
            side = 0;
        } else {
            sideDist.y += deltaDist.y;
            mapPos.y += step.y;
            side = 1;
        }
        //Check if ray has hit a wall
        if (settings->map[mapPos.y][mapPos.x] != 0) hit = 1;
    }

    //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
    double perpWallDist;
    if (side == 0) perpWallDist = (sideDist.x - deltaDist.x);
    else perpWallDist = (sideDist.y - deltaDist.y);

    struct DDAResult ddaResult = {mapPos, perpWallDist, side};

    return ddaResult;
}

void displayMinimap(SDL_Renderer *renderer, struct Settings *settings) {
    int edge = 5;
    SDL_SetRenderDrawColor(renderer, RGB_Black.r, RGB_Black.g, RGB_Black.b, 255);
    SDL_Rect rect = {0, 0, settings->nbColumns * 10 + 2 * edge, settings->nbLines * 10 + 2 * edge};
    SDL_RenderFillRect(renderer, &rect);
    for (int y = 0; y < settings->nbLines; y++) {
        for (int x = 0; x < settings->nbColumns; x++) {
            int texNum = settings->map[y][x];
            int r = texNum * (256 / 8);
            int g = texNum * (256 / 8);
            int b = texNum * (256 / 8);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_Rect rectt = {x * 10 + edge, y * 10 + edge, 10, 10};
            if (SDL_RenderFillRects(renderer, &rectt, 1) != 0) {
                printf("Error: %s\n", SDL_GetError());
            }
        }
    }
}

void displayCompass(SDL_Renderer *renderer, struct Player *player, struct Compass *compass, SDL_Texture *screenBuffer) {
    drawCircle(renderer, compass->borderColor, compass->pos.x, compass->pos.y, compass->size + 10, 5);
    drawCircle(renderer, compass->bgColor, compass->pos.x, compass->pos.y, compass->size + 5, 5);
    int x1 = compass->pos.x;
    int y1 = compass->pos.y;
    int x2 = x1 + (int) (compass->size * (player->dir.x));
    int y2 = y1 + (int) (compass->size * player->dir.y);
    int scale = 5;
    SDL_RenderSetScale(renderer, (float) scale, (float) scale);
    SDL_SetRenderDrawColor(renderer, compass->color.r, compass->color.g, compass->color.b, 255);
    SDL_RenderDrawLine(renderer, x1 / scale, y1 / scale, x2 / scale, y2 / scale);
    SDL_RenderSetScale(renderer, 1, 1);
}

void displayPlayerOnMinimap(SDL_Renderer *renderer, struct Player *player) {
    SDL_RenderSetScale(renderer, 1, 1);
    int edge = 5;
    drawCircle(renderer, RGB_Red, (int) (player->pos.x * 10) + edge, (int) (player->pos.y * 10) + edge, 5, 1);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int x1 = (int) (player->pos.x * 10) + edge;
    int y1 = (int) (player->pos.y * 10) + edge;
    int x2 = x1 + (int) (30 * (player->dir.x));
    int y2 = y1 + (int) (30 * player->dir.y);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawCircle(SDL_Renderer *renderer, SDL_Color color, int x, int y, int radius, int scale) {
    SDL_RenderSetScale(renderer, (float) scale, (float) scale);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, (x + dx) / scale, (y + dy) / scale);
            }
        }
    }
    SDL_RenderSetScale(renderer, 1, 1);
}