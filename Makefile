SRC = sources/init.c sources/configParser.c sources/game.c sources/display.c sources/player.c sources/utils.c sources/mapParser.c
CC = gcc
INCLUDE = -I include -I libs/include # Includes
LIBS = -L libs/bin # Librairies
CFLAGS = -Wall # Compilation flags
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows -mconsole # Linker flags
all : CUB_3D

CUB_3D :
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $(SRC) $(LDFLAGS) -o CUB_3D

clean :
	del rf *.o

mrproper : clean
	del CUB_3D