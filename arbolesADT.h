#ifndef arbolesADT_H
#define arbolesADT_H

typedef struct arbolesCDT * arbolesADT;

/*Estructura generica que guarda un nombre y un entero*/
typedef struct {
    char * nombre;
    int dato;
}calleArbol;

/*Estructura generica que guarda un nombre y un double*/
typedef struct {
    char * nombre;
    double dato;
}calleArbolB;

/*Estructura generica que guarda dos nombres y un double*/
typedef struct {
    char * nombre;
    char *nombre2;
    double dato;
}calleArbolC;

/* Estructura que sera retornada en al menos una funcion en forma de un vector. 
- barrio almacena el nombre del barrio. 
- popCalle almaena el nombre de la calle con mas arboles, y la cantidad de arboles en ese barrio.
- poblacion almacena la cantidad de habitantes de un barrio.
- cantArb almacena la cantidad total de arboles en ese barrio. 
- diametroTotal almacena la suma de todos los diametros de los arboles de un mismo barrio.
*/
typedef struct {
    char * barrio;
    calleArbol popCalle;
    int poblacion;
    int cantArb;
    double diametroTotal;
}TQ3;

/* Estructura que sera retornada en al menos una funcion en forma de un vector. 
- arbol almacena el nombre del arbol. 
- dMin y dMax almacenan maximo y minimo diametro. 
*/
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

/* Agrega especie de arboles, Retorna 1 si el barrio se agrego de forma correcta, si se reporta
un problema mientras se asgina memoria, retorna 0.*/
int agregaArbol (arbolesADT adt, const char * barrio, const char *calle , const char * arbol, double diam);


/* Retorna un vector de calleArbolB estructura que es ordenado de forma descendiente segun el valor que toma el campo 
dato de cada estructura. La dimension del array es guardada en *dim. Si el array es generado correctamente, el puntero retorna un valor
diferente de null, si hay un problema mientras se asigna memoria, el valor de retorno es NULL. */
calleArbolB * resolQ1(arbolesADT adt, int *dim);


/* Retorna un vector de calleArbolB estructura que es ordenado de forma descendiente segun el valor que toma el campo 
dato de cada estructura. La dimension del array es guardada en *dim. Si el array es generado correctamente, el puntero retorna un valor
diferente de null, si hay un problema mientras se asigna memoria, el valor de retorno es NULL. */
calleArbolC * resolQ2( arbolesADT adt, int *dim );

/*Retorna un vector de TQ3 estructura que es ordenado por nombre de barrio en orden alfabetico.
La dimension del array es guardada en *dim. Si el array es generado correctamente, el puntero retorna un valor
diferente de null, si hay un problema mientras se asigna memoria, el valor de retorno es NULL. */
TQ3 * resolQ3(arbolesADT adt, int * dim);

/*Retorna un vector de TQ4 structuras ordenado por el nombre de los arboles en orden alfabetico.
La dimension del array es guardada en *dim. Si el array es generado correctamente, el puntero retorna un valor
diferente de null, si hay un problema mientras se asigna memoria, el valor de retorno es NULL. */
TQ4 * resolQ4(arbolesADT adt, int * dim);

/*Libera todos los recursos empleados para mantener el TAD*/
void freeADT (arbolesADT adt);

#endif
