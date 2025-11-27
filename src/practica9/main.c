#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/heap/heap.h"

typedef struct {
    char nombre[128];
    int paginas;
} Documento;

void* crearDocumento(const char* nombre, int paginas);
void imprimirDocumento(void *p);
int compararDocumento(void *a, void *b);
void* eliminarIndiceHeap(Heap *heap, int idx);
void mostrar_primero5(Heap *heap);
void mostrar_estado(Heap *heap, const char *label);
void limpiarEntrada();


int main(void) {
    Heap heap = inicializarHeap(imprimirDocumento, compararDocumento);

    int opcion;
    char nombre[128];
    int paginas;

    while(1) {
        mostrar_primero5(&heap);

        printf("\nMenu:\n");
        printf("[0] CAMBIAR PRIORIDAD\n");
        printf("[1] MOSTRAR COLA DE IMPRESION\n");
        printf("[2] AGREGAR ARCHIVO\n");
        printf("[3] PROCESAR/IMPRIMIR ARCHIVO\n");
        printf("[4] ELIMINAR ARCHIVO\n");
        printf("[5] ELIMINAR TODOS\n");
        printf("[6] SALIR\n");
        printf("Opcion: ");

        if(scanf("%d", &opcion) != 1) {
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();

        switch(opcion) {

            case 0:
                mostrar_estado(&heap, "ANTES CAMBIAR PRIORIDAD");
                heap.tipo = (heap.tipo == MIN) ? MAX : MIN;
                heapify(&heap);
                mostrar_estado(&heap, "DESPUES CAMBIAR PRIORIDAD");
                break;

            case 1:
                mostrar_estado(&heap, "MOSTRAR COLA");
                break;

            case 2:
                mostrar_estado(&heap, "ANTES AGREGAR");
                printf("Nombre: ");
                fgets(nombre, sizeof(nombre), stdin);
                nombre[strcspn(nombre, "\n")] = '\0';

                printf("Paginas: ");
                scanf("%d", &paginas);
                limpiarEntrada();

                insertarHeap(&heap, crearDocumento(nombre, paginas));
                mostrar_estado(&heap, "DESPUES AGREGAR");
                break;

            case 3:
                mostrar_estado(&heap, "ANTES PROCESAR");
                {
                    void *dato = quitarHeap(&heap);
                    if(dato) {
                        printf("Procesando: ");
                        imprimirDocumento(dato);
                        printf("\n");
                        free(dato);
                    } else printf("Cola vacia.\n");
                }
                mostrar_estado(&heap, "DESPUES PROCESAR");
                break;

            case 4:
                mostrar_estado(&heap, "ANTES ELIMINAR");

                if(heap.cantidad == 0) {
                    printf("Cola vacia.\n");
                    break;
                }

                for(int i = 0; i < heap.cantidad; i++) {
                    printf("%d: ", i);
                    heap.imprimir(heap.arr[i]->dato);
                    printf("\n");
                }

                printf("Indice a eliminar: ");
                int idx;
                scanf("%d", &idx);
                limpiarEntrada();

                {
                    void *dato = eliminarIndiceHeap(&heap, idx);
                    if(dato) free(dato);
                }

                mostrar_estado(&heap, "DESPUES ELIMINAR");
                break;

            case 5:
                mostrar_estado(&heap, "ANTES VACIAR");

                while(heap.cantidad > 0) {
                    void *dato = quitarHeap(&heap);
                    if(dato) free(dato);
                }

                heap.arr = NULL;
                heap.arbol.raiz = NULL;
                heap.arbol.cantidad = 0;

                mostrar_estado(&heap, "DESPUES VACIAR");
                break;

            case 6:
                while(heap.cantidad > 0) {
                    void *dato = quitarHeap(&heap);
                    if(dato) free(dato);
                }
                if(heap.arr) free(heap.arr);
                return 0;
        }
    }

    return 0;
}



void* crearDocumento(const char* nombre, int paginas) {
    Documento *d = malloc(sizeof(Documento));
    strncpy(d->nombre, nombre, sizeof(d->nombre)-1);
    d->nombre[sizeof(d->nombre)-1] = '\0';
    d->paginas = paginas;
    return (void*)d;
}

void imprimirDocumento(void *p) {
    Documento *d = (Documento*)p;
    printf("[ %s | %d pag ]", d->nombre, d->paginas);
}

int compararDocumento(void *a, void *b) {
    Documento *da = (Documento*)a;
    Documento *db = (Documento*)b;

    if(da->paginas < db->paginas) return -1;
    if(da->paginas > db->paginas) return 1;
    return 0;
}

void* eliminarIndiceHeap(Heap *heap, int idx) {
    if(idx < 0 || idx >= heap->cantidad) return NULL;

    void *dato = heap->arr[idx]->dato;
    free(heap->arr[idx]);

    int ultima = heap->cantidad - 1;
    heap->cantidad--;

    if(heap->cantidad == 0) {
        free(heap->arr);
        heap->arr = NULL;
    } else {
        if(idx != ultima)
            heap->arr[idx] = heap->arr[ultima];

        NodoA **aux = realloc(heap->arr, sizeof(NodoA*) * heap->cantidad);
        if(aux) heap->arr = aux;
    }

    heapify(heap);
    return dato;
}

void mostrar_primero5(Heap *heap) {
    int limite = (heap->cantidad < 5) ? heap->cantidad : 5;

    printf("\n----- Primeros %d archivos -----\n", limite);
    for(int i = 0; i < limite; i++) {
        printf("%d: ", i);
        heap->imprimir(heap->arr[i]->dato);
        printf("\n");
    }

    if(limite == 0)
        printf("[cola vacia]\n");
}

void mostrar_estado(Heap *heap, const char *label) {
    printf("\n==== %s ====\n", label);

    printf("\nArreglo:\n");
    if(heap->cantidad == 0) printf("[vacio]\n");
    else {
        imprimirHeap(*heap);
        printf("\n");
    }
	
    printf("\nArbol:\n");
    if(heap->arbol.raiz)
        imprimirArbol(heap->arbol);
    else
        printf("[vacio]\n");

    printf("====================\n\n");
}

void limpiarEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
