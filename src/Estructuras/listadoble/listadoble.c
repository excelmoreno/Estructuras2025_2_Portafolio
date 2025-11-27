#include "listadoble.h"
#include <stdio.h>


ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL,NULL};
}
void mostrarListaD(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: ",lista.cant);
	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
	{
		printf(" ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL");
}

void borrarListaD(ListaD *lista)
{
    NodoD *actual,*tmp;
    actual = lista->inicio;
    while(actual != NULL)
    {
        tmp = actual->sig;
        free(actual);
        actual = tmp;
    }
    lista->inicio = NULL;
    lista->fin = NULL;
    lista->cant = 0;
}

void insertarOrdenadoD(ListaD *lista, void *dato)
{
    NodoD *nuevo = crearNodoD(dato);
    NodoD *p = lista->inicio;

    if(lista->inicio == NULL)
    {
        lista->inicio = nuevo;
        lista->fin = nuevo;
        lista->cant++;
        return;
    }

    while(p != NULL && lista->comparar(dato, p->dato) > 0)
        p = p->sig;

    if(p == lista->inicio)
    {
        nuevo->sig = lista->inicio;
        lista->inicio->ant = nuevo;
        lista->inicio = nuevo;
    }
    else if(p == NULL)
    {
        nuevo->ant = lista->fin;
        lista->fin->sig = nuevo;
        lista->fin = nuevo;
    }
    else
    {
        nuevo->sig = p;
        nuevo->ant = p->ant;
        p->ant->sig = nuevo;
        p->ant = nuevo;
    }
    lista->cant++;
}

void eliminarEnPosicionD(ListaD *lista, int pos)
{
    if(pos < 0 || pos >= lista->cant)
        return;

    NodoD *p = lista->inicio;
    for(int i=0;i<pos;i++)
        p = p->sig;

    if(p->ant != NULL)
        p->ant->sig = p->sig;
    else
        lista->inicio = p->sig;

    if(p->sig != NULL)
        p->sig->ant = p->ant;
    else
        lista->fin = p->ant;

    free(p);
    lista->cant--;
}

void mostrarListaDAsc(ListaD lista)
{
    NodoD *p = lista.inicio;
    while(p != NULL)
    {
        lista.imprimir(p->dato);
        p = p->sig;
    }
}

void mostrarListaDDes(ListaD lista)
{
    NodoD *p = lista.fin;
    while(p != NULL)
    {
        lista.imprimir(p->dato);
        p = p->ant;
    }
}