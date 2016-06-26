# Makefile
CFLAGS=-c -Wall

# Variables
CC = g++
EJECUTABLE = MAIN

# Programa Principal
all: nodeVert.h nodeAdy.h graph.h main1.cpp
	$(CC) main1.cpp -o $(EJECUTABLE)


# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EJECUTABLE) 
