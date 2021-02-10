#include "arbolesADT.h"
#include "manejoArch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <math.h>
#define BLOQUE 15
#define EPSILON 0.0000000001

struct Tnodo3 {
    TQ3 Q3;
    calleArbol * ArbolVec;
    int dimArbolVec;
    calleArbol * calleVec;
    int dimcalleVec;
    struct Tnodo3 * cola;
};

typedef struct Tnodo3 * TList3;

struct Tnodo4 {
    TQ4 Q4;
    struct Tnodo4 * cola;
};

typedef struct Tnodo4 * TList4;

struct arbolesCDT {
    TList3 list3;
    int dim3;

    TList4 list4;
    int dim4;
};

arbolesADT nuevaData () {
    arbolesADT arbol = calloc(1, sizeof(struct arbolesCDT));
    if (arbol == NULL || errno == ENOMEM) {
        return NULL;
    }
    return arbol;
}

static TList3 agregaBarrioRec (TList3 list, const char * barrio, int poblacion, int *agregado) {
    if (list==NULL || strcasecmp(barrio, list->Q3.barrio)<0) {
        TList3 aux=calloc(1,sizeof(*aux));
        if (aux == NULL || errno == ENOMEM) {
            return NULL;
        }
        aux->Q3.barrio=malloc(sizeof(char)*(strlen(barrio)+1));
        if (aux->Q3.barrio==NULL || errno == ENOMEM) {
            return NULL;
        }
        strcpy(aux->Q3.barrio, barrio);
        aux->Q3.poblacion=poblacion;
        aux->cola=list;
        *agregado = 1;
        return aux;
    }
    list->cola=agregaBarrioRec(list->cola, barrio, poblacion, agregado);
    return list;
}

int agregaBarrio (arbolesADT adt, const char * barrio, int poblacion) {
    int agregado = 0;
    adt->list3=agregaBarrioRec(adt->list3, barrio, poblacion, &agregado);
    adt->dim3 += agregado;
    return adt->list3!=NULL;
}

/* Funcion Auxiliar A: Recibe un vector de estructuras, un entero y un vector de caracteres. 
Me guarda informacion sobre:
    - Calles y cantidad de arboles en cada una. 
    - Especies y cantidad de arboles de cada una.
*/
static calleArbol * valorHaciaVector(calleArbol * vec, int * dim, const char * nombre) {
    int i;
    for (i=0 ; i<*dim ; i++) {
        if (!strcmp(vec[i].nombre, nombre)) {
            vec[i].dato++;
            return vec;
        }
    }
    if (*dim%BLOQUE==0) {
        vec=realloc(vec, sizeof(*vec)*(*dim+BLOQUE));
        if (vec==NULL || errno == ENOMEM) {
            return NULL;
        }
    }
    vec[*dim].nombre=malloc(sizeof(char)*(strlen(nombre)+1));
    strcpy(vec[*dim].nombre,nombre);
    vec[(*dim)++].dato=1;
    return vec;
}

/* Funcion Auxiliar B: Recibe un barrio, una calle, un arbol y el diametro del mismo. 
La funcion busca el barrio y guarda informacion sobre calle, y arboles del barrio. */
static int buscaBarrio(TList3 list, const char * barrio, const char * calle, const char * arbol, double diam) {
    int c;
    if (list==NULL || (c=strcasecmp(barrio, list->Q3.barrio))<0)
        return 1;
    if (c==0) {
        list->Q3.diametroTotal += diam;
        list->Q3.cantArb++;
        list->ArbolVec=valorHaciaVector(list->ArbolVec, &list->dimArbolVec, arbol);
        if (list->ArbolVec==NULL)
            return 0;

        list->calleVec=valorHaciaVector(list->calleVec, &list->dimcalleVec, calle);
        if (list->calleVec==NULL)
            return 0;

        return 1;
    }
    return buscaBarrio(list->cola, barrio, calle, arbol, diam);
}

static TList4 agregaArbolRecQ4(TList4 list, const char * nombre, double diam, int * agregado) {
    int c;
    if (list==NULL || (c=strcasecmp(nombre, list->Q4.arbol))<0) {
        TList4 aux=malloc(sizeof(*aux));
        if (aux==NULL || errno == ENOMEM) {
            return NULL;
        }
        aux->Q4.arbol=malloc(sizeof(char)*(strlen(nombre)+1));
        if(aux->Q4.arbol==NULL || errno == ENOMEM) {
            return NULL;
        }
        strcpy(aux->Q4.arbol, nombre);
        aux->Q4.dMin=aux->Q4.dMax=diam;
        aux->cola=list;
        *agregado = 1;
        return aux;
    }
    if (c==0) {
        if (diam<list->Q4.dMin)
            list->Q4.dMin=diam;
        else if (diam>list->Q4.dMax)
            list->Q4.dMax=diam;
        return list;
    }
    list->cola=agregaArbolRecQ4(list->cola, nombre, diam, agregado);
    return list;
}

int agregaArbol (arbolesADT adt, const char * barrio, const char * calle, const char * arbol, double diam) {
    int agregado = 0;
    adt->list4=agregaArbolRecQ4(adt->list4, arbol, diam, &agregado);
    adt->dim4+=agregado;
    return adt->list4!=NULL && buscaBarrio(adt->list3, barrio, calle, arbol, diam);
}

/* Funcion Auxiliar C: Recibe un vector de estructuras, y la dimension del mismo. 
    Compara los campos .dato entre dim estructuras y guarda el mayor de todos.
*/
static calleArbol popValor(calleArbol * vec, int dim) {
  calleArbol aux;
  aux.dato=0;
  for (int i=0 ; i<dim ; i++) {
    if (vec[i].dato>aux.dato)
      aux=vec[i];
  }
  return aux;
}

