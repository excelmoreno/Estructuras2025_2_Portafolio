#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"


void imprimirChar(void *a);
void liberarChar(void *a);
void verificarPalindromo() ;
int esPareja(char abre, char cierra);
void verificarParentesis();

int main(void) {
    int opcion;

    do {
        printf("\n===== Menu =====\n");
        printf("1. Palindromo\n");
        printf("2. Verificacion de parentesis\n");
        printf("3. Terminar\n");

        inputEntero("Selecciona una opcion: ", &opcion);

        switch (opcion) {
            case 1:
                verificarPalindromo();
                break;

            case 2:
                verificarParentesis();
                break;

            case 3:
                printf("\nAdios\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }

    } while (opcion != 3);

    return 0;
}
void imprimirChar(void *a) {
    char *c = a;
    printf("%c", *c);
}

void liberarChar(void *a) {
    free(a);
}
void verificarPalindromo() {
    char cadena[256];
    inputCadena("\nIngresa una cadena: ", cadena, 256);

    Pila pila1 = {NULL, -1, 0, &imprimirChar, &liberarChar};
    Pila pila2 = {NULL, -1, 0, &imprimirChar, &liberarChar};

    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] != ' ') {
            char *c = malloc(sizeof(char));
            *c = tolower(cadena[i]);
            push(&pila1, c);
        }
    }

    Nodo *aux = pila1.cima;
    while (aux != NULL) {
        char *c = malloc(sizeof(char));
        *c = *(char*)aux->dato;
        push(&pila2, c);
        aux = aux->sig;
    }

    printf("\nPila original: ");
    imprimirPila(pila1);

    printf("\nPila invertida: ");
    imprimirPila(pila2);

    int esPalindromo = 1;

    while (!vacia(pila1) && !vacia(pila2)) {
        char *a = pop(&pila1);
        char *b = pop(&pila2);
        if (*a != *b)
            esPalindromo = 0;
        free(a);
        free(b);
    }

    if (esPalindromo)
        printf("\nLa cadena es palindromo.\n");
    else
        printf("\nLa cadena no es palindromo.\n");

    eliminarPila(&pila1);
    eliminarPila(&pila2);
}



int esPareja(char abre, char cierra) {
    return (abre == '(' && cierra == ')') ||
           (abre == '[' && cierra == ']') ||
           (abre == '{' && cierra == '}');
}

void verificarParentesis() {
    char cadena[256];
    inputCadena("\nIngresa una cadena: ", cadena, 256);

    Pila pila = {NULL, -1, 0, &imprimirChar, &liberarChar};

    for (int i = 0; cadena[i] != '\0'; i++) {
        char c = cadena[i];

        if (c == '(' || c == '[' || c == '{') {
            char *p = malloc(sizeof(char));
            *p = c;
            push(&pila, p);
        }
        else if (c == ')' || c == ']' || c == '}') {
            if (vacia(pila)) {
                printf("\nInvalido: se cerro '%c' sin abrir.\n", c);
                return;
            }

            char *tope = pop(&pila);

            if (!esPareja(*tope, c)) {
                printf("\nInvalido: '%c' no cierra '%c'\n", c, *tope);
                free(tope);
                return;
            }

            free(tope);
        }
    }

    if (!vacia(pila)) {
        printf("\nInvalido: quedaron simbolos sin cerrar.\n");
        eliminarPila(&pila);
    } else {
        printf("\nCadena valida.\n");
    }
}
