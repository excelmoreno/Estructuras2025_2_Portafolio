#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

int esPareja(char a, char b);
int validarParentesis(const char *expresion);
int prioridad(char op);
int esOperador(char c);
void infixToPostfix();

void imprimirChar(void *a) {
    char *c = a;
    printf("%c", *c);
}
void liberarChar(void *a) {
    free(a);
}

int main(void) {
    int opcion;

    do {
        printf("\n===== Menu =====\n");
        printf("1. Infix a Postfix\n");
        printf("2. Terminar\n");

        inputEntero("Selecciona una opcion: ", &opcion);

        switch (opcion) {

            case 1:
                infixToPostfix();
                break;

            case 2:
                printf("\nAdios\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }

    } while (opcion != 2);

    return 0;
}


int esPareja(char abre, char cierra) {
    return (abre == '(' && cierra == ')') ||
           (abre == '[' && cierra == ']') ||
           (abre == '{' && cierra == '}');
}

int validarParentesis(const char *expresion) {

    Pila pila = {NULL, -1, 0, &imprimirChar, &liberarChar};

    for (int i = 0; expresion[i] != '\0'; i++) {
        char c = expresion[i];

        if (c == '(' || c == '[' || c == '{') {
            char *p = malloc(sizeof(char));
            *p = c;
            push(&pila, p);
        }
        else if (c == ')' || c == ']' || c == '}') {

            if (vacia(pila)) {
                eliminarPila(&pila);
                return 0; // Se cerro sin abrir
            }

            char *tope = pop(&pila);

            if (!esPareja(*tope, c)) {
                free(tope);
                eliminarPila(&pila);
                return 0; 
            }
            free(tope);
        }
    }

    int valido = vacia(pila);
    eliminarPila(&pila);
    return valido;
}


int prioridad(char op) {
    switch (op) {
        case '^': return 3;
        case '*': 
        case '/': return 2;
        case '+': 
        case '-': return 1;
        default: return 0;
    }
}

int esOperador(char c) {
    return c=='+' || c=='-' || c=='*' || c=='/' || c=='^';
}


void infixToPostfix() {

    char exp[256];
    inputCadena("\nIngresa una expresion infix: ", exp, 256);

    if (!validarParentesis(exp)) {
        printf("\nExpresion invalida: parentesis no equilibrados.\n");
        return;
    }


    Pila operadores = {NULL, -1, 0, &imprimirChar, &liberarChar};

    printf("\nPostfix: ");

    for (int i = 0; exp[i] != '\0'; i++) {

        char c = exp[i];

        if (c == ' ')
            continue;

        if (isalnum(c)) {
            printf("%c ", c);
        }

        else if (c=='(' || c=='[' || c=='{') {
            char *p = malloc(sizeof(char));
            *p = c;
            push(&operadores, p);
        }


        else if (c==')' || c==']' || c=='}') {

            while (!vacia(operadores)) {
                char *tope = pop(&operadores);
                
                if (esPareja(*tope, c)) {
                    free(tope);
                    break;
                }
                printf("%c ", *tope);
                free(tope);
            }
        }


        else if (esOperador(c)) {

            while (!vacia(operadores)) {
                char *tope = (char*) operadores.cima->dato;

                if (!esOperador(*tope)) break;
                if (prioridad(*tope) < prioridad(c)) break;

                tope = pop(&operadores);
                printf("%c ", *tope);
                free(tope);
            }

            char *p = malloc(sizeof(char));
            *p = c;
            push(&operadores, p);
        }
    }


    while (!vacia(operadores)) {
        char *p = pop(&operadores);
        printf("%c ", *p);
        free(p);
    }

    printf("\n");

    eliminarPila(&operadores);
}
