# Makefile
CFLAGS=-c -Wall -g

# Variables
CC = g++
EJECUTABLE = MAIN

# Programa Principal
all: nodeVert.h nodeAdy.h graph.h criticalLinks.cpp
	$(CC) -g -o $(EJECUTABLE) criticalLinks.cpp 


# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EJECUTABLE) 
