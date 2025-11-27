# Compilador y flags
CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -O2
INCLUDES = -I ../Estructuras/lista -I ../captura
LIBDIR = ../../lib
BINDIR = ../../bin

# Archivos
PRACTICA_SRC = $(wildcard *.c)
LISTA_SRC = ../Estructuras/lista/Lista.c ../Estructuras/lista/Nodo.c
CAPTURA_SRC = ../captura/captura.c

LISTA_LIB = $(LIBDIR)/libLista.a
CAPTURA_LIB = $(LIBDIR)/libCaptura.a
OUTPUT = $(BINDIR)/practica1.exe

# Objetivos por defecto
all: $(LISTA_LIB) $(CAPTURA_LIB) $(OUTPUT)

# ================================
# Librerías
# ================================
$(LISTA_LIB): $(LISTA_SRC)
	@echo "Compilando libLista.a..."
	$(CC) $(CFLAGS) -c $(LISTA_SRC) $(INCLUDES)
	ar rcs $(LISTA_LIB) *.o
	del /Q *.o || true  # limpia los .o temporales (Windows)

$(CAPTURA_LIB): $(CAPTURA_SRC)
	@echo "Compilando libCaptura.a..."
	$(CC) $(CFLAGS) -c $(CAPTURA_SRC) $(INCLUDES)
	ar rcs $(CAPTURA_LIB) *.o
	del /Q *.o || true

# ================================
# Ejecutable practica1
# ================================
$(OUTPUT): $(PRACTICA_SRC) $(LISTA_LIB) $(CAPTURA_LIB)
	@echo "Compilando practica1.exe..."
	$(CC) $(CFLAGS) $(PRACTICA_SRC) $(INCLUDES) -L$(LIBDIR) -lLista -lCaptura -o $(OUTPUT)

# ================================
# Limpiar
# ================================
clean:
	del /Q $(OUTPUT) || true
	del /Q $(LIBDIR)\libLista.a || true
	del /Q $(LIBDIR)\libCaptura.a || true
