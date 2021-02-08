#ifndef arbolesADT_H
#define arbolesADT_H

typedef struct arbolesCDT * arbolesADT;

/*Estructura generica que guarda un nombre y un entero*/
typedef struct {
    char * nombre;
    int dato;
}calleArbol;

typedef struct {
    char * nombre;
    double dato;
}calleArbolB;

/* Estructura que sera retornada en forma de un vector en las siguientes funciones. nombreBarrio es un vector de caracteres
que guarda el nombre del barrio. Las siguientes variables guardan un valor relacionado al barrio dado. popArbol guarda el
nombre del arbol mas popular y la cantidad. Popcalle guarda la calle con la mayor cantidad de arboles.
piblacion es un entero que guarda la poblacion y cantArb guarda la cantidad total de arboles. diametroTotal guarda el diametro*/
typedef struct {
    char * barrio;
    calleArbol popCalle;
    int poblacion;
    int cantArb;
    double diametroTotal;
}TQ3;

/*Estructura que sera retornada en forma de array en las siguientes funciones. tree es un vector de caracteres
que guarda el nombre de una especie de arbol dada. dmin guarda el minimo diametro guardado, dMax guarda el maximo diametro
guardado*/
typedef struct {
    char * arbol;
    double dMin;
    double dMax;
}TQ4;

/*Retorna un puntero al nuevo tipo de datos*/
arbolesADT nuevaData();

/* Agrega un barrio, con su poblacion. Retorna 1 si el barrio se agrego de forma correcta, si se reporta
un problema mientras se asgina memoria, retorna 0.*/
int agregaBarrio (arbolesADT adt, const char * barrio, int poblacion);

/* Agrega especie de arboles, Retorna 1 si el barrio se anadio de forma correcta, si se reporta
un problema mientras se asgina memoria, retorna 0.*/
int agregaArbol (arbolesADT adt, const char * barrio, const char *calle , const char * arbol, double diam);


calleArbolB * resolQ1(arbolesADT adt, int *dim);


/*Retorna un vector de TQ23 estructura que es ordenado por nombre de barrio en orden alfabetico.
La dimension del array es guardada en *dim. Si el array es generado correctamente, el puntero retorna un valor
diferente de null, si hay un problema mientras se asigna memoria, el valor de retorno es NULL. */
TQ3 * resolQ3(arbolesADT adt, int * dim);


/*Retorna un vector de TQ4 structuras ordenado por el nombre de los arboles en orden alfabetico.
La dimension del array es guardada en *dim. Si el array es generado correctamente, el puntero retorna un valor
diferente de null, si hay un problema mientras se asigna memoria, el valor de retorno es NULL. */
TQ4 * resolveQ4(arbolesADT adt, int * dim);

/*Libera todos los recursos empleados para mantener el TAD*/
void freeADT (arbolesADT adt);

#endif
