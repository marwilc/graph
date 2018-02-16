# Makefile
CFLAGS=-c -Wall

# Variables
CC = g++
EJECUTABLE = centrality

# Programa Principal
all: nodeVert.h nodeAdy.h graph.h centrality.cpp
	$(CC) -o $(EJECUTABLE) centrality.cpp 


# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EJECUTABLE) 
