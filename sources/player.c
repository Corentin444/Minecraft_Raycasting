#include <math.h>

#include "../include/player.h"

struct Player *initPlayer() {
    struct Player *player = malloc(sizeof(struct Player));
    // TODO find a free position to spawn the player
    player->pos.x = 5;
    player->pos.y = 5;
    player->dir.x = -1;
    player->dir.y = 0;
    player->plane.x = 0;
    player->plane.y = 0.66;
    player->moveSpeed = 0.1;
    player->rotSpeed = 0.05;
    return player;
}

void move(struct Player *player, struct Settings *settings, int direction, double frameTime) {
    // Création d'une nouvelle variable pour ne pas modifier l'anciennes
    struct DVector newPos = player->pos;

    // Calcule le ratio entre le temps de la frame et la vitesse de déplacement du joueur pour avoir une vitesse constante quelque soit la fréquence d'actualisation
    double moveSpeed = frameTime * 5.0;

    // Avance d'une case si direction = 1
    if (direction == 1) {
        newPos.x += player->dir.x * moveSpeed;
        newPos.y += player->dir.y * moveSpeed;
    }
    // Recule d'une case si direction = -1
    if (direction == -1) {
        newPos.x -= player->dir.x * moveSpeed;
        newPos.y -= player->dir.y * moveSpeed;
    }
    // Met à jour la position du joueur si la nouvelle position n'est pas un mur et on ajoute une petite marge en fonction de la direction du joueur
    if (settings->map[(int) (newPos.y + direction * player->dir.y * 0.5)][(int) (newPos.x)] == 0) {
        player->pos.y = newPos.y;
    }
    if (settings->map[(int) (newPos.y)][(int) (newPos.x + direction * player->dir.x * 0.5)] == 0) {
        player->pos.x = newPos.x;
    }
}

void rotate(struct Player *player, int direction, double frameTime) {
    // Création de nouvelles variables pour ne pas modifier les anciennes
    struct DVector newDir = player->dir;
    struct DVector newPlane = player->plane;

    // Calcule le ratio entre le temps de la frame et la vitesse de rotation du joueur pour avoir une vitesse constante quelque soit la fréquence d'actualisation
    double rotSpeed = frameTime * 2.5;

    // Tourne à gauche si direction = 1
    if (direction == 1) {
        newDir.x =
                player->dir.x * cos(-rotSpeed) - player->dir.y * sin(-rotSpeed);
        newDir.y =
                player->dir.x * sin(-rotSpeed) + player->dir.y * cos(-rotSpeed);
        newPlane.x = player->plane.x * cos(-rotSpeed) - player->plane.y * sin(-rotSpeed);
        newPlane.y = player->plane.x * sin(-rotSpeed) + player->plane.y * cos(-rotSpeed);
    }
    // Tourne à droite si direction = -1
    if (direction == -1) {
        newDir.x =
                player->dir.x * cos(rotSpeed) - player->dir.y * sin(rotSpeed);
        newDir.y =
                player->dir.x * sin(rotSpeed) + player->dir.y * cos(rotSpeed);
        newPlane.x = player->plane.x * cos(rotSpeed) - player->plane.y * sin(rotSpeed);
        newPlane.y = player->plane.x * sin(rotSpeed) + player->plane.y * cos(rotSpeed);
    }
    // Met à jour la direction et le plan du joueur
    player->dir = newDir;
    player->plane = newPlane;
}