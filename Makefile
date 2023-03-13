SRC = sources/init.c sources/configParser.c sources/game.c sources/display.c sources/player.c sources/utils.c sources/mapParser.c
CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L libs -lmingw32 -lSDL2main -lSDL2 -mwindows -mconsole

all : CUB_3D

CUB_3D :
	$(CC) $(CFLAGS) $(SRC) -o CUB_3D $(LDFLAGS)

# Suppression des fichiers temporaires.
clean :
	del rf *.o

# Suppression de tous les fichiers, sauf les sources,
# en vue d’une reconstruction complète.
mrproper : clean
	del CUB_3D