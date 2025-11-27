#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"

#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 50

typedef struct
{
    Cola cola;
    int estado;
} Caja;

int* generar_articulos(void);
void imprimirEntero(void* a);
void escanearArticulos(Caja cajas[]);
void habilitarCaja(Caja cajas[]);
void deshabilitarCaja(Caja cajas[]);
void eliminarCajas(Caja cajas[]);

int main(void)
{
    srand(time(NULL));

    Caja cajas[NUMERO_CAJAS];

    for(int i=0; i<NUMERO_CAJAS ; i++)
    {
        cajas[i].cola = inicializarCola();
        cajas[i].cola.imprimir = &imprimirEntero;
        cajas[i].estado = HABILITADA;
    }

    int opcion = 0;

    do
    {


        printf("=========== CAJAS ===========\n");
        for(int i=0; i<NUMERO_CAJAS ; i++)
        {
            printf("[%d] ",i+1);

            if(cajas[i].estado == HABILITADA)
                printf("(H) ");
            else
                printf("(D) ");

            imprimirCola(cajas[i].cola);
            printf("\n");
        }

        printf("\n=============== MENU ===============");
        printf("\n[1] Generar clientes");
        printf("\n[2] Escanear articulos");
        printf("\n[3] Habilitar caja");
        printf("\n[4] Deshabilitar caja");
        printf("\n[5] Terminar programa");

        inputEntero("\n\nSelecciona opcion: ", &opcion);

        switch(opcion)
        {
            case 1:
                for(int i=0; i<NUMERO_CAJAS ; i++)
                {
                    if(cajas[i].estado == HABILITADA && !llenaC(cajas[i].cola))
                        enqueue(&cajas[i].cola, generar_articulos());
                }
                break;

            case 2:
                escanearArticulos(cajas);
                break;

            case 3:
                habilitarCaja(cajas);
                break;

            case 4:
                deshabilitarCaja(cajas);
                break;

            case 5:
                eliminarCajas(cajas);
                printf("\nAdios\n");
                break;

            default:
                printf("\nOpcion invalida\n");
        }

    } while(opcion != 5);

    return 0;
}


int* generar_articulos(void)
{
    int *art = malloc(sizeof(int));
    *art = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
    return art;
}

void imprimirEntero(void *a)
{
    int *x = a;
    printf("%d", *x);
}

void escanearArticulos(Caja cajas[])
{
    int atendio = 0;

    for(int i = 0; i < NUMERO_CAJAS; i++)
    {
        if(cajas[i].estado == HABILITADA && !vaciaC(cajas[i].cola))
        {
            int *cliente = peekC(cajas[i].cola);

            (*cliente)--; 

            

            if(*cliente <= 0)
            {
                cliente = dequeue(&cajas[i].cola);
                free(cliente);
            }   
            atendio = 1;
        }
    }
    if(atendio)
    printf("\nSe escanearon los articulos\n");
    if(!atendio)
        printf("\nNo hay clientes\n");
}


void habilitarCaja(Caja cajas[])
{
    int n;
    inputEntero("\nSelecciona caja a habilitar (1-5): ", &n);

    if(n < 1 || n > NUMERO_CAJAS)
    {
        printf("\nCaja invalida.\n");
        return;
    }

    n--;

    if(cajas[n].estado == HABILITADA)
        printf("\nLa caja %d ya esta habilitada.\n", n+1);
    else
    {
        cajas[n].estado = HABILITADA;
        printf("\nCaja %d habilitada.\n", n+1);
    }
}

void deshabilitarCaja(Caja cajas[])
{
    int n;
    inputEntero("\nSelecciona caja a deshabilitar (1-5): ", &n);

    if(n < 1 || n > NUMERO_CAJAS)
    {
        printf("\nCaja invalida.\n");
        return;
    }

    n--;

    if(cajas[n].estado == DESHABILITADA)
        printf("\nLa caja %d ya esta deshabilitada.\n", n+1);
    else
    {
        cajas[n].estado = DESHABILITADA;
        printf("\nCaja %d deshabilitada.\n", n+1);
    }
}

void eliminarCajas(Caja cajas[])
{
    for(int i=0; i<NUMERO_CAJAS; i++)
        eliminarCola(&cajas[i].cola);
}