#include "arbolesADT.h"
#include <stdio.h>
#include <stdlib.h>

#define MAL_ARGS 1
#define ERROR_ABERTURA 2
#define SIN_MEMORIA 3
#define ERROR_CREANDO 4

#define HEADERS_QUERY1 "BARRIO;DIAMETRO_PROMEDIO\n"
#define HEADERS_QUERY2 "BARRIO;NOMBRE_CIENTIFICO;ARBOLES_POR_HABITANTE\n"
#define HEADERS_QUERY3 "BARRIO;CALLE_CON_MAS_ARBOLES;ARBOLES\n"
#define HEADERS_QUERY4 "NOMBRE_CIENTIFICO;MIN;MAX\n"

void mensajeError( int codigo );

int chequearArgs(int args);

int abrirArchivos(FILE ** hoodsFile, FILE ** treesFile, const char * argv[]);

int leerBarrios(FILE * hoodsFile, arbolesADT adt);

int leerArboles(FILE * treesFile, arbolesADT adt, int maxCol, int hoodCol, int streetCol, int treeNameCol, int diamCol);

int resolverQuerys (arbolesADT adt);