TQ3 * resolQ3(arbolesADT adt, int * dim) {
    TQ3 *vec = malloc(sizeof(TQ3) * adt->dim3);
    if (vec==NULL)
        return NULL;
    *dim=adt->dim3;
    size_t k = 0;
    TList3 aux = adt->list3;
    while (aux != NULL) {
        aux->Q3.popCalle=popValor(aux->calleVec, aux->dimcalleVec);
        vec[k++]=aux->Q3;
        aux = aux->cola;
    }
    return vec;
}

/* Funcion Auxiliar D: Recibe un double.
   Trunca el valor recibido a dos decimales.
*/
static void truncar(double *val) {
    *val *= 100;
    int aux = (int)*val;
    *val = aux/100.0;
}

/* Funcion Auxiliar E: 
    Compara entre dos valores del tipo DOUBLE, contenidos en una estructura del tipo CalleArbolB.
    Retorna 0 si son considerados iguales. 
    Retorna 1 si el segundo es mayor que el primero.
    Retorna -1 si el segundo es menor que el primero.
*/
static int compare (const void * a, const void * b)
{
  double epsilon=0.0001;
  double c2 = ((calleArbolB *)b)->dato;
	double c1 = ((calleArbolB *)a)->dato;
  if(fabs(c2-c1)<epsilon)
    return 0;
  if (c2 > c1) return 1;
  return -1;
}

/* Funcion Auxiliar F: 
    Compara entre dos valores del tipo DOUBLE,
    Retorna 0 si son considerados iguales. 
    Retorna 1 si el segundo es mayor que el primero.
    Retorna -1 si el segundo es menor que el primero.
*/
static int compare2(double a, double  b)
{
  double epsilon=0.0000001;
if( fabs(a-b)<epsilon)
    return 0;
else if ( a > b ) 
    return 1;
return -1;
}


calleArbolB * resolQ1 (arbolesADT adt, int *dim){
    *dim = adt->dim3;
    calleArbolB * vecInf = malloc( sizeof(calleArbolB) * (*dim));
    if (vecInf==NULL)
        return NULL;
    TList3 aux = adt->list3;
    double auxProm = 0;
    int i =0;
    while ( aux != NULL && i < *dim ) {
       auxProm = ( aux->Q3.diametroTotal / (double)(aux->Q3.cantArb) );
        truncar(&auxProm);
        vecInf[i].nombre = aux->Q3.barrio;
        vecInf[i].dato = auxProm;
        aux = aux->cola;
        i++;
    }
    qsort(vecInf, *dim, sizeof(calleArbolB),compare);
    return vecInf;
}


/* Funcion Auxiliar F: 
    Compara entre dos vectores de caracteres contenidos en una estructura del tipo CalleArbolC. */
static int cmpShift(const void* lhs, const void* rhs)
{
    return strcmp(((calleArbolC*)lhs)->nombre, ((calleArbolC*)rhs)->nombre);
}


/* Funcion Auxiliar G: 
    Ordena vector de estructuras del tipo calleArbolC .*/
static void sort_data(calleArbolC shift_data[], int *num_shifts)
{
    qsort(shift_data, *num_shifts, sizeof(calleArbolC), cmpShift);
}

calleArbolC resolQ2B ( calleArbol * calleArbolVec, int dim, int poblacion, char * hood){
   int  i;
    calleArbolC aux = {hood,NULL,0};
    double maxValue = 0;
    double valEsp =0;
    int pos = 0;
    for ( i = 0; i < dim; i++ ){
        valEsp = calleArbolVec[i].dato/ ((double)poblacion);
        if ( compare2( valEsp, maxValue) == 1 ){
            maxValue = valEsp;
            pos = i;
        }
    }

    aux.nombre2= calleArbolVec[pos].nombre;
    truncar(&maxValue);
    aux.dato = maxValue;
    return aux;
}

calleArbolC * resolQ2( arbolesADT adt, int *dim ){
    *dim = adt->dim3;
    calleArbolC * vecInf = malloc( sizeof(calleArbolC) * (*dim));
    if (vecInf==NULL)
        return NULL;
    TList3 aux = adt->list3;
    int i =0;
    while ( aux != NULL && i < *dim ) {
       vecInf[i] = resolQ2B( aux->ArbolVec, aux-> dimArbolVec, aux->Q3.poblacion, aux->Q3.barrio);
       aux = aux->cola;
        i++;
    }
    sort_data( vecInf, dim);
    return vecInf;
}

TQ4 * resolQ4(arbolesADT adt, int * dim) {
    TQ4 *vec = malloc(sizeof(TQ4) * adt->dim4);
    if (vec==NULL)
        return NULL;
    *dim=adt->dim4;
    size_t k = 0;
    TList4 aux = adt->list4;
    while (aux != NULL) {
        vec[k++] = aux->Q4;
        aux = aux->cola;
    }
    return vec;
}

static void freeVecElems(calleArbol * vec, int dim) {
    for (int i=0 ; i<dim ; i++) {
        free(vec[i].nombre);
    }
    return;
}

static void freelist3(TList3 list) {
    if (list == NULL)
        return;
    freeVecElems(list->ArbolVec, list->dimArbolVec);
    free(list->ArbolVec);
    freeVecElems(list->calleVec, list->dimcalleVec);
    free(list->calleVec);
    free(list->Q3.barrio);
    freelist3(list->cola);
    free(list);
}

static void freeList4(TList4 list) {
    if (list == NULL)
        return;
    free(list->Q4.arbol);
    freeList4(list->cola);
    free(list);
}

void freeADT (arbolesADT adt) {
    freelist3(adt->list3);
    freeList4(adt->list4);
    free(adt);
    return;
}


int comparaAux( char * a, char *b ){
     return  strcasecmp(a,b);
}
