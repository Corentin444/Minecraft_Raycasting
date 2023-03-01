# make ; .\CUB_3D.exe
CC = gcc
CFLAGS = -Wall -I include
LDFLAGS = -L libs -lmingw32 -lSDL2main -lSDL2 -mwindows

all : CUB_3D

CUB_3D : main.o
	$(CC) main.o -o CUB_3D $(LDFLAGS)

main.o : sources/main.c
	$(CC) $(CFLAGS) -c sources/main.c -o main.o

# Suppression des fichiers temporaires.
clean :
	del rf *.o

# Suppression de tous les fichiers, sauf les sources,
# en vue d’une reconstruction complète.
mrproper : clean
	del CUB_3D