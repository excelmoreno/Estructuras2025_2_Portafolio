# Variables
CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99 -O2 -c
AR = ar
ARFLAGS = rcs
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
LIB = ../../../lib/libLista.a

# Regla principal
all: $(LIB)

# Crear la librería
$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Compilar archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Limpiar archivos intermedios
clean:
	del /Q *.o
	del /Q $(LIB)
