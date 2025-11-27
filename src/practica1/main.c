//INCLUDES
#include <stdio.h>
#include <string.h>
#include "../Estructuras/lista/lista.h"

//FUNCION MAIN

typedef struct
{
	unsigned int matricula;
	char nombre[64];
	int semestres;
	float promedio;
}Alumno;


void* crearEntero(int dato);
int compararEnteros(void *a, void *b);
void imprimirEntero(void *a);
void* crearFlotante(float dato);
int compararFlotante(void *a, void *b);
void imprimirFlotante(void *a);

void* crearAlumno( Alumno a);
int compararAlumnos(void *a,void *b);
void imprimirAlumno(void *a);
void mostrarMenu();
Alumno capturarAlumno();

int compararMatricula(void *a, void *b);

int compararSemestre(void *a, void *b);

int compararPromedio(void *a, void *b);

int compararCadena(void *a, void *b);

int main(void)
{
	Lista lista;
	lista.inicio = NULL;
	lista.cant = 0;
	lista.imprimir = &imprimirAlumno;
	lista.comparar = &compararMatricula;
	int opcion;
    do {
	void* busqueda = NULL;
    	
	Alumno *al;
	

        mostrarMenu();
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
            	insertarOrdenado(&lista,crearAlumno(capturarAlumno()));
                break;
            case 2:
             	mostrarLista(lista);
                break;
            case 3:
		{
	    	int opcion2;
    		do {
			printf("\n");
        		printf("\n===== REORDENAR ALUMNOS =====\n");
       			printf("1. Por matricula\n");
        		printf("2. Por nombre\n");
        		printf("3. Por semestres\n");
        		printf("4. Por promedio\n");
        		printf("5. Regresar al menu principal\n");
        		printf("Seleccione una opcion: ");
        		scanf("%d", &opcion2);
			
			
			Lista aux;
               		aux.inicio = NULL;
			aux.cant = 0;
			aux.imprimir = &imprimirAlumno;
        		switch(opcion2) {
				
            			case 1:	
					aux.comparar = &compararMatricula;
                		break;
            			case 2:
   					aux.comparar = &compararAlumnos;
                		break;
            			case 3:
					aux.comparar = &compararSemestre;
               			break;
            			case 4:
					aux.comparar = &compararPromedio;
                		break;
            			case 5:
            
                		break;
            			default:
                		printf("Opcion invalida. Intente de nuevo.\n");
        		}
			Nodo* p = lista.inicio;
			while(p != NULL) {
    				insertarOrdenado(&aux, p->dato);
    				p = p->sig;
			}
			borrarLista(&lista);
			lista = aux;
    		} while(opcion2 != 5);
            break;
	    }
            case 4:
	    {
                int opcion3;
    		do {
			printf("\n");
        		printf("\n===== BUSCAR ALUMNOS =====\n");
       			printf("1. Por matricula\n");
        		printf("2. Por nombre\n");
        		printf("3. Por semestres\n");
        		printf("4. Por promedio\n");
        		printf("5. Regresar al menu principal\n");
        		printf("Seleccione una opcion: ");
        		scanf("%d", &opcion3);	

			void* busqueda = NULL;
    			unsigned int mat; 
    			char nombre[64]; 
    			int sem;
    			float prom;
			Nodo* p = lista.inicio;
			Alumno *al;

        		switch(opcion3) {
        			case 1:
            				lista.comparar = &compararEnteros; 
       					printf("Ingrese matricula a buscar: ");
        				scanf("%u", &mat);
        				busqueda = &mat;
        				for(p = lista.inicio; p != NULL; p = p->sig) {
            					al = (Alumno*)p->dato;
            					if(lista.comparar(busqueda, &al->matricula) == 0){
                					lista.imprimir(al);
						}
        				}

            			break;

        			case 2:
            				lista.comparar = &compararCadena; 
       					printf("Ingrese nombre a buscar: ");
        				scanf(" %[^\n]", nombre);
        				busqueda = nombre;
        				for(p = lista.inicio; p != NULL; p = p->sig) {
            					al = (Alumno*)p->dato;
            					if(lista.comparar(busqueda, &al->nombre) == 0){
                					lista.imprimir(al);
						}
        				}
    					
            			break;

        			case 3:
            				lista.comparar = &compararEnteros; 
       					printf("Ingrese semestres a buscar: ");
        				scanf("%d", &sem);
        				busqueda = &sem;
        				for(p = lista.inicio; p != NULL; p = p->sig) {
            					al = (Alumno*)p->dato;
            					if(lista.comparar(busqueda, &al->semestres) == 0){
                					lista.imprimir(al);
						}
        				}
    					
            			break;

        			case 4:
            				lista.comparar = &compararFlotante; 
       					printf("Ingrese promedio a buscar: ");
       		 			scanf("%f", &prom);
        				busqueda = &prom;
        				for(p = lista.inicio; p != NULL; p = p->sig) {
            					al = (Alumno*)p->dato;
            					if(lista.comparar(busqueda, &al->promedio) == 0){
                					lista.imprimir(al);
						}
        				}
            			break;

        			case 5:
            			break;

        			default:
            				printf("Opcion invalida. Intente de nuevo.\n");
            			
    			}	
			
    		} while(opcion3 != 5);
  	    }
            break;
            case 5:{
		unsigned int mat; 
		int pos=0;
		lista.comparar = &compararEnteros; 
		Nodo* p = lista.inicio;
		printf("Ingrese matricula a buscar: ");
        	scanf("%u", &mat);
        	busqueda = &mat;
            	while(p != NULL) {
    			al = (Alumno*)p->dato;
    			if(lista.comparar(busqueda, &al->matricula) == 0) {
        		Nodo *tmp = p->sig;          
        		eliminarEnPosicion(&lista, pos);
        		p = tmp;                    
        
    			} else {
        		p = p->sig;
        		pos++;                       
    			}
		}
		}
            break;
            case 6:
            
            break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while(opcion != 6);
	
	return 0;
}


void* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEnteros(void *a, void *b)
{
	int *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}

void imprimirEntero(void *a)
{
	int *ea;
	ea = a;
	printf("%d",*ea);
}

void* crearFlotante(float dato)
{
	float *nuevo = malloc(sizeof(float));
	*nuevo = dato;
	return nuevo;
}



int compararFlotante(void *a, void *b)
{
	float *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}


void imprimirFlotante(void *a)
{
	float *ea;
	ea = a;
	printf("%.2f",*ea);
}


void* crearAlumno( Alumno a)
{
	Alumno *nuevo = malloc(sizeof(Alumno));
	*nuevo = a;
	return nuevo;	
}

int compararAlumnos(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	return strcmp( aa->nombre,ab->nombre);
}
void imprimirAlumno(void *a)
{
	Alumno *aa;
	aa = a;
	printf("\n");
	printf("\nMatricula: %d",aa->matricula);
	printf("\nNombre: %s",aa->nombre);
	printf("\nSemestres: %d",aa->semestres);
	printf("\nPromedio: %.2f", aa->promedio);
	
}
int compararMatricula(void *a, void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;

	if( aa->matricula < ab->matricula )
		return -1;
	else if ( aa->matricula > ab->matricula )
		return 1;
	else
		return 0;	
}
int compararSemestre(void *a, void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;

	if( aa->semestres < ab->semestres )
		return -1;
	else if ( aa->semestres > ab->semestres )
		return 1;
	else
		return 0;
}
int compararPromedio(void *a, void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;

	if( aa->promedio < ab->promedio )
		return -1;
	else if ( aa->promedio > ab->promedio)
		return 1;
	else
		return 0;	
}

int compararCadena(void *a, void *b)
{
	char *ea,*eb;
	ea = a;
	eb = b;
	return strcmp( ea,eb);
}

void mostrarMenu() {
    printf("\n");
    printf("\n===== MENU DE ALUMNOS =====\n");
    printf("1. Registrar Alumno\n");
    printf("2. Desplegar Alumnos\n");
    printf("3. Reordenar Alumnos\n");
    printf("4. Buscar Alumno\n");
    printf("5. Borrar Alumno\n");
    printf("6. Finalizar Programa\n");
    printf("Seleccione una opcion: ");
}

Alumno capturarAlumno() {
    Alumno a;
    printf("Ingrese matricula: ");
    scanf("%u", &a.matricula);
    printf("Ingrese nombre: ");
    scanf(" %[^\n]", a.nombre); 
    printf("Ingrese semestres: ");
    scanf("%d", &a.semestres);
    printf("Ingrese promedio: ");
    scanf("%f", &a.promedio);
    return a;
}